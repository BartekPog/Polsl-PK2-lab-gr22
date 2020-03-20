#include <stdio.h>
#include <stdlib.h>

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
        printf("ERR: Buffer overflow");
        return;
    }
    buffer->bufferData[buffer->writePosition] = value;
    buffer->writePosition = ++(buffer->writePosition) % buffer->sizeOfBuffer;
}

struct RGB readFromCircularBuffer(struct circularBuffer *buffer)
{
    if (!(buffer->bufferLength))
    {
        printf("ERR: Cannot read from empty buffer");
        struct RGB defaultPixel = {0, 0, 0};
        return defaultPixel;
    }
    int rPos = buffer->readPosition;
    buffer->readPosition = ++(buffer->readPosition) % buffer->sizeOfBuffer;
    buffer->bufferLength--;
    return buffer->bufferData[rPos];
}

void generateRandomRGBToBuffer(int numberOfValues, struct circularBuffer *buffer)
{
}

int main()
{
    struct circularBuffer buffer = CreateCircularBuffer(44);
    freeCircularBuffer(&buffer);
    return 0;
}