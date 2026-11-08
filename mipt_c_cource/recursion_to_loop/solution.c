unsigned long long gcd(unsigned long long x, unsigned long long y) {
  unsigned long long q;

#if 0
  if (y > x) {
    q = x;
    x = y;
    y = q;
  }
#endif

  while ((x % y) != 0) {
    q = x % y;
    x = y;
    y = q;
  }

  return y;
}

void safe_convert_to_llu(long long x, long long y, unsigned long long *ux,
                         unsigned long long *uy) {
  *ux = (x < 0) ? x * -1 : x;
  *uy = (y < 0) ? y * -1 : y;
}
