#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "circular_buffer.h"
#include "states.h"
#include "utils.h"
#include "output.h"

#define BUFFER_SIZE 100000
#define OUTPUT_FILE_NAME "states_record.csv"

#define MANIPULATION_SPEED 0.01
#define TICK_DURATION_MS 200

#define EXIT_KEY 'q'

int main()
{
    struct circularBuffer buffer = CreateCircularBuffer(BUFFER_SIZE);

    int running = 1;
    char character;

    struct machineState state = {closed, 0, '\0'};

    while (1)
    {
        character = '\0';

        if (kbhit())
            character = getchar();

        if (character == EXIT_KEY)
            break;

        state.input = character;

        writeToCircularBuffer(&buffer, state);
        showState(stdout, state);

        state = getNextState(state, MANIPULATION_SPEED);

        fflush(stdout);
        usleep(TICK_DURATION_MS * 1000);
    }

    saveAllToCSV(OUTPUT_FILE_NAME, &buffer);

    freeCircularBuffer(&buffer);

    printf("\nDone\n");
    return 0;
}