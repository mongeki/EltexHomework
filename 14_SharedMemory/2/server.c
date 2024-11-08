#include "chat.h"

int main() {
  shm_unlink(SHM_NAME);
  sem_unlink(SEM_NAME);
  sem_unlink(SEM2_NAME);

  /* One struct in shared memory */
  int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, sizeof(ChatRoom));
  ChatRoom* room =
      mmap(0, sizeof(ChatRoom), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  /* Create semaphores, need 2 */
  sem_t* sem = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0666, 1);
  sem_t* sem2 = sem_open(SEM2_NAME, O_CREAT | O_RDWR, 0666, 1);

  /* Initializing struct */
  room->msg_count = 0;
  room->client_count = 0;
  for (int i = 0; i < MAX_CLIENTS; ++i) {
    memset(room->clients[i], 0, sizeof(room->clients[i]));
  }

  /* Endless loop */
  printf("Server is up...\n");
  while (1) {
    sleep(10);
  }

  /* Unreachable, maybe use signal handler */
  sem_close(sem);
  sem_close(sem2);
  sem_unlink(SEM_NAME);
  sem_unlink(SEM2_NAME);

  munmap(room, sizeof(ChatRoom));
  close(shm_fd);
  shm_unlink(SHM_NAME);
  exit(EXIT_SUCCESS);
}
