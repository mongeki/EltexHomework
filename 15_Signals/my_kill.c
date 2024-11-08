#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
        Name: my_kill - sends signal to process by PID
        Usage: ./mykill [-signal] pid
                             |
                      SIGTERM by default
*/

int main(int argc, char* argv[]) {
  int pid;
  int signal;
  if (argc > 1 && argc < 4) {
    if (argc == 3) {
      sscanf(argv[1], "-%d", &signal);  // Should check
      sscanf(argv[2], "%d", &pid);      // Should check
    } else if (argc == 2) {
      sscanf(argv[1], "%d", &pid);  // Should check
      signal = SIGTERM;
    }
    kill(pid, signal);  // Should check?
  } else {
    printf("Usage:\n\t./mykill [-signal] pid\n");
  }
  exit(EXIT_SUCCESS);
}
