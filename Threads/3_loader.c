#include "3.h"

extern int store_goods[NUM_STORES];
extern pthread_mutex_t store_mutexes[NUM_STORES];

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
