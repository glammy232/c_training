#include <assert.h>
#include <stdio.h>

int main(void) {
  int a, b;
  int test = scanf("%d%d", &a, &b);

  if (test != 2)
    return 1;

  assert(a != 0 && b != 0);

  int min = a < b ? a : b;
  int i;

  for (i = min; i > 1; --i) {
    if (a % i == 0 && b % i == 0) {
      printf("%d\n", i);
      return i;
    }
  }

  return 0;
}
