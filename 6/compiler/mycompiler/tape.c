#include "tape.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct tape *initializeTape()
{
    struct tape *tape = (struct tape *)malloc(sizeof(struct tape));
    tape->first = NULL;
}

// add to end of list
void addToTape(struct tape *tape, int type, const char *lexem, int line)
{
    struct tapeElement *element = (struct tapeElement *)malloc(sizeof(struct tapeElement));
    element->line = line;
    element->type = type;
    element->next = NULL;
    element->prev = NULL;
    strcpy(element->lexem, lexem);

    if (tape->first == NULL)
    {
        tape->first = element;
        return;
    }

    struct tapeElement *aux;
    for (aux = tape->first; aux != NULL; aux = aux->next)
    {
        if (aux->next == NULL)
        {
            aux->next = element;
            element->prev = aux;
            break;
        }
    }
}

void shutdownTape(struct tape *tape)
{
    struct tapeElement *aux;
    while(tape->first != NULL)
    {
        aux = tape->first;
        tape->first = tape->first->next;
        free(aux);
    }

    free(tape);
}
