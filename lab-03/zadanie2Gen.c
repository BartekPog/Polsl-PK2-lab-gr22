#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PROPERTIES_BINARY_NAME "properties.dat"
#define PROPERTIES_JSON_NAME "properties.json"
#define OUTPUT_NAME "output.csv"

struct col
{
    char *name;
    int isFloat;
    float min;
    float max;
};

struct col *getColumns(int colNum, char *colData[])
{
    struct col *columns = malloc(sizeof(struct col) * colNum);
    int err = 0;

    for (int i = 0; (i < colNum) && (!err); i++)
    {
        columns[i].name = colData[i * 4];

        columns[i].isFloat = strcmp(colData[i * 4 + 1], "int");

        int filled = 0;

        filled += sscanf(colData[i * 4 + 2], "%f", &columns[i].min);
        filled += sscanf(colData[i * 4 + 3], "%f", &columns[i].max);
        if (filled != 2)
            err++;
    }

    if (err)
    {

        printf("Error, cannot parse parameters properly\n");
        free(columns);
        columns = NULL;
    }

    return columns;
}

int savePropsToBin(int rowNum, int colNum, struct col *columns, char *fileName)
{
    FILE *binProps = fopen(fileName, "wb");

    if (binProps)
    {
        fwrite(&rowNum, sizeof(int), 1, binProps);
        fwrite(&colNum, sizeof(int), 1, binProps);
        fwrite(columns, sizeof(struct col), colNum, binProps);
        for (int i = 0; i < colNum; i++)
        {
            int length = strlen(columns[i].name);
            fwrite(&length, sizeof(int), 1, binProps);
            fwrite(columns[i].name, sizeof(char), length, binProps);
        }
        fclose(binProps);
    }
    else
        return 1;

    return 0;
}

int savePropsToJson(int rowNum, int colNum, struct col *columns, char *fileName)
{
    FILE *binProps = fopen(fileName, "w");

    if (binProps)
    {
        fprintf(binProps, "{\n\t\"columnNumber\": %d,\n", colNum);
        fprintf(binProps, "\t\"rowNumber\": %d,\n", rowNum);
        fprintf(binProps, "\t\"columns\": [\n");

        for (int i = 0; i < colNum; i++)
        {
            fprintf(binProps, "\t\t{\n");
            fprintf(binProps, "\t\t\t\"Name\": \"%s\",\n", columns[i].name);
            fprintf(binProps, "\t\t\t\"isFloatingPoint\": %s,\n", (columns[i].isFloat == 0 ? "false" : "true"));
            fprintf(binProps, "\t\t\t\"MinValue\": %f,\n", columns[i].min);
            fprintf(binProps, "\t\t\t\"MaxValue\": %f\n", columns[i].max);

            fprintf(binProps, "\t\t}");

            if (i < colNum - 1)
                fprintf(binProps, ",");

            fprintf(binProps, "\n");
        }

        fprintf(binProps, "\t]\n}");

        fclose(binProps);
    }
    else
        return 1;

    return 0;
}

int generateCsv(int rowNum, int colNum, struct col *columns, char *fileName)
{
    FILE *csv = fopen(fileName, "w");
    if (!csv)
        return 1;

    fprintf(csv, "%s", columns[0].name);
    for (int i = 1; i < colNum; i++)
        fprintf(csv, ", %s", columns[i].name);

    ///TODO
}

int main(int argc, char *argv[])
{
    int err = 0;
    if (argc == 1)
    {
        printf("Each column is declared with 4 args:\n");
        printf("1. Name\n2. Type {int, float}\n3. Minimal value\n4. Maximal value\n");
        printf("Additionally you need to specify the size of output csv file\n\n");
        return 0;
    }

    if (argc < 6)
    {
        printf("Insufficient arguments number. Expected 4 per column + size, Got: %d\n", argc - 1);
        return 0;
    }
    else if ((argc - 2) % 4 != 0)
    {
        printf("Wrong parameters number. Expected 4 per column, Got: %d\n", argc - 1);
        return 0;
    }

    int rowNum = 0;
    sscanf(argc[argv - 1], "%d", &rowNum);
    if (rowNum <= 0)
    {
        printf("Error with number of rows param: It must be a natural number\n");
        return 0;
    }

    int colNum = (argc - 2) / 4;
    struct col *columns = getColumns(colNum, argv + 1);

    if (columns == NULL)
        return 0;

    if (!savePropsToBin(rowNum, colNum, columns, PROPERTIES_BINARY_NAME))
        printf("Succesfully saved props binary to: %s\n", PROPERTIES_BINARY_NAME);
    else
        printf("Error occured when saving properties to binary file\n");

    if (!savePropsToJson(rowNum, colNum, columns, PROPERTIES_JSON_NAME))
        printf("Succesfully saved props binary to: %s\n", PROPERTIES_JSON_NAME);
    else
        printf("Error occured when saving properties to json file\n");
    ///////////////

    free(columns);
    return 0;
}