#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dfa *DFA_initialize()
{
    struct dfa *a = (struct dfa *)malloc(sizeof(struct dfa));
    a->addQIndex = 0;
    a->addSigmaIndex = 0;
    a->addFIndex = 0;
    a->q = -1;

    for (int i = 0; i < DEFAULT_MATRIX_SIZE; i++)
        for (int j = 0; j < DEFAULT_MATRIX_SIZE; j++)
            a->delta[i][j] = -1;

    return a;
}

void DFA_shutdown(struct dfa *a)
{
    free(a);
}

void DFA_addState(struct dfa *a, int state)
{
    a->Q[a->addQIndex++] = state;
}

void DFA_addAlphabetSymbol(struct dfa *a, char symbol)
{
    a->sigma[a->addSigmaIndex++] = symbol;
}

void DFA_addTransition(struct dfa *a, int fromState, int toState, char symbol)
{
    a->delta[fromState][symbol] = toState;
}

void DFA_addInitialState(struct dfa *a, int state)
{
    if (a->q != -1)
        printf("[LEXICAL] DFA warning: initial state already set, overwriting it\n");

    a->q = state;
}

void DFA_addFinalState(struct dfa *a, int state)
{
    a->F[a->addFIndex++] = state;
}

int DFA_testString(struct dfa *a, char *string, int *finalstate)
{
    int currentState = a->q;
    for (int cursor = 0; cursor < strlen(string); cursor++)
    {
        char symbol = string[cursor];

        // printf("%d -> %d\n", currentState, a->delta[currentState][symbol]);

        currentState = a->delta[currentState][symbol];
        // printf("%d\n", currentState);
        if (currentState == -1)
        {
            if (finalstate != 0)
                *finalstate = currentState;
            return 0;
        }
    }

    // verify if currentState is a final state
    for (int i = 0; i < a->addFIndex; i++)
        if (currentState == a->F[i])
        {
            if (finalstate != 0)
                *finalstate = currentState;
            return 1;
        }

    if (finalstate != 0)
        *finalstate = currentState;
    return 0;
}
