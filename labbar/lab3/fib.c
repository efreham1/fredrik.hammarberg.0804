#include <stdio.h>

typedef int(*int_fold_func)(int, int);

int fib(int num)
{
  int ppf = 0; // the two given fib values
  int pf  = 1;

  for (int i = 1; i < num; ++i)
  {
    int tmp = pf;
    pf = ppf + pf;
    ppf = tmp;
  }

  return pf;
}

int rec_fib(int num){
    if (num == 1 || num == 2){
        return 1;
    }
    else{
        return rec_fib(num-1) + rec_fib(num-2);
    }
}

int add(int a, int b)
{
  return a + b;
}

int foldl_int_int(int numbers[], int numbers_siz, int_fold_func f)
{
  int result = 0;

  for (int i = 0; i < numbers_siz; ++i)
  {
    result = f(result, numbers[i]);
  }

  return result;
}

long sum(int numbers[], int numbers_siz){
    return foldl_int_int(numbers, numbers_siz, add);
}

int main(void){

    printf("rekursivt: %d, imperativt: %d\n", fib(5), rec_fib(5));
    int array[] = {1, 2, 3, 4, 5};
    printf("sum: %ld\n", sum(array, 5));

    return 0;
}