#include "3.h"

int main() {
  char input[MAX_INPUT];
  while (1) {
    printf("bash$ ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
      perror("fgets");
      continue;
    }
    size_t len = strlen(input);
    // Delete \n
    if (len > 0 && input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }
    if (strcmp(input, "exit") == 0) {
      break;
    }
    exec_commands(input);
  }
  exit(EXIT_SUCCESS);
}
