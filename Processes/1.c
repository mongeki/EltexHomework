#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t cpid;
  int wstatus;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) { /* Code executed by child */
    printf("Child's PID is %d\n", getpid());
    printf("Child's PPID is %d\n", getppid());
  } else { /* Code executed by parent */
    wait(&wstatus);
    printf("Parent's PID is %d\n", getpid());
    printf("Parent's PPID is %d\n", getppid());
    printf("Child's exitcode = %d\n", WEXITSTATUS(wstatus));
    exit(EXIT_SUCCESS);
  }
}
