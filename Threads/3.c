#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_STORES 5
#define NUM_CUSTOMERS 3

int store_goods[NUM_STORES];

pthread_mutex_t store_mutexes[NUM_STORES];

void* thread_customer(void* args) {
  int customer_id = *(int*)args;
  srand(time(0));
  int demand = (rand() % (110000 - 90000 + 1)) + 90000;
  while (demand > 0) {
    for (int store_id = 0; store_id < NUM_STORES; ++store_id) {
      pthread_mutex_lock(&store_mutexes[store_id]);
      if (store_goods[store_id] > 0) {
        printf("Покупатель %d зашел в магазин %d, в магазине %d, надо %d\n",
               customer_id, store_id, store_goods[store_id], demand);
        if (store_goods[store_id] > demand) {
          store_goods[store_id] -= demand;
          demand = 0;
        } else {
          demand -= store_goods[store_id];
          store_goods[store_id] = 0;
        }
        pthread_mutex_unlock(&store_mutexes[store_id]);
        sleep(2);
      } else {
        pthread_mutex_unlock(&store_mutexes[store_id]);
      }
    }
  }
  return NULL;
}

void* thread_loader() {
  while (1) {
    for (int store_id = 0; store_id < NUM_STORES; ++store_id) {
      pthread_mutex_lock(&store_mutexes[store_id]);
      store_goods[store_id] += 5000;
      printf("Погрузчик добавил 5000 в магазин %d. Всего теперь %d\n", store_id,
             store_goods[store_id]);
      pthread_mutex_unlock(&store_mutexes[store_id]);
      sleep(1);
    }
  }
  return NULL;
}

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

  exit(0);
}
