#include "3.h"

void exec_commands(char *input) {
  char *commands[MAX_CMDS];
  int num_cmds = 0;

  // Разделяем команды
  commands[num_cmds] = strtok(input, "|");
  while (commands[num_cmds] != NULL) {
    num_cmds++;
    commands[num_cmds] = strtok(NULL, "|");
  }

  int pipefd[2 *
             (num_cmds - 1)];  // Вместо матрицы, массив для дескрипторов пайпов
  for (int i = 0; i < num_cmds - 1; ++i) {
    if (pipe(pipefd + i * 2) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < num_cmds; ++i) {  // По порядку порождаем процессы
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // дочерний процесс
      if (i >
          0) {  // если не первая команда, подключаем stdin к предыдущему пайпу
        if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) == -1) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }
      if (i < num_cmds - 1) {  // если не последняя команда, подключаем stdout к
                               // текущему пайпу
        if (dup2(pipefd[i * 2 + 1], STDOUT_FILENO) == -1) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }

      // Закрываем дескрипторы пайпов
      for (int j = 0; j < 2 * (num_cmds - 1); ++j) {
        close(pipefd[j]);
      }

      // Разбиваем команду на аргументы
      char *args[MAX_ARGV];
      int count = 0;
      char *arg = strtok(commands[i], " \n");
      while (arg != NULL) {
        args[count++] = arg;
        arg = strtok(NULL, " \n");
      }
      args[count] = NULL;

      execvp(args[0], args);
      perror("execvp");
      exit(EXIT_FAILURE);
    }
  }

  // Закрываем дескрипторы пайпов в родительском процессе
  for (int j = 0; j < 2 * (num_cmds - 1); ++j) {
    close(pipefd[j]);
  }

  // Ожидаем завершения всех дочерних процессов
  for (int i = 0; i < num_cmds; ++i) {
    wait(NULL);
  }
}
