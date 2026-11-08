#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 127

int main(void) {
  srand((unsigned int)time(NULL));
  int num = rand() % (MAX_NUM + 1);

  int ans = -1;
  while (ans != num) {
    int res = scanf("%d", &ans);
    assert(1 == res);
    if (ans > num) {
      printf("less\n");
    } else if (ans < num) {
      printf("more\n");
    } else {
      printf("you win: %d\n", num);
      return 0;
    }
  };
  return 0;
}
