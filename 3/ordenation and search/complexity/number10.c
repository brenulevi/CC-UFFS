#include <stdio.h>

float average(int *grades)
{
    int sum = 0;
    for(int i = 0; i < 10; i++) 
    {
        sum += grades[i];
    }
    return (float)sum/(float)10;
}

int main()
{
    int mat;
    int students = 0;
    float averages = 0;

    while(1)
    {
        printf("Matricula: ");
        scanf("%d", &mat);

        if(mat == 0)
            break;

        int grades[10];
        for(int i = 0; i < 10; i++) {
            printf("Nota %d: ", i+1);
            scanf("%d", &grades[i]);
        }

        float student_average = average(grades);
        printf("%d, media: %.1f\n", mat, student_average);

        students++;
        averages += student_average;
    }

    printf("Media geral da turma: %.1f\n", (float)averages/(float)students);

    return 0;
}

// Complexidade: N