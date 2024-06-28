#include <stdio.h>

#define N 7

int main() {
  int matrix[N][N];
  int n = 0;
  for (int lvl = 0; lvl <= N / 2; ++lvl) {
    for (int i = lvl; i < N - lvl; ++i) {
      matrix[lvl][i] = ++n;
    }
    for (int i = lvl + 1; i < N - lvl; ++i) {
      matrix[i][N - lvl - 1] = ++n;
    }
    for (int i = N - lvl - 2; i > lvl; --i) {
      matrix[N - lvl - 1][i] = ++n;
    }
    for (int i = N - lvl - 1; i > lvl; --i) {
      matrix[i][lvl] = ++n;
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
