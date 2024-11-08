#include <stdio.h>
#include <stdlib.h>

/* Prints binary binary representation of a integer
 * using bitwise operations */

int main() {
  int num;
  if (scanf("%d", &num) != 1) {
    perror("scanf");
    exit(EXIT_FAILURE);
  }
  for (int bit = 31; bit >= 0; --bit) {
    printf("%d", (num >> bit) & 1);
  }
  printf("\n");
  exit(EXIT_SUCCESS);
}
