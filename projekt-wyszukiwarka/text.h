/** @file */

#ifndef TEXT
#define TEXT

#include <stdio.h>

/** One way linked list of char strings, inverted, stop-words replaced by "\0"*/
struct stringLinkedListElem
{
    char *value;                  ///< Word contained in a wordLinkedList
    struct wordLinkedList *pNext; ///< Pointer to the next element of linked list
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
 * @param pHeadPointer Pointer to the head pointer of the list 
 * @param value value to add to the list 
 */
void addToStringListHead(struct stringLinkedListElem **pHeadPointer, char *value);

/**
 * @brief Counts how many elements are in the lis
 * 
 * @param pHead pointer to list head
 * @return int number of elements
 */
int countStringLinkedListElements(struct stringLinkedListElem *pHead);

#endif