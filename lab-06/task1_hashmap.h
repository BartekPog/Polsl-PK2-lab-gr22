/** @file */

#ifndef HASHMAP
#define HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASHMAP_SIZE
#define HASHMAP_SIZE sizeof(char)
#endif

struct indexListElem
{
    int index;                   ///< Index in the string
    struct indexListElem *pNext; ///< Pointer to the next element
};

struct hashmapListElem
{
    char character;                ///< String containing the character
    int count;                     ///< In how many documents has occured
    struct indexListElem *indexes; ///< Pointer to the index list
    struct hashmapListElem *pNext; ///< Pointer to the next element
};

struct characterHashmap
{
    struct hashmapListElem *array[HASHMAP_SIZE]; ///< Array of hashmap elements
    int size;                                    ///< Size of the hashmap array
};

/**
 * @brief Initializes a hashmap of characters
 * 
 * @return struct characterHashmap* pointer to a fresh character hashmap instance 
 */
struct characterHashmap *initCharacterHashmap();

/**
 * @brief Gets the index in hashmap of the element
 * 
 * @param character Element of which the index will be found 
 * @return int Index in hashmap
 */
int hash(char character);

/**
 * @brief Adds character occurence to the hashmap
 * 
 * @param hashmap Hashmap of the characters
 * @param character which will be saved in hashmap
 */
void addOccurenceToMap(struct characterHashmap *hashmap, char character);

/**
 * @brief Get the occurence count of particular character from hashmap
 * 
 * @param hashmap Hashmap of the characters
 * @param character character whose occurence will be returned
 * @return int Occurence count of the character
 */
int getOccurenceFromMap(struct characterHashmap *hashmap, char *character);

/**
 * @brief Frees the memory taken by the hashmap
 * 
 * @param hashmap pointer to the hashmap instance
 */
void freeHashmap(struct characterHashmap *hashmap);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 *
 * @param pHead
 */
void freeHashCharacterList(struct hashmapListElem **pHead);

/**
 * @brief Frees the memory assigned to the indexes list
 * 
 * @param indexes pointer to the indexes pointer
 */
void freeIndexList(struct indexListElem **indexes);

#endif