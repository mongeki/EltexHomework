#include "shmposix.h"

int main() {
  int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);

  char *ptr = mmap(0, MSG_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("Server: %s\n", ptr);

  sprintf(ptr, "Hello!");
  printf("Client: %s\n", ptr);

  munmap(ptr, MSG_SIZE);
  close(shm_fd);
	exit(EXIT_SUCCESS);
}
