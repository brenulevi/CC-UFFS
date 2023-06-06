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

FILE **openFiles(char *type);
void closeFiles(FILE **fileArray);
void sort(int *arr);
void split(int *arr, FILE **files, int *vecIndex, int vecLen);
void merge();

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15, 23, -2, 0, -96, 4, 50, -9, 22, 99, 1002, 10, 40, 76, 77, 70, -70, -87, -90, -99, 21, -1, 1};
    int vecLen = sizeof(vec) / sizeof(int);

    FILE **inputFiles = openFiles("input");
    FILE **outputFiles = openFiles("output");

    int j = 0;
    int outputCount = 0;
    while (j < vecLen)
    {
        split(vec, inputFiles, &j, vecLen);
        outputCount++;
    }

    // merge();
    for (int k = 0; k < outputCount; k++)
    {
        int matrix[MEMORY_LIMIT][MEMORY_LIMIT];
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            if (k == 0)
                rewind(inputFiles[i]);

            for (int j = 0; j < MEMORY_LIMIT; j++)
            {
                int n = __INT32_MAX__;
                fscanf(inputFiles[i], "%d,", &n);
                matrix[i][j] = n;
            }

            fseek(inputFiles[i], 1, SEEK_CUR);
        }
        printf("\n");
    }

    closeFiles(inputFiles);

    return 0;
}

FILE **openFiles(char *type)
{
    FILE **files = malloc(MEMORY_LIMIT * sizeof(FILE *));
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char directory[30];
        sprintf(directory, ".\\bin\\%ss\\%s%d%s", type, type, i, ".txt");
        files[i] = fopen(directory, "w+");
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

void split(int *arr, FILE **files, int *vecIndex, int vecLen)
{
    // for any file
    for (int nFile = 0; nFile < MEMORY_LIMIT; nFile++)
    {
        // create an array with 5 elements from super array
        int nArray[MEMORY_LIMIT] = {0};
        int arrLen = 0;
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            if (*vecIndex < vecLen)
            {
                nArray[i] = arr[(*vecIndex)++];
                arrLen++;
            }
            else
                nArray[i] = __INT32_MAX__;
        }

        // sort it
        sort(nArray);

        // write in file
        for (int i = 0; i < arrLen; i++)
        {
            if (nArray[i] == __INT32_MAX__)
                break;

            if (i == arrLen - 1)
            {
                fprintf(files[nFile], "%d ", nArray[i]);
                continue;
            }
            else
                fprintf(files[nFile], "%d,", nArray[i]);
        }
    }
}

void merge()
{
}