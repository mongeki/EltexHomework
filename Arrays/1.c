#include <stdio.h>

#define N 6

int main() {
  int arr[N][N];
  int n = 1;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j, ++n) {
      arr[i][j] = n;
      printf("%5d", arr[i][j]);
    }
    printf("\n");
  }
  return 0;
}
