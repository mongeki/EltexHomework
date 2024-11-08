#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

void *thread_print(void *args) {
  printf("Thread #%d\n", *((int *)args));
  return NULL;
}

int main() {
  int retval;
  int thread_nums[N] = {0, 1, 2, 3, 4};
  pthread_t thread[N];
  for (int i = 0; i < N; ++i) {
    pthread_create(&thread[i], NULL, thread_print, (void *)&thread_nums[i]);
  }
  for (int j = 0; j < N; ++j) {
    pthread_join(thread[j], (void **)&retval);
  }
  exit(0);
}
