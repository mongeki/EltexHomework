#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int sig_num, siginfo_t* info, void* args) {
  int* param = (int*)args;
  printf("Signal SIGUSR1=%d, %d %d\n", sig_num, info->si_signo, *param);
}

int main() {
  struct sigaction handler;
  sigset_t set;
  int ret;

  pid_t pid = getpid();
  printf("My pid is %d\n", pid);

  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);

  handler.sa_handler = NULL;
  handler.sa_sigaction = sig_handler;
  handler.sa_mask = set;
  handler.sa_flags = 0;

  ret = sigaction(SIGUSR1, &handler, NULL);
  if (ret < 0) {
    perror("Can't set signal handler\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    sleep(1);
  }

  exit(EXIT_SUCCESS);
}
