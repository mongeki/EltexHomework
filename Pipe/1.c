#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MESSAGE_SIZE 4

int main() {
  int pipefd[2];  // Массив для дескрипторов канала
  pid_t pid;

  // Создаем неименованный канал
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    // Закрываем дескриптор для чтения
    close(pipefd[0]);

    // Записываем строку в канал
    write(pipefd[1], "Hi!", MESSAGE_SIZE);

    // Закрываем дескриптор для записи
    close(pipefd[1]);

    // Ожидаем завершения дочернего процесса
    wait(NULL);
  } else {
    // Закрываем дескриптор для записи
    close(pipefd[1]);

    // Читаем строку из канала
    char buffer[MESSAGE_SIZE];
    read(pipefd[0], buffer, MESSAGE_SIZE);

    // Закрываем дескриптор для чтения
    close(pipefd[0]);

    // Выводим прочитанную строку на экран
    printf("%s\n", buffer);
  }
  return 0;
}
