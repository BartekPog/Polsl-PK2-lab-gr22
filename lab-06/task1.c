#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "task1_table.h"

#define DEFAULT_OUT_FILE "task1_out.csv"

#define DEBUG 1

void test();

int main(int argc, char *argv[])
{
    if (DEBUG)
        test();

    if (argc < 2)
    {
        printf("ERR: You need to specify the text to analyze\n\n");
        printf("For example run:\n");
        printf("./task1 \"Test string\"\n");
        printf("\n\nIf you want to specify the output file name give it as secont program argument\n");
        return 0;
    }

    char *outFileName;
    if (argc > 2)
        outFileName = strdup(argv[2]);
    else
        outFileName = strdup(DEFAULT_OUT_FILE);

    FILE *outFile = fopen(outFileName, "w");

    if (!outFile)
    {
        printf("ERR: Cannot open file %s\n", outFileName);
        free(outFileName);
        return 0;
    }

    struct indexList **table = initIndexListTable();
    saveStringToTable(table, argv[1]);

    fprintf(outFile, "ASCII_code,Character,Number_of_occurences,Min_self_distance,Max_self_distance\n");

    for (int i = 0; i < UCHAR_MAX; i++)
    {
        char character = decode(i);

        int occurences = getNumberOfOccurences(table, character);
        if (occurences < 1)
            continue;

        fprintf(outFile, "%d,'%c',", i, character);

        if (occurences > 1)
            fprintf(outFile, "%d,%d\n", getMinDistance(table, character), getMaxDistance(table, character));

        else
            fprintf(outFile, ",\n");
    }

    free(outFileName);
    freeIndexesTable(table);
    fclose(outFile);
    return 0;
}

void test()
{
    setbuf(stdout, NULL);
    for (int c = -128; c < 128; c++)
        assert((char)c == decode((unsigned char)encode((char)c)));
}