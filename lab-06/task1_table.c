#include "task1_table.h"

int encode(char c)
{
    return (int)(unsigned char)(c);
}

char decode(unsigned char c)
{
    return (char)(c);
}

struct indexList **initIndexListTable()
{
    struct indexList **table = malloc(sizeof(struct indexList *) * SIZE);

    for (int i = 0; i < SIZE; i++)
        table[i] = NULL;

    return 0;
}

/**
 * @brief Saves index of character in index list table
 * 
 * @param table pointer to the table first elem
 * @param c character to save
 * @param index index in file
 */
void addOccurence(struct indexList **table, char c, int index)
{
    // int
}

/**
 * @brief Save string stats to table
 * 
 * @param table pointer to the table first elem
 * @param str string to save
 */
void addMultipleOccurences(struct indexList **table, char *str);

/**
 * @brief Get the Number Of Occurences of a character
 * 
 * @param table pointer to the table first elem
 * @param c character to count occurences of
 * @return int number of occurences
 */
int getNumberOfOccurences(struct indexList **table, char c);

/**
 * @brief Get the minimal distance between characters
 * 
 * @param table pointer to the table first elem
 * @param c character to count occurences of
 * @return int minimal distance
 */
int getMinDistance(struct indexList **table, char c);

/**
 * @brief Get the maximal distance between characters
 * 
 * @param table pointer to the table first elem
 * @param c character to count occurences of
 * @return int maximal distance
 */
int getMaxDistance(struct indexList **table, char c);