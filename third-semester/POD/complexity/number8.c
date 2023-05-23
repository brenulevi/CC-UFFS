#include <stdio.h>

int main()
{
    int antony = 150, growth_antony = 2;
    int carl = 110, growth_carl = 3;
    int time = 0;

    while(antony != carl) 
    {
        antony += growth_antony;
        carl += growth_carl;

        time++;
    }

    printf("%d\n", time);

    return 0;
}