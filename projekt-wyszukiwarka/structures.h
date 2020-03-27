/** @file */

#ifndef STRUCTURES
#define STRUCTURES

/** One way linked list of char strings*/
struct stringLinkedList
{
    char *value;                  ///< Word contained in a wordLinkedList
    struct wordLinkedList *pNext; ///< Pointer to the next element of linked list
};

#endif