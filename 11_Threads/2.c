#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9

long a = 0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *thread_calc() {
  for (int i = 0; i < 100000000; ++i) {
    pthread_mutex_lock(&m1);
    a = a + 1;
    pthread_mutex_unlock(&m1);
  }
  return NULL;
}

int main() {
  int retval;
  pthread_t thread[N];
  for (int i = 0; i < N; ++i) {
    pthread_create(&thread[i], NULL, thread_calc, NULL);
  }
  for (int j = 0; j < N; ++j) {
    pthread_join(thread[j], (void **)&retval);
  }
  printf("a = %ld\n", a);
  exit(EXIT_SUCCESS);
}
