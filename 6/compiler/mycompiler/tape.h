#pragma once

struct tapeElement
{
    int type;
    char lexem[64];
    int line;
    struct tapeElement *next;
    struct tapeElement *prev;
};

struct tape
{
    struct tapeElement* first;
};

struct tape* initializeTape();

void addToTape(struct tape* tape, int type, const char* lexem, int line);
void shutdownTape(struct tape* tape);
