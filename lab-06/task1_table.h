/** @file */

#ifndef TABLE
#define TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE sizeof(unsigned char) * 8

struct indexList
{
    int index;                   ///< Index in the string
    struct indexListElem *pNext; ///< Pointer to the next element
};

/**
 * @brief Get the index of character
 * 
 * @param c character to get index of
 * @return int index
 */
int encode(char c);

/**
 * @brief Get back the character 
 * 
 * @param c 
 * @return int 
 */
char decode(unsigned char c);

/**
 * @brief Inits the list table
 * 
 */
struct indexList **initIndexListTable();

/**
 * @brief Saves index of character in index list table
 * 
 * @param table pointer to the table first elem
 * @param c character to save
 * @param index index in file
 */
void addOccurence(struct indexList **table, char c, int index);

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

#endif