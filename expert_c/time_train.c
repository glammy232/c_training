#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main(void) {
  time_t cur_time;
  time(&cur_time);
  printf("%s\n", ctime(&cur_time));
  time_t max_time = (time_t)((1UL << (sizeof(time_t) * CHAR_BIT - 1)) - 1);
  printf("%lld\n", (long long)max_time);
  double sec = difftime(max_time, cur_time);
  printf("%.2f seconds\n", sec);
  uint64_t y_sec = 365UL * 60 * 60 * 24;
  uint64_t m_sec = 30UL * 60 * 60 * 24;
  uint64_t w_sec = 7UL * 60 * 60 * 24;
  uint64_t d_sec = 24UL * 60 * 60;
  uint64_t h_sec = 60UL * 60;
  uint64_t min_sec = 60UL;

  uint64_t rem_sec = (uint64_t)sec;

  uint64_t y = rem_sec / y_sec;
  rem_sec %= y_sec;
  uint64_t m = rem_sec / m_sec;
  rem_sec %= m_sec;
  uint64_t w = rem_sec / w_sec;
  rem_sec %= w_sec;
  uint64_t d = rem_sec / d_sec;
  rem_sec %= d_sec;
  uint64_t h = rem_sec / h_sec;
  rem_sec %= h_sec;
  uint64_t min = rem_sec / min_sec;
  printf("%lu y, %lu m, %lu w, %lu d, %lu h, %lu m\n", y, m, w, d, h, min);
}
