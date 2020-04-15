#include <stdio.h>
#include <string.h>
#include "libs/stmr.h"

#include "document.h"

#define INPUT_FILE "data/Articles-prep.csv"
#define STOP_WORDS_FILE "data/en-stopwords.txt"

#define MAX_QUERY_SIZE 100

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    int errors = 0;

    FILE *fileStream = fopen(INPUT_FILE, "r");

    printf("Tell me what do You intent to read about?\t");
    char query[MAX_QUERY_SIZE];

    // print("test");
    int result = scanf("%s", query);

    if (result < 1)
    {
        errors++;
        printf("Cannot search for empty query");
    }

    //TESTING
    struct docArray *docs = createDocArrayFromFile(fileStream);

    printDocument(fileStream, docs->documentPointers[0]);
    return 0;

    deleteDocArray(docs);

    fclose(fileStream);
    return 0;
}
