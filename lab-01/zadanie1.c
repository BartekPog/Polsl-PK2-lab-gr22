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
    for (int i = 0; i < 20; i++)
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