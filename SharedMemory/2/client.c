#include <curses.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "chat.h"

ChatRoom* room;
char myname[MAX_NAME_LEN];
char empty[MAX_NAME_LEN];  // Empty string for comparing

WINDOW* users;
WINDOW* chat;
WINDOW* input;

sem_t* sem;
sem_t* sem2;

void* sender() {
  while (1) {
    char message[MAX_MSG_LEN];
    mvwgetstr(input, 1, 1, message);                // Input message
    if (strcmp(message, "exit") == 0) return NULL;  // Stop-word

    sem_wait(sem);  // Critical sections begins

    sprintf(room->messages[room->msg_count], "[%s]: %s", myname, message);
    room->msg_count++;

    sem_post(sem);  // End

    werase(input);  // ncurses refresh window
    box(input, 0, 0);
    wrefresh(input);
  }
}
void* receiver() {  // Printing messages
  while (1) {
    werase(chat);
    for (int i = 0; i < room->msg_count; ++i) {
      mvwprintw(chat, i + 1, 1, "%s", room->messages[i]);
    }
    box(chat, 0, 0);
    wrefresh(chat);
    usleep(200000);
  }
}
void* show_users() {  // Printing online users
  while (1) {
    werase(users);
    int users_on_screen = 0;
    for (int i = 0; i < MAX_CLIENTS; ++i) {
      if (memcmp(room->clients[i], empty, sizeof(empty))) {
        mvwprintw(users, users_on_screen + 1, 1, "%s", room->clients[i]);
        users_on_screen++;
      }
    }
    box(users, 0, 0);
    wrefresh(users);
    usleep(500000);
  }
}

int main() {
  /* Open shared memory */
  int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
  room =
      mmap(0, sizeof(ChatRoom), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  printf("Enter your name: ");
  scanf("%s", myname);

  /* Open semaphores */
  sem = sem_open(SEM_NAME, O_RDWR);
  sem2 = sem_open(SEM2_NAME, O_RDWR);

  memset(empty, 0, sizeof(empty));
  int my_index = 0;

  sem_wait(sem2);  // Critical section begins

  for (int i = 0; i < MAX_CLIENTS; ++i) {  // Finding free pos in clients array
    if (memcmp(room->clients[i], empty, sizeof(empty)) == 0) {
      strcpy(room->clients[i], myname);
      my_index = i;
      break;
    }
  }

  sem_post(sem2);  // End

  /* Long ncurses preparation */
  initscr();
  cbreak();
  curs_set(0);
  refresh();
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
  int rows = size.ws_row;
  int cols = size.ws_col;
  chat = newwin(rows - 4, cols / 3 * 2 - 1, 0, 0);
  users = newwin(rows - 4, cols / 3 - 1, 0, cols / 3 * 2 + 1);
  input = newwin(3, cols, rows - 3, 0);
  box(users, 0, 0);
  box(chat, 0, 0);
  box(input, 0, 0);
  wrefresh(users);
  wrefresh(chat);
  wrefresh(input);

  /* 3 threads for "sending", "receiving" messages, and printing online-users */
  pthread_t receive_thread, send_thread, users_thread;
  pthread_create(&send_thread, NULL, sender, NULL);
  pthread_create(&receive_thread, NULL, receiver, NULL);
  pthread_create(&users_thread, NULL, show_users, NULL);

  pthread_join(send_thread, NULL);
  pthread_cancel(receive_thread);  // If sending is over, cancel other threads
  pthread_cancel(users_thread);
  pthread_join(receive_thread, NULL);
  pthread_join(users_thread, NULL);

  memset(room->clients[my_index], 0,
         sizeof(room->clients[1]));  // Deleting our name from users-list
                                     /* Closing shared memory and semaphores */
  close(shm_fd);
  sem_close(sem);
  sem_close(sem2);

  delwin(users);
  delwin(chat);
  delwin(input);
  endwin();
  exit(EXIT_SUCCESS);
}
