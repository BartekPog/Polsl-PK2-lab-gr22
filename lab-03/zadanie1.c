#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0

#define TEXT_FILENAME "1text.txt"
#define MAX_SEARCHED 300

char *concatStrings(int howMany, char *strings[])
{
    int size = howMany;
    for (int i = 0; i < howMany; i++)
        size += strlen(strings[i]);

    char *final = malloc(size * sizeof(char));
    memset(final, ' ', size);

    char *partial = final;
    for (int i = 0; i < howMany; i++)
    {
        memmove(partial, strings[i], strlen(strings[i]));
        partial += strlen(strings[i]) + 1;
    }
    *(--partial) = '\0';
    return final;
}

int isIn(char *haystack, char *needle)
{
    char *lowerHayStack = strdup(haystack);
    char *lowerNeedle = malloc(sizeof(char) * (strlen(needle) + 1));
    memmove(lowerNeedle, needle, strlen(needle) + 1);

    for (int i = 0; i < strlen(haystack); i++)
        lowerHayStack[i] = tolower(haystack[i]);

    for (int i = 0; i < strlen(needle); i++)
        lowerNeedle[i] = tolower(needle[i]);

    int result = strstr(lowerHayStack, lowerNeedle) != NULL;
    free(lowerNeedle);
    free(lowerHayStack);

    return result;
}

int main(int argc, char *argv[])
{
    assert(argc > 1);

    char *searched = concatStrings(argc - 1, argv + 1);

    for (int i = 0; i < strlen(searched); i++)
        assert(!isdigit(searched[i]));

    FILE *textFile = fopen(TEXT_FILENAME, "r");
    int filelen;
    size_t stringlen;

    fscanf(textFile, "%d %lu", &filelen, &stringlen);

#if DEBUG
    assert(filelen == 78);
    assert(stringlen == 102);
#endif

    char **documents = malloc(filelen * sizeof(char *));

    for (int i = 0; i < filelen; i++)
    {
        char *buffer = malloc(sizeof(char) * (stringlen + 1));
        int characters = getline(&buffer, &stringlen, textFile);
        assert(characters > 0);

        documents[i] = strdup(buffer);
        free(buffer);
    }

    ///////////////

    for (int i = 0; i < filelen; i++)
    {

        if (isIn(documents[i], searched))
        {
            char *buffer = malloc(sizeof(char) * (stringlen + 6));
            sprintf(buffer, "%.2d. %s", i, documents[i]);
            fputs(buffer, stdout);
            free(buffer);
        }
    }

    ///////////////

    free(searched);

    for (int i = 0; i < filelen; i++)
        free(documents[i]);
    free(documents);

    system("echo done");
    return 0;
}