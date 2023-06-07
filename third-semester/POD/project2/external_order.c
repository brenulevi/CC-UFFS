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

void sort(int *arr);
int lowest(int *arr);
int hasNumber(int *arr);

int main()
{
    int vec[] = {30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
    int vecLen = sizeof(vec) / sizeof(int);

    FILE *inputFiles[MEMORY_LIMIT];
    FILE *outputFiles[MEMORY_LIMIT];

    // Open input and output files
    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        char inputDirectory[30];
        char outputDirectory[30];

        if (strcmp(PLATFORM, "windows") == 0)
        {
            sprintf(inputDirectory, ".\\bin\\inputs\\input%d.txt", i);
            sprintf(outputDirectory, ".\\bin\\outputs\\output%d.txt", i);
        }
        else
        {
            sprintf(inputDirectory, "./bin/inputs/input%d.txt", i);
            sprintf(outputDirectory, "./bin/outputs/output%d.txt", i);
        }

        inputFiles[i] = fopen(inputDirectory, "w+");
        outputFiles[i] = fopen(outputDirectory, "w+");
    }

    // Get number vector and split into input files
    int vecIndex = 0;

    while (vecIndex < vecLen)
    {
        // for any file
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            // create an array with 5 elements from super array
            int arr[MEMORY_LIMIT] = {0};
            int arrActualLen = 0;
            for (int j = 0; j < MEMORY_LIMIT; j++)
            {
                if (vecIndex < vecLen)
                {
                    arr[j] = vec[(vecIndex)++];
                    arrActualLen++;
                }
                else
                    arr[j] = __INT32_MAX__;
            }

            // sort it
            sort(arr);

            // write in file
            for (int j = 0; j < arrActualLen; j++)
            {
                if (arr[j] == __INT32_MAX__)
                    break;

                if (j == arrActualLen - 1)
                {
                    fprintf(inputFiles[i], ",%d, ", arr[j]);
                    continue;
                }
                else
                    fprintf(inputFiles[i], ",%d", arr[j]);
            }
        }
    }

    // Merge all input files in output file
    int outputCount = ((int)ceil(sqrt(vecLen)) % 5) + 1;

    for (int k = 0; k < outputCount; k++)
    {
        int arr[MEMORY_LIMIT];
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            if (k == 0)
                fseek(inputFiles[i], 1, SEEK_SET);

            fscanf(inputFiles[i], "%d,", &arr[i]);
        }
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

    outputCount--;

    for (int i = 0; i < MEMORY_LIMIT; i++)
    {
        rewind(inputFiles[i]);
        rewind(outputFiles[i]);
    }

    for (int k = 0; k < outputCount; k++)
    {
        int arr[MEMORY_LIMIT];
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            arr[i] = __INT32_MAX__;
        }
        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            fseek(outputFiles[i], 1, SEEK_SET);
            fscanf(outputFiles[i], "%d,", &arr[i]);
        }
        while (hasNumber(arr) == 1)
        {
            int lowestIndex = lowest(arr);
            fprintf(inputFiles[k], ",%d", arr[lowestIndex]);
            int n;
            arr[lowestIndex] = (fscanf(outputFiles[lowestIndex], "%d,", &n) == 1) ? n : __INT32_MAX__;
        }

        for (int i = 0; i < MEMORY_LIMIT; i++)
        {
            fseek(outputFiles[i], 1, SEEK_CUR);
        }
    }

    for (int i = 0; i < outputCount; i++)
    {
        fprintf(inputFiles[i], ",");
    }

    // Get final array in input0.txt
    int farr[vecLen];
    int farrActualLen = 0;

    fseek(inputFiles[0], 1, SEEK_SET);

    while(farrActualLen < vecLen)
    {
        fscanf(inputFiles[0], "%d,", &farr[farrActualLen++]);
    }

    printf("Initial array:\n");
    for(int i = 0; i < vecLen; i++)
    {
        printf("%d ", vec[i]);
    }
    printf("\nSorted array:\n");
    for(int i = 0; i < vecLen; i++)
    {
        printf("%d ", farr[i]);
    }
    printf("\n");

    return 0;
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