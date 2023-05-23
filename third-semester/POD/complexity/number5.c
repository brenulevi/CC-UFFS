#include <stdio.h>

int factorial(int n, int result)
{
    if(n < 1)
        return result;

    result *= n;

    factorial(n-1, result);
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", factorial(n, 1));

    return 0;
}

// Complexidade: N