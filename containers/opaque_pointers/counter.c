#include "counter.h"
#include <stdlib.h>

struct counter {
  int value;
  int secret;
  int attempts;
};

counter_t *counter_create(int initial_value, int secret_number) {
  counter_t *c = malloc(sizeof *c);
  if (!c)
    return NULL;
  c->value = initial_value;
  c->secret = secret_number;
  c->attempts = 0;
  return c;
}

void counter_destroy(counter_t *c) { free(c); }

int counter_increment(counter_t *c) { return ++c->value; }
int counter_decrement(counter_t *c) { return --c->value; }
int counter_get(const counter_t *c) { return c->value; }

int counter_guess(counter_t *c, int guess) {
  c->attempts++;
  return guess == c->secret;
}

int counter_attempts(const counter_t *c) { return c->attempts; }
