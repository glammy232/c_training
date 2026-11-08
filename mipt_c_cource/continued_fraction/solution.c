#include <stdio.h>

char *continued_fraction(long long x, long long div) {
  static char res[256];
  size_t i = 0;

  while (x % div != 0) {
    if (x % div > 0 && x / div == 0) {
      res[i] = 0;
      i++;
      x = x % div;
      continue;
    }
  }
  return res;
}

int main(void) {
  printf("%lld\n", 1ll % 3);
  printf("%lld\n", 1ll / 3);
  printf("%s\n", continued_fraction(1LL, 3LL));
  return 0;
}
