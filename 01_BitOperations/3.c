#include <stdio.h>
#include <stdlib.h>

/* Find the number of ones in the binary representation 
 * of a positive integer */

int main() {
  int num;
  if (scanf("%d", &num) != 1 || num < 1) {
    perror("scanf");
    exit(EXIT_FAILURE);
  }
  int count = 0;
  for (; num > 0; num >>= 1) {
    if (num & 1) ++count;
  }
  printf("%d\n", count);
  exit(EXIT_SUCCESS);
}
