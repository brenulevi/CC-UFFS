#include <stdio.h>

int main() {
    int num, result = 0;

    scanf("%d", &num);

    for(int i = 1; i <= num; i++)
        result += i;
    
    printf("%d\n", result);

    return 0;
}

// Complexidade: N