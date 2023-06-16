#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABETIC_NUMBER 26

typedef struct node Node;
typedef struct head Trie;

struct node
{
    char value;
    Node *children[ALPHABETIC_NUMBER];
    int isTerminal;
};

Node *initializeNode(char value);
void freeNode(Node *node);
Node *insertNode(Node *root, char *str);
int search(Node *root, char *str);
void printTrie(Node *root);
Node *deleteNode(Node *root, char *str);
int isNodeTerminal(Node *root, char *str);
char *getLongestPrefix(Node *root, char *word);
int verify(Node *root, char *str);

int main()
{
    Node *root = initializeNode('\0');
    root = insertNode(root, "breno");
    root = insertNode(root, "matheus");
    root = insertNode(root, "mateus");
    root = insertNode(root, "lucas");

    (search(root, "emily") == 0) ? printf("Not Found!\n") : printf("Found!\n");
    (search(root, "mateus") == 0) ? printf("Not Found!\n") : printf("Found!\n");
    (search(root, "mateu") == 0) ? printf("Not Found!\n") : printf("Found!\n");
    (search(root, "luca") == 0) ? printf("Not Found!\n") : printf("Found!\n");
    (search(root, "bruno") == 0) ? printf("Not Found!\n") : printf("Found!\n");

    printTrie(root);

    printf("\n");

    root = deleteNode(root, "breno");
    printTrie(root);

    printf("\n");

    root = deleteNode(root, "mateus");
    printTrie(root);
    
    printf("\n");

    freeNode(root);

    return 0;
}

Node *initializeNode(char value)
{
    Node *newNode = malloc(sizeof(Node));
    for (int i = 0; i < ALPHABETIC_NUMBER; i++)
        newNode->children[i] = NULL;
    newNode->isTerminal = 0;
    newNode->value = value;
    return newNode;
}

void freeNode(Node *node)
{
    for (int i = 0; i < ALPHABETIC_NUMBER; i++)
    {
        if (node->children[i] != NULL)
            freeNode(node->children[i]);
        else
            continue;
    }
    free(node);
}

Node *insertNode(Node *root, char *str)
{
    Node *aux = root;

    for (int i = 0; str[i] != '\0'; i++)
    {
        int index = (int)str[i] - 'a';
        if (aux->children[index] == NULL)
            aux->children[index] = initializeNode(str[i]);
        aux = aux->children[index];
    }
    aux->isTerminal = 1;
    return root;
}

int search(Node *root, char *str)
{
    Node *temp = root;

    for (int i = 0; str[i] != '\0'; i++)
    {
        int pos = str[i] - 'a';
        if (temp->children[pos] == NULL)
            return 0;
        temp = temp->children[pos];
    }
    if (temp->isTerminal == 1 && temp != NULL)
        return 1;
    return 0;
}

void printTrie(Node *root)
{
    if (!root)
        return;
    Node *aux = root;
    printf("%c ", aux->value);
    for (int i = 0; i < ALPHABETIC_NUMBER; i++)
        printTrie(aux->children[i]);
}

Node *deleteNode(Node *root, char *str)
{
    if (!root)
        return NULL;
    if (!str || str[0] == '\0')
        return root;
    if (!isNodeTerminal(root, str))
        return root;

    Node *temp = root;

    char *longPrefix = getLongestPrefix(root, str);

    if (longPrefix[0] == '\0')
    {
        free(longPrefix);
        return root;
    }

    int i;
    for (i = 0; longPrefix[i] != '\0'; i++)
    {
        int pos = (int)longPrefix[i] - 'a';
        if (temp->children[pos] != NULL)
            temp = temp->children[pos];
        else
        {
            free(longPrefix);
            return root;
        }
    }

    int strLen = strlen(str);
    for (i; i < strLen; i++)
    {
        int position = (int)str[i] - 'a';
        if (temp->children[position])
        {
            Node *nodeToRemove = temp->children[position];
            temp->children[position] = NULL;
            freeNode(nodeToRemove);
        }
    }
    free(longPrefix);
    return root;
}

int isNodeTerminal(Node *root, char *str)
{
    Node *aux = root;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int pos = (int)str[i] - 'a';
        if (aux->children[pos])
            aux = aux->children[pos];
    }
    return aux->isTerminal;
}

char *getLongestPrefix(Node *root, char *str)
{
    if (!str || str[0] == '\0')
        return NULL;

    int strLen = strlen(str);

    char *longPrefix = malloc((strLen + 1) * sizeof(char));
    for (int i = 0; str[i] != '\0'; i++)
        longPrefix[i] = str[i];
    longPrefix[strLen] = '\0';

    int branchIndex = verify(root, longPrefix) - 1;
    if (branchIndex >= 0)
    {
        longPrefix[branchIndex] = '\0';
        longPrefix = (char *)realloc(longPrefix, (branchIndex + 1) * sizeof(char));
    }

    return longPrefix;
}

int verify(Node *root, char *str)
{
    Node *temp = root;

    int strLen = strlen(str);

    if (strLen == 0)
        return 0;

    int index = 0;
    for (int i = 0; i < strLen; i++)
    {
        int pos = str[i] - 'a';
        if (temp->children[pos])
        {
            for (int j = 0; j < ALPHABETIC_NUMBER; j++)
            {
                if (j != pos && temp->children[j])
                {
                    index = i + 1;
                    break;
                }
            }
            temp = temp->children[pos];
        }
    }
    return index;
}
