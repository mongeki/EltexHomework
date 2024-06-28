#include <stdio.h>

int main() {
  int num;
  int repl;
  if (scanf("%d %d", &num, &repl) != 2 || num < 1) {
    printf("Error\n");
    return -1;
  }
  num = (num & 0xFFFF00FF) | (repl & 0x0000FF00);
  printf("%d\n", num);
  return 0;
}
