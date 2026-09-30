#include <stdio.h>

int sum_to_n(int n);

int main() {
  int n;

  printf("Enter a value for n: ");
  scanf("%d", &n);

  if (n < 1) {
    printf("Error: n must be greater than or equal to 1.\n");
  } else {
    int result = sum_to_n(n);
    printf("Sum of integers from 1 to %d is: %d\n", n, result);
  }

  return 0;
}

int sum_to_n(int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum = sum + i;
  }
  return sum;
}