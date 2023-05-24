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

// Auxiliary Functions

void externalOrder(int *sortedVec, int *originalVec, int vecLen);
void printVec(int *vec, int vecLen);

// File Functions

FILE** createFile(char *type);
void closeFile(FILE *file);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15};
    int vecLen = sizeof(vec) / sizeof(int);

    int sortedVec[vecLen];

    externalOrder(sortedVec, vec, vecLen);

    return 0;
}

void externalOrder(int *sortedVec, int *originalVec, int vecLen)
{
    FILE **inputFiles;
    // create inputs files
    inputFiles = createFile("input");
    // distribute values in input files ordenered

    for(int i = 0; i < MEMORY_LIMIT; i++)
    {
        printf("%c\n",fgetc(inputFiles[i]));
    }



    // create output files
    // distribute values in output files comparing first values in input files
    // read output files
}

FILE** createFile(char *type)
{
    FILE** files = malloc(MEMORY_LIMIT * sizeof(FILE*));
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char directory[20];
        sprintf(directory, "./bin/%ss/%s%d%s", type, type, i, ".txt");
        files[i] = fopen(directory, "r+");
    }
    return files;
}

// printf("File number: %d\n", i);
    //     for (int j = 0; j < MEMORY_LIMIT && k < 7; j++)
    //     {
    //         printf("%d ", originalVec[k++]);
    //     }
    //     printf("\n");