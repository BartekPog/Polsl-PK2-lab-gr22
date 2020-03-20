//////////////////////////////////////////////
//ZADANIE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIN_SIZE 100

void *rev(char *a)
{
    char *b = a + strlen(a) - 1;

    char buf;

    while (b > a)
    {
        buf = *a;
        *a++ = *b;
        *b-- = buf;
    }
}

char *decToBinary(int a)
{
    char *binarna = malloc(sizeof(char) * MAX_BIN_SIZE);
    int licznik = 0;

    if (a < 0)
    {
        binarna[licznik++] = '-';
        a = -a;
    }

    while (a > 0)
    {
        binarna[licznik++] = a % 2 + '0';
        a = a / 2;
    }
    binarna[licznik] = '\n';

    rev(binarna);
    return binarna;
}

int main()
{
    for (int i = 0; i < 10; i++)
    {
        int liczba;
        printf("Podaj liczbe: ");
        scanf("%d", &liczba);
        char *binarna = decToBinary(liczba);

        printf("%s", binarna);

        free(binarna);
    }

    return 0;
}

/////////////////////////////////////////////////////
//ZADANIE 2
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

/////////////////////////////////////////
//ZADANIE 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void zamaskuj(char *liczba, char *maska)
{
    if (strlen(maska) != strlen(liczba))
    {
        printf("ERR: lenghts of number and mask are not equal");
        return;
    }

    for (int i = 0; i < strlen(maska); i++)
        liczba[i] = (maska[i] != '0' ? liczba[i] : '0');
}

int main()
{
    char liczba[MAX_SIZE];
    char maska[MAX_SIZE];

    printf("Liczba: ");
    scanf("%s", liczba);

    printf("Maska:  ");
    scanf("%s", maska);

    zamaskuj(liczba, maska);

    printf("Wynik:  %s \n", liczba);
    return 0;
}