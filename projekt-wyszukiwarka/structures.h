/** @file */

#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>

/** One way linked list of char strings, inverted, stop-words replaced by "\0"*/
struct stringLinkedListElem
{
    char *value;                  ///< Word contained in a wordLinkedList
    struct wordLinkedList *pNext; ///< Pointer to the next element of linked list
};

/** Structure containing a single document*/
struct document
{
    char header[300]; ///< header of the document
    fpos_t startPos;  ///< Position of the beginning of the article in file
    fpos_t endPos;    ///< Position of the ending of the article in file
    int grams;        ///< Total number of grams
};

/** document one way linked list*/
struct docLinkedListElem
{
    struct document *doc;            ///< Pointer to the stored document
    struct docLinkedListElem *pNext; ///< Pointer to the next element of linked list
};

/** Array of pointers to documents ant its size*/
struct docArray
{
    struct document **documentPointers; ///< Array of pointers to documents
    int size;                           ///< Size of the docArray
};

/**
 * @brief Frees memory taken by the linked list. It does not nullify the pointer
 * 
 * @param pointerToHeadPointer list head pointer 
 */
void deleteStringLinkedList(struct stringLinkedListElem *pHead);

/**
 * @brief Adds element to the beginning (head) of the list
 * 
 * @param pHead head of the list 
 * @param value value to add to the list 
 */
void addToStringListHead(struct stringLinkedListElem *pHead, char *value);

/**
 * @brief Counts how many elements are in the lis
 * 
 * @param pHead pointer to list head
 * @return int number of elements
 */
int countStringLinkedListElements(struct stringLinkedListElem *pHead);

/**
 * @brief Frees the memory taken by the document array and all the documents stored in it
 * 
 * @param array pointer to the document array
 */
void deleteDocArray(struct docArray *array);

#endif