#include <curses.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "chat.h"

WINDOW *users;
WINDOW *chat;
WINDOW *input;

char myname[MAX_NAME_LEN];
mqd_t to_server, to_client;

void *sender() {
  ChatMessage message;
  strcpy(message.name, myname);
  while (1) {
    mvwgetstr(input, 1, 1, message.message);                // Input message
    if (strcmp(message.message, "exit") == 0) return NULL;  // Stop-word
    werase(input);  // Clear input message
    if (mq_send(to_server, (char *)&message, sizeof(ChatMessage), 0) < 0) {
      perror("mq_send");
      exit(EXIT_FAILURE);
    }
  }
}
void *receiver() {
  ChatMessage message;
  int msgs_on_screen = 0;
  while (1) {
    if (mq_receive(to_client, (char *)&message, sizeof(ChatMessage), NULL) <
        0) {
      perror("mq_receive");
      exit(EXIT_FAILURE);
    }
    mvwprintw(chat, msgs_on_screen + 1, 1, "[%s]: %s\n", message.name,
              message.message);  // Print message, no overflow check :(
    box(chat, 0, 0);             // Drawing broken frames of the window again
    wrefresh(chat);
    msgs_on_screen++;
  }
}

int main() {
  char to_server_qname[MAX_QNAME_LEN];
  char to_client_qname[MAX_QNAME_LEN];
  struct mq_attr to_server_attr, to_client_attr;
  to_server_attr.mq_flags = 0;
  to_server_attr.mq_maxmsg = 10;
  to_server_attr.mq_msgsize = sizeof(ChatMessage);
  to_server_attr.mq_curmsgs = 0;
  to_client_attr.mq_flags = 0;
  to_client_attr.mq_maxmsg = 10;
  to_client_attr.mq_msgsize = sizeof(ChatMessage);
  to_client_attr.mq_curmsgs = 0;

  printf("Enter your name: ");
  scanf("%s", myname);

  mqd_t server_mqd =
      mq_open("/server_queue", O_RDWR);  // Queue for registration
  if (server_mqd < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }
  ChatMessage message;
  strcpy(message.name, myname);

  sprintf(to_server_qname, "/to_server_q_%s", message.name);
  sprintf(to_client_qname, "/to_client_q_%s", message.name);
  mq_unlink(to_server_qname);
  mq_unlink(to_client_qname);
  to_server = mq_open(to_server_qname, O_CREAT | O_RDWR, 0666,
                      &to_server_attr);  // Queue for sending
  if (to_server < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }
  to_client = mq_open(to_client_qname, O_CREAT | O_RDWR, 0666,
                      &to_client_attr);  // Queue for receiving
  if (to_client < 0) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }
  if (mq_send(server_mqd, (const char *)&message, sizeof(ChatMessage), 0) < 0) {
    perror("mq_send");
    exit(EXIT_FAILURE);
  }

  /* Long ncurses preparation */
  initscr();
  cbreak();
  curs_set(0);
  refresh();
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  int rows = size.ws_row;
  int cols = size.ws_col;
  chat = newwin(rows - 4, cols / 3 * 2 - 1, 0, 0);
  users = newwin(rows - 4, cols / 3 - 1, 0, cols / 3 * 2 + 1);
  input = newwin(3, cols, rows - 3, 0);
  box(users, 0, 0);
  box(chat, 0, 0);
  box(input, 0, 0);
  mvwprintw(users, 1, 1, "There will be users-list");  // No user-list yet

  wrefresh(users);
  wrefresh(chat);
  wrefresh(input);

  pthread_t send_thread, receive_thread;
  pthread_create(&send_thread, NULL, sender, NULL);  // Thread for sending msgs
  pthread_create(&receive_thread, NULL, receiver,
                 NULL);  // Thread for receiving msgs

  pthread_join(send_thread, NULL);
  pthread_cancel(receive_thread);  // If sending is over, cancel receiving
  pthread_join(receive_thread, NULL);

  mq_close(to_server);
  mq_close(to_client);
  mq_close(server_mqd);
  mq_unlink(to_server_qname);
  mq_unlink(to_client_qname);

  delwin(users);
  delwin(chat);
  delwin(input);
  endwin();
  exit(EXIT_SUCCESS);
}
