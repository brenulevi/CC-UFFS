#pragma once

// states Q
// alphabet Σ
// transitions δ
// initial state q
// final states F

#define DEFAULT_ARRAY_SIZE 128
#define DEFAULT_MATRIX_SIZE 128

struct dfa
{
    int Q[DEFAULT_ARRAY_SIZE];
    char sigma[DEFAULT_ARRAY_SIZE];
    int delta[DEFAULT_MATRIX_SIZE][DEFAULT_MATRIX_SIZE];
    int q;
    int F[DEFAULT_ARRAY_SIZE];

    // variable controls
    unsigned int addQIndex;
    unsigned int addSigmaIndex;
    unsigned int addFIndex;
};

struct dfa *DFA_initialize();
void DFA_shutdown(struct dfa *a);

void DFA_addState(struct dfa *a, int state);
void DFA_addAlphabetSymbol(struct dfa *a, char symbol);
void DFA_addTransition(struct dfa *a, int fromState, int toState, char symbol);
void DFA_addInitialState(struct dfa *a, int state);
void DFA_addFinalState(struct dfa *a, int state);

int DFA_testString(struct dfa *a, char *string, int *finalstate);
