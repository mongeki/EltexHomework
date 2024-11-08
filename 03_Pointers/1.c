#include <stdio.h>
#include <stdlib.h>

int main() {
  int num;
  int repl;
  if (scanf("%d%d", &num, &repl) != 2 || num < 1) {
    perror("scanf");
    exit(EXIT_FAILURE);
  }
  char* ptr = (char*)&num;
  ptr += 2;
  *ptr = repl;
  printf("%d\n", num);
  exit(EXIT_SUCCESS);
}
