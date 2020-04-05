/** @file */
#ifndef IMPORT
#define IMPORT

#include <stdio.h>

/**
 * @brief Create a document array from a given file stream
 * 
 * @param fileStream filestream on which the document array shall be created
 * @return struct docArray 
 */
struct docArray createDocArrayFromFile(FILE *fileStream);

/**
 * @brief Creates a one way linked list of all documents
 * 
 * @param fileStream File stream of the articles file
 * @return struct docLinkedListElem 
 */
struct docLinkedListElem readArticlesFile(FILE *fileStream);

#endif
