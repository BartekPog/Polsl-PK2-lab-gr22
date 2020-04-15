/** @file*/

#include "document.h"

#define HEADER_SIZE 1000

struct docArray *createDocArrayFromFile(FILE *fileStream)
{
    int numberOfElements;

    struct docLinkedListElem *docListHead = createDocListFromFile(fileStream, &numberOfElements);
    printf("Found %d documents\n", numberOfElements);

    struct docArray *documents = malloc(sizeof(struct docArray));

    documents->size = numberOfElements;

    documents->documentPointers = malloc(sizeof(struct document *) * numberOfElements);

    for (int i = 0; i < numberOfElements; i++)
    {
        struct document *currentDocPtr = docListHead->docPtr;
        (documents->documentPointers)[i] = currentDocPtr;

        struct docLinkedListElem *pDocList = docListHead->pNext;
        free(docListHead);
        docListHead = pDocList;
    }

    return documents;
}

struct docLinkedListElem *createDocListFromFile(FILE *fileStream, int *numberOfElements)
{
    struct docLinkedListElem *pHead = NULL;
    *numberOfElements = 0;

    int character;
    while ((character = getc(fileStream)) != EOF)
    {
        if (character != (int)'"')
            continue;

        char *articleHeader = malloc(sizeof(char) * HEADER_SIZE);
        char *headerEnd = articleHeader;

        character = getc(fileStream);
        while (character != (int)'"')
        {
            *headerEnd = (char)character;
            headerEnd++;
            character = getc(fileStream);
        }
        *headerEnd = '\0';

        if ((getc(fileStream) != (int)',') || (getc(fileStream) != (int)'"'))
            continue;

        fpos_t startPos;
        fgetpos(fileStream, &startPos);

        int lenght = 0;

        while (getc(fileStream) != (int)'"')
            lenght++; // Reading the article

        struct document *doc = malloc(sizeof(struct document));

        doc->header = articleHeader;
        doc->startPos = startPos;
        doc->lenght = lenght;

        addDocToDocListHead(&pHead, doc);
        (*numberOfElements)++;
    }

    return pHead;
}

void addDocToDocListHead(struct docLinkedListElem **pHeadPointer, struct document *doc)
{
    struct docLinkedListElem *newElem = malloc(sizeof(struct docLinkedListElem));

    newElem->docPtr = doc;
    newElem->pNext = *pHeadPointer;

    *pHeadPointer = newElem;
}

void deleteDocArray(struct docArray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        free(array->documentPointers[i]->header);
        free(array->documentPointers[i]);
    }
    free(array);
}

void printDocument(FILE *fileStream, struct document *doc)
{

    printf("\n %s \n", doc->header);
    fpos_t pos = doc->startPos;

    fsetpos(fileStream, &pos);

    for (int i = 0; i < doc->lenght; i++)
        putc(getc(fileStream), stdout);

    printf("\n");
    return;
}