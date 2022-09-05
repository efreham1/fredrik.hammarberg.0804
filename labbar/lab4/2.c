#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;

}

int main(void)
{
  int x = 7;
  int y = 42;
  swap(&x, &y);
  printf("%d, %d\n", x, y);
  return 0;
}