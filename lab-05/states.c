#include "states.h"

struct machineState getNextState(struct machineState currentState, float manipulationSpeed)
{
    struct machineState nextState;
    nextState.input = '\0';

    // Handle input
    switch (currentState.input)
    {
    case 'o':
        switch (currentState.stateCase)
        {
        case closed:
        case closing:
        case stop:;
            nextState.stateCase = opening;
            nextState.degreeOfOpenness = currentState.degreeOfOpenness + manipulationSpeed;
            return nextState;
        }
        break;

    case 'c':
        switch (currentState.stateCase)
        {
        case open:
        case opening:
        case stop:;
            nextState.stateCase = closing;
            nextState.degreeOfOpenness = currentState.degreeOfOpenness - manipulationSpeed;
            return nextState;
            break;
        }
        break;

    case 's':
        switch (currentState.stateCase)
        {
        case open:
        case closed:;
            nextState.stateCase = currentState.stateCase;
            nextState.degreeOfOpenness = currentState.degreeOfOpenness;
            return nextState;
            break;
        default:;
            nextState.stateCase = stop;
            nextState.degreeOfOpenness = currentState.degreeOfOpenness;
            return nextState;
            break;
        }
        break;
    }

    // Handle state changes
    switch (currentState.stateCase)
    {
    case open:
    case closed:
    case stop:;
        nextState.stateCase = currentState.stateCase;
        nextState.degreeOfOpenness = currentState.degreeOfOpenness;
        return nextState;
        break;
    case opening:;
        if (currentState.degreeOfOpenness + manipulationSpeed >= 1)
        {
            nextState.degreeOfOpenness = 1;
            nextState.stateCase = open;
        }
        else
        {
            nextState.degreeOfOpenness = currentState.degreeOfOpenness + manipulationSpeed;
            nextState.stateCase = opening;
        }
        return nextState;
        break;
    case closing:;
        if (currentState.degreeOfOpenness - manipulationSpeed <= 0)
        {
            nextState.degreeOfOpenness = 0;
            nextState.stateCase = closed;
        }
        else
        {
            nextState.degreeOfOpenness = currentState.degreeOfOpenness - manipulationSpeed;
            nextState.stateCase = closing;
        }
        return nextState;
        break;
    }
}
