#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo"
#define MESSAGE_SIZE 4

int main() {
  // Открытие канала на чтение
  int fd = open(FIFO_NAME, O_RDONLY);
  if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
  }

  // Чтение строки из канала
  char buffer[MESSAGE_SIZE];
  read(fd, buffer, MESSAGE_SIZE);

  // Вывод прочитанной строки на экран
  printf("%s\n", buffer);

  // Закрытие канала
  close(fd);

  exit(EXIT_SUCCESS);
}
