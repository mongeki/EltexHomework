#include <stdio.h>

int main() {
  int num;
  int repl;
  if (scanf("%d%d", &num, &repl) != 2 || num < 1) {
    printf("Error\n");
    return -1;
  }
  char* ptr = (char*)&num;
  ptr += 2;
  *ptr = repl;
  printf("%d\n", num);
  return 0;
}
