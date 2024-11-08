#include <stdio.h>

int main() {
  int num;
  if (scanf("%d", &num) != 1 || num < 1) {
    printf("NaN or number is non-positive\n");
    return -1;
  }
  int count = 0;
  for (; num > 0; num >>= 1) {
    if (num & 1) ++count;
  }
  printf("%d\n", count);
  return 0;
}
