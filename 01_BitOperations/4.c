#include <stdio.h>
#include <stdlib.h>

/* Change the value of the third byte in a positive integer
   to the number entered by the user (the original number is
   also entered from the keyboard). */

int main() {
  int num;
  int repl;
  if (scanf("%d %d", &num, &repl) != 2 || num < 1) {
    perror("scanf");
    exit(EXIT_FAILURE);
  }
  num = (num & 0xFFFF00FF) | (repl & 0x000000FF) << 16;
  printf("%d\n", num);
  exit(EXIT_SUCCESS);
}
