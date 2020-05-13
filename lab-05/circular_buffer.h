
#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include <stdlib.h>
#include <stdio.h>

#include "states.h"

struct circularBuffer
{
    unsigned int sizeOfBuffer;       // Buffer size
    int bufferLength;                // 0 number of values to read
    int readPosition;                // 0 write position
    int writePosition;               // 0 read position
    struct machineState *bufferData; // Bufffer data
};

/**
 * @brief Creates a circular buffer object
 * 
 * @param sizeOfBuffer desired size of buffer
 * @return struct circularBuffer pointer to the newly created buffer
 */
struct circularBuffer CreateCircularBuffer(unsigned int sizeOfBuffer);

/**
 * @brief Writes one value to circular buffer
 * 
 * @param buffer pointer to the buffer
 * @param value value to save in buffer
 */
void writeToCircularBuffer(struct circularBuffer *buffer, struct machineState value);

/**
 * @brief Reads one value from the circular buffer
 * 
 * @param buffer pointer to the buffer
 * @return struct machineState 
 */
struct machineState readFromCircularBuffer(struct circularBuffer *buffer);

/**
 * @brief Free the memory taken by buffer
 * 
 * @param buffer 
 */
void freeCircularBuffer(struct circularBuffer *buffer);

#endif