#include "task1_hashmap.h"

struct characterHashmap *initCharacterHashmap()
{
    struct characterHashmap *newMap = malloc(sizeof(struct characterHashmap));

    newMap->size = HASHMAP_SIZE;

    for (int i = 0; i < HASHMAP_SIZE; i++)
        newMap->array[i] = NULL;

    return newMap;
}

int hash(char character)
{
    return character % HASHMAP_SIZE;
}

/**
 * @brief Adds character occurence to the hashmap
 * 
 * @param hashmap Hashmap of the characters
 * @param character which will be saved in hashmap
 */
void addOccurenceToMap(struct characterHashmap *hashmap, char character)
{
    struct hashmapListElem **headPtr = &(hashmap->array[hash(character)]);
}

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