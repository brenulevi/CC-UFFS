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

#define MEMORY_LIMIT 3

// Auxiliary Functions

void externalOrder(int *sortedVec, int *originalVec, int vecLen);
void printVec(int *vec, int vecLen);

// File Functions

void openFile(FILE **file, char *filename, char *mode);
void closeFile(FILE *file);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15};
    int vecLen = sizeof(vec) / sizeof(int);
    int sortedVec[vecLen];

    externalOrder(&sortedVec, vec, vecLen);

    printVec(sortedVec, vecLen);

    return 0;
}

void externalOrder(int *sortedVec, int *originalVec, int vecLen);


void openFile(FILE **file, char *filename, char *mode)
{
    *file = fopen(filename, mode);
    if (*file == NULL)
    {
        printf("Can't open file\n");
        exit(1);
    }
}

void printVec(int *vec, int vecLen)
{
    for(int i = 0; i < vecLen; i++)
        printf("%d ", vec[i]);
    printf("\n");
}
