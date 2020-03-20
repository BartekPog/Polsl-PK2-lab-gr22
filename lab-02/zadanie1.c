#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUF_SIZE 1000
#define NUMBER_OF_PIXELS 800
#define COLOR 'r'
#define BORDER 50

struct RGB
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct circularBuffer
{
    const unsigned int sizeOfBuffer; // Pojemność bufora
    int bufferLength;                // 0 ilość aktualnie zaalokowanych wartości
    int readPosition;                // 0 pozycha zapisu
    int writePosition;               // 0 pozycja wczytu
    struct RGB *bufferData;
};

struct pixelArray
{
    int size;
    struct RGB *data;
};

struct doublyLinkedListElement
{
    struct doublyLinkedListElement *pPrev;
    struct doublyLinkedListElement *pNext;
    struct RGB value;
};

struct doublyLinkedList
{
    struct doublyLinkedListElement *pHead;
    struct doublyLinkedListElement *pTail;
};

struct circularBuffer CreateCircularBuffer(unsigned int sizeOfBuffer)
{
    struct circularBuffer buffer = {sizeOfBuffer, 0, 0, 0, malloc(sizeof(struct RGB) * sizeOfBuffer)};
    return buffer;
}

void freeCircularBuffer(struct circularBuffer *buffer)
{
    free(buffer->bufferData);
}

void writeToCircularBuffer(struct circularBuffer *buffer, struct RGB value)
{
    if (buffer->bufferLength >= buffer->sizeOfBuffer)
    {
        printf("ERR: Buffer overflow\n");
        return;
    }
    buffer->bufferData[buffer->writePosition] = value;
    buffer->writePosition = (++(buffer->writePosition)) % buffer->sizeOfBuffer;
    buffer->bufferLength++;
}

struct RGB readFromCircularBuffer(struct circularBuffer *buffer)
{
    if (!(buffer->bufferLength))
    {
        printf("ERR: Cannot read from empty buffer\n");
        struct RGB defaultPixel = {0, 0, 0};
        return defaultPixel;
    }
    int rPos = buffer->readPosition;
    buffer->readPosition = (++(buffer->readPosition)) % buffer->sizeOfBuffer;
    buffer->bufferLength--;
    return buffer->bufferData[rPos];
}

struct RGB randomRGB()
{
    struct RGB pixel = {rand() % 255, rand() % 255, rand() % 255};
    return pixel;
}

void generateRandomRGBToBuffer(struct circularBuffer *buffer, int numberOfValues)
{
    srand(time(NULL));
    for (int i = 0; i < numberOfValues; i++)
    {
        writeToCircularBuffer(buffer, randomRGB());
    }
}

struct pixelArray CreatePixelArrayFromBuffer(struct circularBuffer *buffer)
{
    struct pixelArray array = {buffer->bufferLength, malloc(sizeof(struct RGB) * buffer->bufferLength)};
    for (int i = 0; i < array.size; i++)
    {
        array.data[i] = readFromCircularBuffer(buffer);
    }

    return array;
}

void freePixelArray(struct pixelArray *array)
{
    free(array->data);
}

struct doublyLinkedList CreateDoublyLinkedList()
{
    struct doublyLinkedList list;
    list.pHead = NULL;
    list.pTail = NULL;
    return list;
}

void recursionalDLLfree(struct doublyLinkedListElement *pHead)
{
    if (pHead)
    {
        recursionalDLLfree(pHead->pNext);
        free(pHead);
    }
}

void freeDoublyLinkedList(struct doublyLinkedList *list)
{
    recursionalDLLfree(list->pHead);
    list->pHead = list->pTail = NULL;
}

void addToListHead(struct doublyLinkedList *list, struct RGB value)
{
    if (list->pHead == NULL)
    {
        list->pHead = list->pTail = malloc(sizeof(struct doublyLinkedListElement));
        *(list->pHead) = (struct doublyLinkedListElement){NULL, NULL, value};
    }
    else
    {
        list->pHead->pPrev = malloc(sizeof(struct doublyLinkedListElement));
        *(list->pHead->pPrev) = (struct doublyLinkedListElement){0, list->pHead, value};
        list->pHead = list->pHead->pPrev;
    }
}

unsigned char getRGBValue(struct RGB pixel, char color)
{
    switch (color)
    {
    case 'R':
    case 'r':
        return pixel.R;
    case 'G':
    case 'g':
        return pixel.G;
    case 'B':
    case 'b':
        return pixel.B;
    }
    printf("ERR: %c is not a Valid pixel color\n", color);
    return 0;
}

int fillDoublyLinkedListFromPixelArrayAndCountHigher(struct doublyLinkedList *list, struct pixelArray *array, char color, unsigned char minBorder)
{
    int higherThanBorder = 0;
    for (int i = 0; i < array->size; i++)
    {
        addToListHead(list, array->data[i]);

        if (getRGBValue(array->data[i], color) > minBorder)
            higherThanBorder++;
    }
    return higherThanBorder;
}
int fillDoublyLinkedListFromPixelArrayAndCountHigherWithRAMArithmetics(struct doublyLinkedList *list, struct pixelArray *array, char color, unsigned char minBorder)
{
    int higherThanBorder = 0;
    struct RGB *ptr = array->data;
    for (struct RGB *ptr = array->data; ptr < array->data + array->size; ptr++)
    {
        addToListHead(list, *ptr);

        if (getRGBValue(*ptr, color) > minBorder)
            higherThanBorder++;
    }
    return higherThanBorder;
}

int main()
{
    struct circularBuffer buffer = CreateCircularBuffer(MAX_BUF_SIZE);

    generateRandomRGBToBuffer(&buffer, NUMBER_OF_PIXELS);

    struct pixelArray array = CreatePixelArrayFromBuffer(&buffer);

    struct doublyLinkedList list = CreateDoublyLinkedList();

    // int higherThanBorder = fillDoublyLinkedListFromPixelArrayAndCountHigher(&list, &array, COLOR, BORDER);
    int higherThanBorder = fillDoublyLinkedListFromPixelArrayAndCountHigherWithRAMArithmetics(&list, &array, COLOR, BORDER);
    printf("There are %d pixels of given color (%c) higher than given border (%d)\n", higherThanBorder, COLOR, BORDER);

    freeDoublyLinkedList(&list);
    freeCircularBuffer(&buffer);
    freePixelArray(&array);
    return 0;
}