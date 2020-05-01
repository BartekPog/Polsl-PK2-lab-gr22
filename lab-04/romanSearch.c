#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FILE_DIR "example.html"

int isRomanNum(char ch)
{
    switch (tolower(ch))
    {
    case 'i':
    case 'v':
    case 'x':
    case 'l':
    case 'c':
    case 'd':
    case 'm':
        return 1;
    }
    return 0;
}

int readOne(FILE *f)
{
    int c;
    for (int i = 0; i < 3; i++)
    {
        c = getc(f);
        if ((c == EOF) || (!isRomanNum(c)))
            return 0;
    }

    c = getc(f);
    if ((c == EOF) || (tolower(c) != 'v'))
        return 0;

    for (int i = 0; i < 3; i++)
    {
        c = getc(f);
        if ((c == EOF) || (!isRomanNum(c)))
            return 0;
    }
    return 1;
}

void printOne(FILE *f)
{
    for (int i = 0; i < 7; i++)
        putchar(getc(f));
    putchar('\n');
}

int main()
{
    FILE *f = fopen(FILE_DIR, "r");
    if (!f)
    {
        printf("Cannot open file %s", FILE_DIR);
        return 0;
    }

    int shallContinue = 1;
    fpos_t pos;
    int linecount = 1;
    int c;

    while (shallContinue)
    {
        fgetpos(f, &pos);
        if (readOne(f))
        {
            printf("line: %3d\t", linecount);
            fsetpos(f, &pos);
            printOne(f);
        }
        else
            fsetpos(f, &pos);

        c = getc(f);
        if (c == EOF)
            shallContinue = 0;
        else if (c == '\n')
            linecount++;
    }

    printf("total lines: %d\n", linecount);
    fclose(f);
    return 0;
}

// // Example output from file:

// line: 1015      XXXVIII
// line: 1016      CCCVIII
// line: 1017      DXLVIII
// total lines: 2423