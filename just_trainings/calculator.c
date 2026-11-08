#include <assert.h>
#include <stdio.h>

int main(void) {
  int a, b;
  char op;
  int res = scanf("%d %c %d", &a, &op, &b);
  assert(3 == res);
  switch (op) {
  case '+':
    printf("%d\n", a + b);
    break;
  case '-':
    printf("%d\n", a - b);
    break;
  case '*':
    printf("%d\n", a * b);
    break;
  case '/':
    if (b == 0) {
      printf("can`t divide on zero\n");
      break;
    }
    printf("%d\n", a / b);
    break;
  };
  return 0;
}
