/** @file */

#ifndef TEXT_MANIP
#define TEXT_MANIP

#include "structures.h"
#include "libs/stmr.h"
#include <string.h>

/**
 * @brief Returns one way linked list of text tokens. All the unnecesary symbols and stop words are skipped. Tokens are stemmed.
 * 
 * @param inputText text given for tokenization
 * @param stopWords array of stop words
 * @param stopWordsSize size of stop words array
 * @return struct stringLinkedListElem* pointer to first element of tokens linked list
 */
struct stringLinkedListElem *tokenize(char *inputText, char **stopWords, int stopWordsSize);

/**
 * @brief Returns 1 if given character is a big or small letter. Otherwise 0 is returned
 * 
 * @param character Given character
 * @return int 1 if character is a letter or 0 otherwise
 */
int isLetter(char character);

/**
 * @brief Returns 1 if given word is a stop word
 * 
 * @param word word checked
 * @param stopWords array of stop words
 * @param stopWordsSize size of stop words array
 * @return int 1 if word is a stop words or 0 otherwise
 */
int isStopWord(char *word, char **stopWords, int stopWordsSize);

/**
 * @brief Counts how many searched n-gram exists in the given document
 * 
 * @param searchedNGram n-gram function is supposed to look for in the document. Stored as a one way linked list of words
 * @param document one way linked list of words
 * @return int how many searched n-gram was found in the document
 */
int countTokenOverlaps(struct stringLinkedListElem *searchedNGram, struct stringLinkedListElem *document);

#endif