#include <stdio.h>

long long factorial(int n);

int main() {
    int n;
    
    printf("Enter a value for n: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Error: n must be greater than or equal to 0.\n");
    } else {
        long long result = factorial(n);
        printf("Factorial of %d is: %lld\n", n, result);
    }
    
    return 0;
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}