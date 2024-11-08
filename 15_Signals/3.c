#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  sigset_t set;
  int ret;
  int sig_num;

  pid_t pid = getpid();
  printf("My pid is %d\n", pid);

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  ret = sigprocmask(SIG_BLOCK, &set, NULL);
  if (ret < 0) {
    perror("Can't block signal disposition\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    sigwait(&set, &sig_num);
    printf("Sig number %d\n", sig_num);
  }

  exit(EXIT_SUCCESS);
}
