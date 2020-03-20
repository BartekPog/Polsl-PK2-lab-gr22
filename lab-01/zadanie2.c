#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zastapBit(char *liczba, int nrBitu, char wartosc)
{
    if (nrBitu < strlen(liczba))
        liczba[nrBitu] = wartosc;
}

int main()
{
    char napis[] = {"10001001010101010000010101"};

    zastapBit(napis, 0, '0');

    printf("%s \n", napis);
    return 0;
}