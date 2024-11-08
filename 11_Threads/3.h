#ifndef THREAD3_H
#define THREAD3_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_STORES 5
#define NUM_CUSTOMERS 3

void* thread_customer();
void* thread_loader();

#endif
