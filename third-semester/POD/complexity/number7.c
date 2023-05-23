#include <stdio.h>

int main() 
{
    int salary = 0, children = 0, total = 0;
    while (1) {
        printf("Salario: ");
        int s;
        scanf("%d", &s);

        if(s < 0)
            break;

        printf("Filhos: ");
        int c;
        scanf("%d", &c);

        salary += s;
        children += c;

        total++;
    }

    printf("Media salarios: %.1f\nMedia filhos: %.1f\n", (float)salary/(float)total, (float)children/(float)total);

    return 0;
}