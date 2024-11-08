#include <stdio.h>

int main() {
  int num;
  if (scanf("%d", &num) != 1) {
    printf("NaN\n");
    return -1;
  }
  for (int bit = 31; bit >= 0; --bit) {
    printf("%d", (num >> bit) & 1);
  }
  printf("\n");
  return 0;
}
