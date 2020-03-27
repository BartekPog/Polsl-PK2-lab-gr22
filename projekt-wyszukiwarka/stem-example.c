#include <stdio.h>
#include <string.h>
#include "libs/stmr.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        char *word = argv[1];

        int end = stem(word, 0, strlen(word) - 1);

        printf("%s\n", word);

        word[end + 1] = '\0';

        printf("%s\n", word);
    }

    return 0;
}