#include "task1_table.h"

int encode(char c)
{
    return (int)(unsigned char)(c);
}

char decode(unsigned char c)
{
    return (char)(c);
}

struct indexList **initIndexListTable()
{
    struct indexList **table = calloc(UCHAR_MAX + 1, sizeof(struct indexList *));
    return table;
}

void addOccurence(struct indexList **table, char c, int index)
{
    struct indexList *newElem = malloc(sizeof(struct indexList));

    newElem->index = index;

    newElem->pNext = table[encode(c)];
    table[encode(c)] = newElem;
}

void saveStringToTable(struct indexList **table, char *str)
{
    for (int i = 0; i < strlen(str); i++)
        addOccurence(table, str[i], i);
}

int getNumberOfOccurences(struct indexList **table, char c)
{
    struct indexList *head = table[encode(c)];

    int occurences = 0;

    while (head)
    {
        occurences++;
        head = head->pNext;
    }
    return occurences;
}

int getMinDistance(struct indexList **table, char c)
{
    struct indexList *head = table[encode(c)];

    if ((!head) || (!(head->pNext)))
        return -1;

    int first = head->index;

    head = head->pNext;
    int second = head->index;

    int min = abs(first - second);

    head = head->pNext;
    while (head)
    {
        first = second;
        second = head->index;
        min = MIN(min, abs(first - second));
        head = head->pNext;
    }
    return min;
}

int getMaxDistance(struct indexList **table, char c)
{
    struct indexList *head = table[encode(c)];

    if ((!head) || (!(head->pNext)))
        return -1;

    int first = head->index;

    while (head->pNext)
        head = head->pNext;

    return abs(first - head->index);
}

void freeIndexesTable(struct indexList **table)
{
    struct indexList *pRunner, *pSub;

    for (int i = 0; i < UCHAR_MAX; i++)
    {
        pRunner = table[i];

        while (pRunner)
        {
            pSub = pRunner->pNext;
            free(pRunner);
            pRunner = pSub;
        }
    }
    free(table);
}