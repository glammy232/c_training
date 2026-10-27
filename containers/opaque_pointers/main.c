#include "counter.h"
#include <stdio.h>

int main(void) {
  counter_t *c = counter_create(0, 42);

  for (int i = 0; i < 5; i++)
    counter_increment(c);
  printf("value = %d\n", counter_get(c));

  int guesses[] = {1, 7, 42};
  for (int i = 0; i < 3; i++) {
    if (counter_guess(c, guesses[i]))
      printf("Угадал с попытки №%d!\n", counter_attempts(c));
    else
      printf("Мимо: %d (попыток: %d)\n", guesses[i], counter_attempts(c));
  }

  counter_destroy(c);
  return 0;
}
