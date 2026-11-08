#include <stdio.h>

#define MU_ASSERT(TEST, MESSAGE)                                               \
  do {                                                                         \
    if (!(TEST))                                                               \
      return (MESSAGE);                                                        \
  } while (0);
#define MU_RUN_TEST(TEST)                                                      \
  do {                                                                         \
    char *message = TEST();                                                    \
    if (message)                                                               \
      return message;                                                          \
  } while (0);

size_t tests_run = 0;

unsigned long long gcd(unsigned long long x, unsigned long long y);
void safe_convert_to_llu(long long x, long long y, unsigned long long *ux,
                         unsigned long long *uy);

static char *test_gcd() {
  long long x[] = {2, 3, 2, 1769, 698917, 917, -417143, 63862, 702228, -659323};

  long long y[] = {1, 2, 4, 427, -102089, 872, -455947, -55298, 373125, 727699};

  unsigned long long ans[] = {1, 1, 2, 61, 7853, 1, 9701, 2, 3, 7};

  for (size_t i = 0; i < (sizeof(x) / sizeof(x[0])); ++i) {
    tests_run++;

    static char error_msg[256];

    snprintf(error_msg, sizeof(error_msg),
             "Exception: gcd(%lld, %lld). Expected %llu, but got %llu", x[i],
             y[i], ans[i], gcd(x[i], y[i]));

    unsigned long long ux = 0, uy = 0;
    safe_convert_to_llu(x[i], y[i], &ux, &uy);

    MU_ASSERT(gcd(ux, uy) == ans[i], error_msg);
  }

  return 0;
}

static char *all_tests() {
  MU_RUN_TEST(test_gcd);
  return 0;
}

int main(void) {
  char *result = all_tests();

  if (result != 0)
    printf("%s\n", result);
  else
    printf("ALL TESTS COMPLETED!\n");

  printf("tests ran: %zu\n", tests_run);

  return result != 0;
}
