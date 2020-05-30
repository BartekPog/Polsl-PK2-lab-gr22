#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIZZ 3
#define BUZZ 5

#define UPPER_LIMIT 100
#define MAX_CHAR_LEN 200

char *fizzBuzz1(int n)
{
    char *text = calloc(MAX_CHAR_LEN, sizeof(char));

    if (n % FIZZ == 0)
        text = strcat(text, "Fizz");

    if (n % BUZZ == 0)
        text = strcat(text, "Buzz");

    if (text[0] == '\0')
        sprintf(text, "%d", n);

    return text;
}

char *fizzBuzz2(int n)
{
    if (n % (FIZZ * BUZZ) == 0)
        return strdup("FizzBuzz");

    if (n % FIZZ == 0)
        return strdup("Fizz");

    if (n % BUZZ == 0)
        return strdup("Buzz");

    char *text = calloc(MAX_CHAR_LEN, sizeof(char));
    sprintf(text, "%d", n);

    return text;
}

char *fizzBuzz3(int n)
{
    char *text = calloc(MAX_CHAR_LEN, sizeof(char));

    if (!((n % FIZZ) * (n % BUZZ)))
        return strcat((n % FIZZ ? text : strcat(text, "Fizz")), (n % BUZZ ? "\0" : "Buzz"));

    sprintf(text, "%d", n);
    return text;
}

int main()
{
    setbuf(stdout, NULL);

    char *(*functions[])(int) = {fizzBuzz1, fizzBuzz2, fizzBuzz3};

    int numberOfFunctions = sizeof(functions) / sizeof(&fizzBuzz1);

    for (int i = 1; i <= UPPER_LIMIT; i++)
    {
        printf("%4d\t", i);

        for (int funIndex = 0; funIndex < numberOfFunctions; funIndex++)
        {
            char *text = functions[funIndex](i);
            printf("%10s", text);
            free(text);
        }

        printf("\n");
    }

    return 0;
}