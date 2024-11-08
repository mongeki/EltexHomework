#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t p1, p2;
  int p1status, p2status;
  printf("Parent PID is %d\n", getpid());
  printf("Parent PPID is %d\n", getppid());
  if ((p1 = fork()) == 0) {
    printf("P1 PID is %d\n", getpid());
    printf("P1 PPID is %d\n", getppid());
    pid_t p3, p4;
    int p3status, p4status;
    if ((p3 = fork()) == 0) {
      printf("P3 PID is %d\n", getpid());
      printf("P3 PPID is %d\n", getppid());
    } else if (p3 > 0 && (p4 = fork()) == 0) {
      printf("P4 PID is %d\n", getpid());
      printf("P4 PPID is %d\n", getppid());
    } else if (p3 < 0 || p4 < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else {
      waitpid(p3, &p3status, 0);
      waitpid(p4, &p4status, 0);
    }
  } else if (p1 > 0 && (p2 = fork()) == 0) {
    printf("P2 PID is %d\n", getpid());
    printf("P2 PPID is %d\n", getppid());
    pid_t p5;
    int p5status;
    if ((p5 = fork()) == 0) {
      printf("P5 PID is %d\n", getpid());
      printf("P5 PPID is %d\n", getppid());
    } else if (p5 < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else {
      waitpid(p5, &p5status, 0);
    }
  } else if (p1 < 0 || p2 < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else {
    waitpid(p1, &p1status, 0);
    waitpid(p2, &p2status, 0);
  }
  exit(0);
}
