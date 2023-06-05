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

FILE **createFiles(char *type);
void closeFiles(FILE **fileArray);

void test(int* vec, FILE** files, int* vecIndex, int vecLen);

void sort(int *arr);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15, 23, -2, 0, -96, 4, 50, -9, 22, 99, 1002, 10, 40, 76, 77, 70, -70, -87, -90, -99, 21, -1, 1};
    int vecLen = sizeof(vec) / sizeof(int);

    FILE **inputFiles = createFiles("input");

    int j = 0;
    
    while(j < vecLen)
        test(vec, inputFiles, &j, vecLen);

    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        fclose(inputFiles[i]);
    }

    return 0;
}

FILE **createFiles(char *type)
{
    FILE **files = malloc(MEMORY_LIMIT * sizeof(FILE *));
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char directory[30];
        sprintf(directory, "./bin/%ss/%s%d%s", type, type, i, ".txt");
        files[i] = fopen(directory, "r+");
        if (files[i] == NULL)
        {
            printf("Error to open file.");
            exit(1);
        }
    }
    return files;
}

void closeFiles(FILE **fileArray)
{
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        fclose(fileArray[i]);
    }
}

void sort(int *arr)
{
    int lower;
    for (int i = 0; i < MEMORY_LIMIT - 1; i++)
    {
        lower = i;
        for (int j = i + 1; j < MEMORY_LIMIT; j++)
        {
            if (arr[lower] > arr[j])
                lower = j;
        }
        int c = arr[i];
        arr[i] = arr[lower];
        arr[lower] = c;
    }
}

void test(int* vec, FILE** files, int* vecIndex, int vecLen)
{
    for (int nFile = 0; nFile < MEMORY_LIMIT; nFile++)
    {
        int nArray[MEMORY_LIMIT] = {0};
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            nArray[i] = (*vecIndex < vecLen) ? vec[(*vecIndex)++] : __INT32_MAX__;
        }

        sort(nArray);

        for(int i = 0; i < MEMORY_LIMIT; i++)
        {
            if(nArray[i] == __INT32_MAX__)
                break;

            if(i == MEMORY_LIMIT-1)
            {
                fprintf(files[nFile], "%d ", nArray[i]);
                continue;
            } else fprintf(files[nFile], "%d,", nArray[i]);
        }
    }
}