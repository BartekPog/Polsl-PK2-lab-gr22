#ifndef OUTPUT
#define OUTPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "states.h"
#include "circular_buffer.h"

/**
 * @brief Get the State as newly alocated string
 * 
 * @param state 
 * @return char* 
 */
char *getStateString(enum machineStateCase state);

/**
 * @brief Displays the state to outStream
 * 
 * @param outStream 
 * @param state 
 */
void showState(FILE *outStream, struct machineState state);

/**
 * @brief Saves states history to file
 * 
 * @param fileName name of output file
 * @param buffer 
 * @return int 
 */
int saveAllToCSV(char *fileName, struct circularBuffer *buffer);

#endif