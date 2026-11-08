#include <stdlib.h>

struct stack {
  size_t sz;
  size_t els_cnt;
  void *dt;
};

void stack_push(struct stack *stack, const void *el, size_t el_sz) {
  stack->dt = realloc(stack->dt, stack->sz + el_sz);
  stack->sz += el_sz;
  stack->els_cnt++;
}

void stack_pop(void) {}

int main(void) {
  struct stack *st = malloc(sizeof(struct stack));
  int a = 5;
  stack_push(st, (const void *)&a, sizeof(int));
}
