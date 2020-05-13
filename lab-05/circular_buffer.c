#include "circular_buffer.h"

struct circularBuffer CreateCircularBuffer(unsigned int sizeOfBuffer)
{
    struct circularBuffer buffer = {sizeOfBuffer, 0, 0, 0, malloc(sizeof(struct machineState) * sizeOfBuffer)};
    return buffer;
}

void writeToCircularBuffer(struct circularBuffer *buffer, struct machineState value)
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

struct machineState readFromCircularBuffer(struct circularBuffer *buffer)
{
    if (!(buffer->bufferLength))
    {
        printf("ERR: Cannot read from empty buffer\n");
        struct machineState defaultRecord = {stop, 0, '\0'};
        return defaultRecord;
    }
    int rPos = buffer->readPosition;
    buffer->readPosition = (++(buffer->readPosition)) % buffer->sizeOfBuffer;
    buffer->bufferLength--;
    return buffer->bufferData[rPos];
}

void freeCircularBuffer(struct circularBuffer *buffer)
{
    free(buffer->bufferData);
}