#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_INPUT_FILE "output.csv"
#define DEFAULT_OUTPUT_FILE "analysis.txt"

struct column
{
    char *name;
    float *values;
};

int getNumberOfRows(FILE *csv)
{
    fpos_t pos;
    fgetpos(csv, &pos);

    int count = 0;
    for (char c = getc(csv); c != EOF; c = getc(csv))
        if ((c == '\n') && (getc(csv) != EOF))
            count = count + 1;

    fsetpos(csv, &pos);
    return count;
}

int getNumberOfCols(FILE *csv)
{
    fpos_t pos;
    fgetpos(csv, &pos);

    int count = 0;
    for (char c = getc(csv); ((c != EOF) && (c != '\n')); c = getc(csv))
        if (c == ',')
            count = count + 1;

    fsetpos(csv, &pos);
    return count + 1;
}

char *getValString(FILE *csv)
{
    fpos_t pos;
    fgetpos(csv, &pos);

    int count = 0;
    for (char c = getc(csv); ((c != EOF) && (c != '\n') && (c != ',')); c = getc(csv))
        count = count + 1;

    fsetpos(csv, &pos);

    char *value = malloc(sizeof(char) * (count + 1));
    char *valEnd = value;

    for (int i = 0; i < count; i++)
        *valEnd++ = getc(csv);

    getc(csv);

    *valEnd = '\0';
    return value;
}
int compareFloat(void *a, void *b)
{
    float _a = *(float *)a;
    float _b = *(float *)b;
    if (_a < _b)
        return -1;
    else if (_a == _b)
        return 0;
    else
        return 1;
}

void printAnalysisToStream(FILE *stream, struct column col, int size)
{
    qsort(col.values, size, sizeof(float), (int (*)(const void *, const void *))compareFloat);

    float min = col.values[0];
    float max = col.values[size - 1];
    double sum = 0;

    for (int i = 0; i < size; i++)
        sum += col.values[i];

    float mean = (float)(sum / size);

    float median = col.values[(size - 1) / 2];
    median += col.values[size / 2];
    median /= 2;

    fprintf(stream, "       Column: %s\n", col.name);
    fprintf(stream, "minimum value: %f\n", min);
    fprintf(stream, "maximum value: %f\n", max);
    fprintf(stream, "   mean value: %f\n", mean);
    fprintf(stream, " median value: %f\n\n", median);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    char *fileName = DEFAULT_INPUT_FILE;
    char *outFileName = DEFAULT_OUTPUT_FILE;

    if (argc > 1)
        fileName = argv[1];
    if (argc > 2)
        outFileName = argv[2];

    FILE *csv = fopen(fileName, "r");

    if (!csv)
    {
        printf("Error, cannot open file.\n");
        return 0;
    }

    int rows = getNumberOfRows(csv);
    int cols = getNumberOfCols(csv);
    if ((rows < 1) || (cols < 1))
    {
        printf("Error, invalid csv file.");
        fclose(csv);
        return 0;
    }

    printf("found columns: %d\n", cols);
    printf("found rows: %d\n\n", rows);

    struct column *colArr = malloc(sizeof(struct column) * cols);

    for (int i = 0; i < cols; i++)
        colArr[i].values = malloc(sizeof(float) * rows);

    for (int i = 0; i < cols; i++)
        colArr[i].name = getValString(csv);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            char *valString = getValString(csv);

            float value = 0;
            if (sscanf(valString, "%f", &value) == 0)
                printf("Error reading value: %s", valString);

            free(valString);
            colArr[col].values[row] = value;
        }
    }
    fclose(csv);

    FILE *analysisFile = fopen(outFileName, "w");

    for (int i = 0; i < cols; i++)
    {
        printAnalysisToStream(stdout, colArr[i], rows);
        printAnalysisToStream(analysisFile, colArr[i], rows);
    }

    fclose(analysisFile);

    for (int i = 0; i < cols; i++)
    {
        free(colArr[i].name);
        free(colArr[i].values);
    }

    free(colArr);

    return 0;
}