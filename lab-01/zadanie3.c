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