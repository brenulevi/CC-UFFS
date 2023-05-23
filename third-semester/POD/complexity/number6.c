#include <stdio.h>

int main()
{
    int n, num_passed = 0, total_num = -1;
    do
    {
        scanf("%d", &n);
        if(n >= 10 && n <= 20)
            num_passed++;
        
        total_num++;

    } while (n > 0);
    
    printf("%c entre 10 e 20: %.2f%c\n", '%', ((float)num_passed/(float)total_num)*100, '%');

    return 0;
}

// Complexidade: N