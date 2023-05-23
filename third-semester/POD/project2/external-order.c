#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_LIMIT 3

void openFile(FILE** file, char* filename, char* mode);
void closeFile(FILE* file);

int main()
{
    int vec[] = {30, 21, 43, 3, 9, 82, 15};
    FILE* file;

    for(int i = 0; i < MEMORY_LIMIT; i++)
    {
        char str[100];
        sprintf(str, "%s%d%s", "input", i, ".txt");
        openFile(&file, str, "wt");
    }

    return 0;
}

void openFile(FILE** file, char* filename, char* mode)
{
    *file = fopen(filename, mode);
    if(*file == NULL)
    {
        printf("Can't open file\n");
        exit(1);
    }
}
