#include "3.h"

extern int store_goods[NUM_STORES];
extern pthread_mutex_t store_mutexes[NUM_STORES];

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
