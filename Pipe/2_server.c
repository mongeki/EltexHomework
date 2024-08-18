#include <fcntl.h>  // open
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MESSAGE_SIZE 4

int main() {
  // Создание именованного канала
  if (mkfifo(FIFO_NAME, 0666) == -1) {
    perror("mkfifo failed");
    exit(EXIT_FAILURE);
  }
  // Открытие канала на запись
  int fd = open(FIFO_NAME, O_WRONLY);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }
  // Запись строки в канал
  write(fd, "Hi!", MESSAGE_SIZE);

  // Закрытие канала
  close(fd);

  // Удаление канала
  unlink(FIFO_NAME);

  exit(EXIT_SUCCESS);
}
