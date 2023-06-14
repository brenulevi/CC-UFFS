#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABETIC_NUMBER 26

typedef struct node
{
    char value;
    int isTerminal;
    struct node *childs[26];
} Node;

typedef struct trie
{
    struct node *childs[26];
} Trie;

void initialize(Trie *head);
void insertNode();
void completeSearch();
void partialSearch();
void removeNode();
void printChilds();

int main()
{
    Trie myTrie;
    initialize(&myTrie);
    printChilds(&myTrie);
    return 0;
}

void initialize(Trie *head)
{
    for (int i = 0; i < ALPHABETIC_NUMBER; i++)
    {
        head->childs[i] = NULL;
    }
}

void insertNode(Trie *head, char *strValue)
{
    for (int i = 0; i < strlen(strValue); i++)
    {
        
    }
}

void completeSearch()
{
}

void partialSearch()
{
}

void removeNode()
{
}

void printChilds(Trie *head)
{
    for (int i = 0; i < ALPHABETIC_NUMBER; i++)
    {
        if (head->childs[i] == NULL)
            printf("NULL ");
        else
            printf("%c ", head->childs[i]->value);
    }
    printf("\n");
}
