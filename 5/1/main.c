#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tableData
{
    int id;
    char logical_name[20];
    char physical_name[20];
};

struct attData
{
    int id;
    char att_name[20];
    char type;
    char mandatory;
    int size;
};

void readFile(char* str, int len);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::ARGUMENT INVALID\n");
        return -1;
    }

    readFile(argv[1], strlen(argv[1]));

    return 0;
}

void readFile(char* str, int len)
{
    FILE* table;
    table = fopen("table.dic", "r");

    struct tableData td;

    while(1)
    {
        fread(&td, sizeof(td), 1, table);

        if(feof(table))
        {
            printf("NO TABLE FOUND\n");
            return;
        }

        if(strcmp(str, td.logical_name) == 0)
            break;
    }

    fclose(table);

    // printf("%d\n%s\n%s\n", td.id, td.logical_name, td.physical_name);

    FILE* att;
    att = fopen("att.dic", "r");

    fseek(att, 0, SEEK_END);
    long int fileLen = ftell(att);
    fseek(att, 0, SEEK_SET);

    struct attData *arr = malloc(fileLen);
    struct attData aux;

    int count = 0;

    while(1)
    {
        fread(&aux, sizeof(aux), 1, att);

        if(feof(att))
            break;

        if(aux.id == td.id)
        {
            arr[count++] = aux;
            // printf("%d\n%s\n%c\n%d\n%d\n\n", arr[count].id, arr[count].att_name, arr[count].type, arr[count].mandatory, arr[count].size);
        }
    }

    fclose(att);

    FILE* dat;
    dat = fopen(td.physical_name, "r");

    
}