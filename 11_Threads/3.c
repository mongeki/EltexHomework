#include "3.h"

int store_goods[NUM_STORES];

pthread_mutex_t store_mutexes[NUM_STORES];

int main() {
  pthread_t customers[NUM_CUSTOMERS];
  pthread_t loader;

  int retval;

  int customer_id[NUM_CUSTOMERS] = {1, 2, 3};

  srand(time(0));
  for (int k = 0; k < NUM_STORES; ++k) {
    store_goods[k] = (rand() % (11000 - 9000 + 1)) + 9000;
  }

  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    pthread_create(&customers[i], NULL, thread_customer, &customer_id[i]);
  }
  pthread_create(&loader, NULL, thread_loader, NULL);

  for (int j = 0; j < NUM_CUSTOMERS; ++j) {
    pthread_join(customers[j], (void**)&retval);
  }
  pthread_cancel(loader);

  exit(EXIT_SUCCESS);
}
