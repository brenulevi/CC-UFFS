#include "cobcompiler.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("compiler error: file missing\n");
        return -1;
    }
    else if (argc > 3)
    {
        printf("compiler error: only support one file\n");
        return -1;
    }

    cobcompiler(argv[1]);

    return 0;
}