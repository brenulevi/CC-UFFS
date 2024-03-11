#include <stdio.h>

int main() {
    int num1, num2, result = 0;

    scanf("%d %d", &num1, &num2);

    for(int i = 0; i < num2; i++) {
        result += num1;
    }

    printf("%d\n", result);
    return 0;
}

// Complexidade: N