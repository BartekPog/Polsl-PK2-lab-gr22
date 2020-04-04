/** @file */

#ifndef STRUCTURES
#define STRUCTURES

/** One way linked list of char strings, inverted*/
struct stringLinkedListElem
{
    char *value;                  ///< Word contained in a wordLinkedList
    struct wordLinkedList *pNext; ///< Pointer to the next element of linked list
};

/**
 * @brief Frees memory taken by the linked list. Also nullifies the list head, thus it has to be given as a pointer to head pointer.
 * 
 * @param pointerToHeadPointer pointer to the list head pointer 
 */
void deleteStringLinkedList(struct stringLinkedListElem **pointerToHeadPointer);

/**
 * @brief Adds element to the beginning (head) of the list
 * 
 * @param pHead head of the list 
 * @param value value to add to the list 
 */
void addToListHead(struct stringLinkedListElem *pHead, char *value);

/**
 * @brief Counts how many elements are in the lis
 * 
 * @param pHead pointer to list head
 * @return int number of elements
 */
int countStringLinkedListElements(struct stringLinkedListElem *pHead);

#endif