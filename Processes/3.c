#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGV 128

int main() {
  char input[MAX_INPUT];
  char *argv[MAX_ARGV];

  pid_t cpid;
  int wstatus;

  while (1) {
    printf("bash$ ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
      break;
    }
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {  // Delete \n
      input[len - 1] = '\0';
    }
    int count = 0;
    argv[count] = strtok(input, " ");
    while (argv[count] != NULL && count < MAX_ARGV - 1) {
      count++;
      argv[count] = strtok(NULL, " ");
    }
    argv[count] = NULL;  // MAN execvp: "The array of pointers must be
                         // terminated by a null pointer."
    if (strcmp(argv[0], "exit") == 0) {
      break;
    }
    cpid = fork();
    if (cpid == -1) {
      perror("fork");
      continue;
    }
    if (cpid == 0) {
      if (execvp(argv[0], argv) ==
          -1) {  // MAN execvp: "The file is sought  in the  colon-separated
                 // list of directory pathnames specified in the PATH
                 // environment variable."
        perror("execvp");
      }
      exit(EXIT_FAILURE);
    } else {
      waitpid(cpid, &wstatus, 0);
    }
  }
  exit(EXIT_SUCCESS);
}
