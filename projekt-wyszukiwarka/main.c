#include <stdio.h>
#include <string.h>
#include "libs/stmr.h"

#define INPUT_FILE "data/Articles-prep.csv"
#define STOP_WORDS_FILE "data/en-stopwords.txt"

#define MAX_QUERY_SIZE 100

int main()
{
    int errors = 0;
    printf("Tell me what do You intent to read about?\t");
    char query[MAX_QUERY_SIZE];
    scanf("%s", query);

    return 0;
}
