#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
  unsigned long long q;

  if (y > x) {
    q = x;
    x = y;
    y = q;
  }
  assert(y > 0);

  while ((x % y) != 0) {
    q = x % y;
    x = y;
    y = q;
  }

  return y;
}

int main(void) {
  long long x = 0, y = 0, g;
  int res;

  res = scanf("%lld %lld", &x, &y);
  assert(res == 2);
  unsigned long long ux = (x < 0) ? x * -1 : x;
  unsigned long long uy = (y < 0) ? y * -1 : y;
  g = gcd(ux, uy);
  printf("%llu\n", g);
  return 0;
}
