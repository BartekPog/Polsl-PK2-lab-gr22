/** @file */

#ifndef DOCUMENT
#define DOCUMENT

#include <stdio.h>
#include <stdlib.h>

/** Structure containing a single document*/
struct document
{
    char *header;    ///< header of the document
    fpos_t startPos; ///< Position of the beginning of the article in file
    int lenght;      ///< Lenght of the document
    // fpos_t endPos;   ///< Position of the first character after article
    // int grams;       ///< Total number of grams
};

/** document one way linked list*/
struct docLinkedListElem
{
    struct document *docPtr;         ///< Pointer to the stored document
    struct docLinkedListElem *pNext; ///< Pointer to the next element of linked list
};

/** Array of pointers to documents ant its size*/
struct docArray
{
    struct document **documentPointers; ///< Array of pointers to documents
    int size;                           ///< Size of the docArray
};

/**
 * @brief Create a document array from a given file stream
 * 
 * @param fileStream filestream on which the document array shall be created
 * @return struct docArray* Pointer to the document array
 */
struct docArray *createDocArrayFromFile(FILE *fileStream);

/**
 * @brief Creates a one way linked list of all documents
 * 
 * @param fileStream File stream of the articles file
 * @param[out] numberOfElements changed by reference - number of elements in a created list
 * @return struct docLinkedListElem pointer to the head of document list 
 */
struct docLinkedListElem *createDocListFromFile(FILE *fileStream, int *numberOfElements);

// /**
//  * @brief Counts the number of elements in a document linked list
//  *
//  * @param docHead head of documents list
//  * @return int number of elements
//  */
// int countDocLinkedListElements(struct docLinkedListElem *docHead);

/**
 * @brief Adds document to the document list at the head position.
 * 
 * @param pHeadPointer 
 * @param doc 
 */
void addDocToDocListHead(struct docLinkedListElem **pHeadPointer, struct document *doc);

/**
 * @brief Frees the memory taken by the document array and all the documents stored in it
 * 
 * @param array pointer to the document array
 */
void deleteDocArray(struct docArray *array);

/**
 * @brief Prints the given document
 * 
 * @param fileStream file on which the document is based
 * @param doc pointer to the printed document
 */
void printDocument(FILE *fileStream, struct document *doc);

#endif