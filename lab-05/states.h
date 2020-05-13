
#ifndef STATES
#define STATES

enum machineStateCase
{
    open,
    opening,
    closed,
    closing,
    stop
};

struct machineState
{
    enum machineStateCase stateCase;
    double degreeOfOpenness;
    char input;
};

/**
 * @brief Gets the next state 
 * Valid input characters:
 * o - open
 * c - close
 * s - stop
 * 
 * @param currentState 
 * @param manipulationSpeed increase/decrease of degreeOfOpenness in one tick 
 * @return struct machineState next state of the machine
 */
struct machineState getNextState(struct machineState currentState, float manipulationSpeed);

#endif