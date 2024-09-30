#include "cobcompiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dfa.h"
#include "tape.h"

int lexical(FILE *file, struct tape *tape);
void lexical_fillAutomata(struct dfa *automata);

void cobcompiler(char *filename)
{
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        printf("compiler error: source not found\n");
        return;
    }

    // initialize tape
    struct tape *tape = initializeTape();

    // lexical
    if (!lexical(file, tape))
        return;

    // sintatic
    // semantic

    // end
    shutdownTape(tape);
}

int isOperator(char c)
{
    if (c == '+' || c == ';' || c == '-' || c == ':' || c == '*' || c == '/' ||
        c == '(' || c == ')' || c == '%')
        return 1;
    return 0;
}

int lexical(FILE *file, struct tape *tape)
{
    // initialize automata
    struct dfa *automata = DFA_initialize();
    lexical_fillAutomata(automata);

    int successful = 1;

    // read file, fill tape and symbol table
    char str[64];
    int index = 0;
    int line = 1;
    while (!feof(file))
    {
        char c = fgetc(file);

        if (c == ' ')
            continue;
        else if (c == '\n')
        {
            line++;
            continue;
        }
        else if (isOperator(c))
            str[index++] = c;
        else if (c == '>' || c == '<')
        {
            str[index++] = c;
            c = fgetc(file);
            if(c == '=')
                str[index++] = c;
            else
                fseek(file, -1, SEEK_CUR);
        }
        else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
        {
            str[index++] = c;
            c = fgetc(file);
            if (c != EOF)
                fseek(file, -1, SEEK_CUR);
            if (!isOperator(c) && c != '<' && c != '>'  && c != ' ' && c != '\n' && c != EOF)
                continue;
        }
        else
        {
            str[index++] = c;
        }

        str[index] = '\0';
        index = 0;

        int finalState;
        if (DFA_testString(automata, str, &finalState))
        {
            // send to tape
            addToTape(tape, finalState, str, line);
        }
        else
        {
            printf("LEXICAL ERROR [line: %d, lexem: %s]\n", line, str);
            successful = 0;
        }
    }
    
    addToTape(tape, 50, "$", line);

    // for (struct tapeElement *aux = tape->first; aux != NULL; aux = aux->next)
    // {
    //     printf("%d %s %d\n", aux->type, aux->lexem, aux->line);
    // }

    DFA_shutdown(automata);
    return successful;
}

void lexical_fillAutomata(struct dfa *automata)
{
    for (int i = 0; i < 43; i++)
        DFA_addState(automata, i);

    for (int i = 1; i < 26; i++)
        DFA_addFinalState(automata, i);
    DFA_addFinalState(automata, 26);
    DFA_addFinalState(automata, 34);
    DFA_addFinalState(automata, 33);
    DFA_addFinalState(automata, 37);
    DFA_addFinalState(automata, 27);
    DFA_addFinalState(automata, 39);
    DFA_addFinalState(automata, 28);
    DFA_addFinalState(automata, 29);
    DFA_addFinalState(automata, 40);
    DFA_addFinalState(automata, 30);
    DFA_addFinalState(automata, 31);
    DFA_addFinalState(automata, 32);
    DFA_addFinalState(automata, 35);
    DFA_addFinalState(automata, 36);
    DFA_addFinalState(automata, 19);
    DFA_addFinalState(automata, 20);
    DFA_addFinalState(automata, 41);
    DFA_addFinalState(automata, 42);

    DFA_addInitialState(automata, 0);

    for (int i = 32; i < 128; i++)
        DFA_addAlphabetSymbol(automata, (char)i);

    // add transitions
    DFA_addTransition(automata, 0, 1, 'v');
    DFA_addTransition(automata, 1, 2, 'a');
    DFA_addTransition(automata, 2, 26, 'r');

    DFA_addTransition(automata, 0, 3, 'i');
    DFA_addTransition(automata, 3, 4, 'n');
    DFA_addTransition(automata, 4, 26, 't');

    DFA_addTransition(automata, 0, 5, 'b');
    DFA_addTransition(automata, 5, 6, 'e');
    DFA_addTransition(automata, 6, 7, 'g');
    DFA_addTransition(automata, 7, 8, 'i');
    DFA_addTransition(automata, 8, 26, 'n');

    DFA_addTransition(automata, 0, 9, 'p');
    DFA_addTransition(automata, 9, 10, 'r');
    DFA_addTransition(automata, 10, 11, 'o');
    DFA_addTransition(automata, 11, 12, 'g');
    DFA_addTransition(automata, 12, 13, 'r');
    DFA_addTransition(automata, 13, 14, 'a');
    DFA_addTransition(automata, 14, 26, 'm');

    DFA_addTransition(automata, 3, 26, 'f');

    DFA_addTransition(automata, 0, 16, 't');
    DFA_addTransition(automata, 16, 17, 'h');
    DFA_addTransition(automata, 17, 18, 'e');
    DFA_addTransition(automata, 18, 26, 'n');

    DFA_addTransition(automata, 0, 21, 'e');
    DFA_addTransition(automata, 21, 22, 'l');
    DFA_addTransition(automata, 22, 23, 's');
    DFA_addTransition(automata, 23, 26, 'e');

    DFA_addTransition(automata, 21, 25, 'n');
    DFA_addTransition(automata, 25, 26, 'd');

    // add to all keyword states ascii letters and numbers
    for (int i = 1; i < 27; i++)
    {
        for (int j = 65; j < 91; j++)
        {
            // verify if for this states i and symbol j already has a transition
            if (automata->delta[i][j + 32] != -1)
                continue;

            // if not, add transition for all uppercase and lowercase letters to all keyword states to 28 [0..26]->28
            DFA_addTransition(automata, i, 28, j);
            DFA_addTransition(automata, i, 28, j + 32);
        }

        // add all char numbers
        for (int j = 48; j < 58; j++)
        {
            DFA_addTransition(automata, i, 28, j);
            DFA_addTransition(automata, 28, 28, j);
            DFA_addTransition(automata, 38, 38, j);
            DFA_addTransition(automata, 0, 27, j);
            DFA_addTransition(automata, 27, 27, j);
        }

        // add '_' to all keyword states to 28
        DFA_addTransition(automata, i, 28, '_');
    }

    // add ascii letters 0 - 28 / 28 - 28
    for (int i = 65; i < 91; i++)
    {
        // add all uppercase letters 0->28
        DFA_addTransition(automata, 0, 28, i);

        // add all uppercas and lowercase letters - 28->28
        DFA_addTransition(automata, 28, 28, i);
        DFA_addTransition(automata, 28, 28, i + 32);

        DFA_addTransition(automata, 38, 38, i);
        DFA_addTransition(automata, 38, 38, i + 32);

        // filter all keyword states that begin with this letters
        if (i + 32 == 'v' || i + 32 == 'i' || i + 32 == 'b' || i + 32 == 'p' || i + 32 == 't' || i + 32 == 'e')
            continue;

        // add all lowercase letters 0->28
        DFA_addTransition(automata, 0, 28, i + 32);
    }

    // auto transition state 28 via '_'
    DFA_addTransition(automata, 28, 28, '_');

    // add operations
    DFA_addTransition(automata, 0, 29, '>');
    DFA_addTransition(automata, 29, 40, '=');
    DFA_addTransition(automata, 0, 30, ';');
    DFA_addTransition(automata, 0, 42, ':');
    DFA_addTransition(automata, 0, 31, '<');
    DFA_addTransition(automata, 31, 32, '=');
    DFA_addTransition(automata, 0, 35, '=');
    DFA_addTransition(automata, 0, 36, '%');
    DFA_addTransition(automata, 0, 37, '+');
    DFA_addTransition(automata, 0, 33, '(');
    DFA_addTransition(automata, 0, 34, ')');
    DFA_addTransition(automata, 0, 19, '-');
    DFA_addTransition(automata, 0, 20, '*');
    DFA_addTransition(automata, 0, 41, '/');

    // add literals
    DFA_addTransition(automata, 0, 38, '"');
    DFA_addTransition(automata, 38, 39, '"');
}
