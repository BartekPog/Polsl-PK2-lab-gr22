/** @file*/

#include "document.h"

#define HEADER_SIZE 300

struct docArray *createDocArrayFromFile(FILE *fileStream)
{
    int numberOfElements;
    struct docLinkedListElem *docListHead = createDocListFromFile(fileStream, &numberOfElements);

    struct docArray *documents = malloc(sizeof(struct docArray));

    documents->size = numberOfElements;

    documents->documentPointers = malloc(sizeof(struct document *) * numberOfElements);

    for (int i = 0; i < numberOfElements; i++)
    {
        struct document *currentDocPtr = docListHead->docPtr;
        documents->documentPointers[i] = currentDocPtr;

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
    while (character = getc(fileStream) != EOF)
    {
        if (character != (int)'"')
            continue;

        char *articleHeader = malloc(sizeof(char) * HEADER_SIZE);
        char *headerEnd = articleHeader;

        while (character = getc(fileStream) != (int)'"')
        {
            *headerEnd = (char)character;
            headerEnd++;
        }
        headerEnd = '\0';

        if ((getc(fileStream) != (int)',') || (getc(fileStream) != (int)'"'))
            continue;

        fpos_t startPos;
        fgetpos(fileStream, &startPos);

        while (getc(fileStream) != (int)'"')
            ; // Reading the article

        fpos_t endPos;
        fgetpos(fileStream, &endPos);

        struct document *doc = malloc(sizeof(struct document));

        doc->header = articleHeader;
        doc->startPos = startPos;
        doc->endPos = endPos;

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