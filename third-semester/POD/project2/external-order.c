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
#include <math.h>

#define MEMORY_LIMIT 5

#if defined(_WIN32)
#define PLATFORM "windows"
#elif defined(__unix__)
#define PLATFORM "linux"
#endif

void externalSort(FILE **inputFiles, FILE **outputFiles, int *vec, int vecLen, int tradeFlag);
FILE **openFiles(char *type);
void closeFiles(FILE **fileArray);
void sort(int *arr);
void split(int *arr, FILE **files, int *vecIndex, int vecLen);
int lowest(int *arr);
int hasNumber(int *arr);
void invertFiles(FILE **outputFile, FILE **inputFile);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15, 23, -2, 0, -96, 4, 50, -9, 22, 99, 1002, 10, 40, 76, 77, 70, -70, -87, -90, -99, 21, -1, 1};
    int vecLen = sizeof(vec) / sizeof(int);

    FILE **inputFiles = openFiles("input");
    FILE **outputFiles = openFiles("output");

    int tradeNumber = ((int)ceil(sqrt(vecLen))) % MEMORY_LIMIT;
    int trades = 0;

    externalSort(inputFiles, outputFiles, vec, vecLen, trades);
    trades++;
    invertFiles(outputFiles, inputFiles);
    externalSort(inputFiles, outputFiles, vec, vecLen, trades);

    closeFiles(inputFiles);
    closeFiles(outputFiles);

    return 0;
}

FILE **openFiles(char *type)
{
    FILE **files = malloc(MEMORY_LIMIT * sizeof(FILE *));
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char directory[30];

        if (strcmp(PLATFORM, "linux") == 0)
            sprintf(directory, "./bin/%ss/%s%d%s", type, type, i, ".txt");
        else
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
                fprintf(files[nFile], ",%d, ", nArray[i]);
                continue;
            }
            else
                fprintf(files[nFile], ",%d", nArray[i]);
        }
    }
}

int lowest(int *arr)
{
    int lower = 0;
    for (int i = 1; i < MEMORY_LIMIT; i++)
    {
        if (arr[i] < arr[lower])
            lower = i;
    }

    return lower;
}

int hasNumber(int *arr)
{
    int flag = 0;
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        if (arr[i] != __INT32_MAX__)
            return 1;
    }
    return flag;
}

void externalSort(FILE **inputFiles, FILE **outputFiles, int *vec, int vecLen, int tradeFlag)
{
    int outputCount = 0;
    int j = 0;
    printf("%d\n", tradeFlag);
    if (tradeFlag == 0)
    {
        while (j < vecLen)
        {
            split(vec, inputFiles, &j, vecLen);
            outputCount++;
        }
    }
    else
        outputCount = 1;

    for (int k = 0; k < outputCount; k++)
    {
        int arr[MEMORY_LIMIT];
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            if (k == 0)
                fseek(inputFiles[i], 1, SEEK_SET);

            fscanf(inputFiles[i], "%d,", &arr[i]);
            printf("%d ", arr[i]);
        }
        printf("\n");
        while (hasNumber(arr) == 1)
        {
            int lowestIndex = lowest(arr);
            fprintf(outputFiles[k], ",%d", arr[lowestIndex]);
            int n;
            arr[lowestIndex] = (fscanf(inputFiles[lowestIndex], "%d,", &n) == 1) ? n : __INT32_MAX__;
        }

        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            fseek(inputFiles[i], 1, SEEK_CUR);
        }
    }

    for (int i = 0; i < outputCount; i++)
    {
        fprintf(outputFiles[i], ",");
    }
}

void invertFiles(FILE **outputFiles, FILE **inputFiles)
{
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        rewind(inputFiles[i]);
        rewind(outputFiles[i]);

        char directory[30];

        if (strcmp(PLATFORM, "linux") == 0)
            sprintf(directory, "./bin/inputs/input%d%s", i, ".txt");
        else
            sprintf(directory, ".\\bin\\inputs\\input%d%s", i, ".txt");

        fclose(fopen(directory, "w"));

        char c;
        while ((c = fgetc(outputFiles[i])) != EOF)
        {
            fprintf(inputFiles[i], "%c", c);
        }

        if (strcmp(PLATFORM, "linux") == 0)
            sprintf(directory, "./bin/outputs/output%d%s", i, ".txt");
        else
            sprintf(directory, ".\\bin\\outputs\\output%d%s", i, ".txt");

        fclose(fopen(directory, "w"));

        inputFiles[i] = fopen(directory, "w+");
        outputFiles[i] = fopen(directory, "w+");

        rewind(inputFiles[i]);
        rewind(outputFiles[i]);
    }
}