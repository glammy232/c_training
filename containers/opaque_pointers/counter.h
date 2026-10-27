#ifndef COUNTER_H
#define COUNTER_H

typedef struct counter counter_t;

counter_t *counter_create(int initial_value, int secret_number);
void counter_destroy(counter_t *c);

int counter_increment(counter_t *c);
int counter_decrement(counter_t *c);
int counter_get(const counter_t *c);

int counter_guess(counter_t *c, int guess);
int counter_attempts(const counter_t *c);

#endif
