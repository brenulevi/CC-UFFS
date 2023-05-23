#include <stdio.h>

double sum(double n1, double n2) {
    return n1 + n2;
}

double subtract(double n1, double n2) {
    return n1 - n2;
}

double multiply(double n1, double n2) {
    return n1 * n2;
}

double divide(double n1, double n2) {
    return n1 / n2;
}

int main() {
    int num1, num2, result;
    char op;

    scanf("%c", &op);

    while(op != '@') {
        scanf("%d %d", &num1, &num2);

        if(op == '+')
            printf("%f\n", sum(num1, num2));
        else if (op == '-')
            printf("%f\n", subtract(num1, num2));
        else if (op == '*')
            printf("%f\n", multiply(num1, num2));
        else if (op == '/')
            if(num2 != 0)
                printf("%f\n", divide(num1, num2));
            else printf("Denominador nao pode ser zero!\n");
        else printf("Operador invalido!\n");
    }

    return 0;
}

// Complexidade: N