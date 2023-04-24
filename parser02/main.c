#include "tinyexpr.h"
#include <stdio.h>

int main()
{
  char *expr;
  int res;
  expr = "2 + 4 * 4! - 1";
  res = te_interp(expr, 0);
  printf("Expressão: %s\nResultado: %d\n", expr, res);
  return 0;
}