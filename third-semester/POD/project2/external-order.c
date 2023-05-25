/**
 * @file external-order.c
 * @author Breno Soares Alves
 * @version
 * @date
 *
 * @copyright
 *
 * @brief
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_LIMIT 5

FILE **createFile(char *type);
void closeFile(FILE *file);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15};
    int vecLen = sizeof(vec) / sizeof(int);

    FILE **inputFiles;

    // creating input files
    inputFiles = createFile("input");

    // sorting and writing in respective input file
    int k = 0;
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        // sort
        for (int j = 0; j < MEMORY_LIMIT && k < vecLen; j++)
        {
        }

        // writing
        for (int j = 0; j < MEMORY_LIMIT && k < vecLen; j++)
        {
            fprintf(inputFiles[i], "%d", vec[k]);
            if (j < MEMORY_LIMIT - 1 && k < vecLen - 1)
                fprintf(inputFiles[i], ",");
        }
    }

    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        fclose(inputFiles[i]);
    }

    return 0;
}

FILE **createFile(char *type)
{
    FILE **files = malloc(MEMORY_LIMIT * sizeof(FILE *));
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char directory[30];
        sprintf(directory, ".\\bin\\%ss\\%s%d%s", type, type, i, ".txt");
        files[i] = fopen(directory, "r+");
        if (files[i] == NULL)
        {
            printf("Error to open file.");
            exit(1);
        }
    }
    return files;
}

//     for (int j = 0; j < MEMORY_LIMIT && k < 7; j++)
//     {
//         printf("%d ", originalVec[k++]);
//     }
//     printf("\n");