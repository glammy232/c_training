#include "ring_buffer.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#define N_ITEMS 100000

static ring_buffer_t g_rb;
static uint8_t g_storage[1024];

// Producer: пишет 0..N_ITEMS-1, при переполнении — повторяет попытку
static void *producer(void *arg) {
  (void)arg;
  for (size_t i = 0; i < N_ITEMS; ++i) {
    uint8_t v = (uint8_t)(i & 0xFF);
    while (!ring_buffer_push(&g_rb, v)) {
      // буфер полон — немного подождём (можно использовать condvar/futex)
      sched_yield();
    }
  }
  return NULL;
}

// Consumer: читает ровно N_ITEMS байт и проверяет порядок
static void *consumer(void *arg) {
  (void)arg;
  size_t received = 0;
  uint8_t v;
  while (received < N_ITEMS) {
    if (ring_buffer_pop(&g_rb, &v)) {
      if (v != (uint8_t)(received & 0xFF)) {
        fprintf(stderr, "MISMATCH at %zu: got %u\n", received, v);
        return (void *)1;
      }
      ++received;
    } else {
      sched_yield();
    }
  }
  printf("Consumer received %zu items OK\n", received);
  return NULL;
}

int main(void) {
  if (!ring_buffer_init(&g_rb, g_storage, sizeof(g_storage))) {
    fprintf(stderr, "init failed\n");
    return 1;
  }

  pthread_t tp, tc;
  pthread_create(&tp, NULL, producer, NULL);
  pthread_create(&tc, NULL, consumer, NULL);
  pthread_join(tp, NULL);
  void *res;
  pthread_join(tc, &res);
  return res ? 1 : 0;
}
