#include <stdio.h>

#define N 7

void print(int *arr);

int main() {
  int arr[N];
  for (int i = 0; i < N; ++i) {
    arr[i] = i + 1;
  }
  print(arr);
  for (int i = 0; i < N / 2; ++i) {
    int tmp = arr[i];
    arr[i] = arr[N - 1 - i];
    arr[N - 1 - i] = tmp;
  }
  print(arr);
}

void print(int *arr) {
  for (int i = 0; i < N; ++i) {
    printf("%3d", arr[i]);
  }
  printf("\n");
}
