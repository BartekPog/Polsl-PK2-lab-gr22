/** @file */

#ifndef TEXT_MANIP
#define TEXT_MANIP

#include "structures.h"

struct stringLinkedList *tokenize(char *inputText, char *stopWords);

int isLetter(char character);

int isStopWord(char *word, );

#endif