#include "output.h"

char *getStateString(enum machineStateCase stateCase)
{
    char *stateString = NULL;

    switch (stateCase)
    {
    case open:;
        stateString = strdup("open");
        break;
    case opening:;
        stateString = strdup("opening");
        break;
    case closed:;
        stateString = strdup("closed");
        break;
    case closing:;
        stateString = strdup("closing");
        break;
    case stop:;
        stateString = strdup("stop");
        break;
    }
    return stateString;
}

void showState(FILE *outStream, struct machineState state)
{
    char *stateString = getStateString(state.stateCase);

    fprintf(outStream, "\nState: %10s\t Gate open percentage: %.1lf%%", stateString, 100 * state.degreeOfOpenness);

    if (state.input != '\0')
        fprintf(outStream, "\tInput: %c", state.input);

    free(stateString);
}

int saveAllToCSV(char *fileName, struct circularBuffer *buffer)
{
    FILE *csv = fopen(fileName, "w");

    if (!csv)
        return 1;

    fprintf(csv, "State_case,Open_percentage,input\n");
    for (int i = 0; i < buffer->bufferLength; i++)
    {
        struct machineState state = readFromCircularBuffer(buffer);
        char input = (state.input == '\0' ? ' ' : state.input);
        char *stateString = getStateString(state.stateCase);
        fprintf(csv, "%s,%.2lf,%c\n", stateString, state.degreeOfOpenness * 100, input);

        free(stateString);
    }

    fclose(csv);
}