//Daniel Barreto Calvo

//This code is intended to find a solution 
//to the game Jail Braake.
//It does so by using graphs.
//having every node as an state, and every
//edge as a move we are able to find the 
//solutions to the puzzle.

#include <stdio.h>
#include <stdlib.h>

//state of the game
struct State
{
    char* board;
};

//array of states and arrays size   
struct State* states;
unsigned int statesSize;

//edges conecting the states
unsigned char** edges;

// Prints an state
// mainly for debuging
void printState(struct State state)
{
    for(int i = 0; i < 20; i++)
    {
        if(i % 4 == 0)
        {
            printf("\n");
        }
        printf("%c", state.board[i]);
    }
    printf("\n");
}

// compares 2 states
//returns 1 if they are equal, 0 if difrent 
char equalStates(struct State s1, struct State s2)
{
    char areEqual = 1;
    for(int i = 0; i < 20 && areEqual; i++)
    {
        if(s1.board[i] != s2.board[i])
            areEqual = 0;
    }
    return areEqual;
}

//adds an state to the array and adds one to its size
void addState(struct State state)
{
    states = realloc(states, sizeof(struct State)*(statesSize+1));
    states[statesSize] = state;
    statesSize++;
}

//Gets the initial state from the file given from parameter
struct State getInitial(FILE* fp)
{
    struct State initialState;
    int value;

    initialState.board = (char*)malloc(20);

    for(int i = 0;(value = fgetc(fp)) != EOF;)
    {
        if((value > 47 && value < 58) || value == 32)
        {
            initialState.board[i] = value;
            i++;
        }
    }
    return initialState;
}

//main method
int main()
{
    //reads the file with the initial state
    FILE* fp = fopen("FirstState.txt", "r");
    struct State initial = getInitial(fp);

    //initializes the state array and its size to 0
    states = (struct State*)malloc(0);
    statesSize = 0;

    //adds initial state
    addState(initial);

    printState(states[0]);
    return 0;
}