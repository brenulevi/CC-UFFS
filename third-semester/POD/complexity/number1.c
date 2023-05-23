#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    for(int i = 1; i <= num; i++) {
        printf("%d\n", i);
        if(i == num/2)
            printf("Metade\n");
    }
    return 0;
}

// Complexidade: N