#include <stdio.h>
#include <stdlib.h>

#define N 6

int main() {
  int matrix[N][N];
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      matrix[i][j] = N - i - 1 > j ? 0 : 1;
      printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
  exit(EXIT_FAILURE);
}
