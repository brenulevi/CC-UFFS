#include <stdio.h>
#include <string.h>

int greater(int *pontuation) {
    int grtr;
    for(int i = 1; i < 3; i++) {
        if(pontuation[i-1] > pontuation[i])
            grtr = i-1;
    }
    return grtr;
}

int main()
{
    const int ascii = 65;
    int pont[4] = {0, 0, 0, 0};

    char team1[1];
    char team2[1];
    while(1)
    {
        printf("Time: ");
        scanf("%s", team1);

        if(strcmp(team1, "A") != 0 && strcmp(team1, "B") != 0 && strcmp(team1, "C") != 0 && strcmp(team1, "D") != 0)
            break;
        
        int score1;
        printf("Gols: ");
        scanf("%d", &score1);

        printf("Time: ");
        scanf("%s", team2);

        int score2;
        printf("Gols: ");
        scanf("%d", &score2);

        if(score1 > score2) {
            pont[team1[0]-ascii] += 3;
        } else if (score1 == score2) {
            pont[team1[0]-ascii] += 1;
            pont[team2[0]-ascii] += 1;
        } else {
            pont[team2[0]-ascii] += 3;
        }
    }

    int index = greater(pont);
    
    printf("Campeao: %c\n", index+ascii);

    for(int i = 0; i < 4; i++)
    {
        printf("%c: %d pontos\n", i+ascii, pont[i]);
    }

    return 0;
}

// Complexidade: N