#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

    free(outFileName);
    fclose(outFile);
    return 0;
}

void test()
{
    for (int c = -128; c < 128; c++)
        assert((char)c == decode((unsigned char)encode((char)c)));
}