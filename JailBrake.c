//Daniel Barreto Calvo

//This code is intended to find a solution 
//to the game Jail Braake.
//It does so by using graphs.
//having every node as an state, and every
//edge as a move we are able to find the 
//solutions to the puzzle.

#include <stdio.h>
#include <stdlib.h>

// define constants to reprecent directions
const unsigned char UP = 0;
const unsigned char DOWN = 64;
const unsigned char LEFT = 128;
const unsigned char RIGHT = 192;

//state of the game
struct State
{
    char* board;
};

//Linked list with all the edges and the move information
struct Edge
{
    unsigned char destinationState;
    unsigned char piece;
    unsigned char direction;
    struct Edge* tail;
};

//array of states and arrays size   
struct State* states;
unsigned char statesSize;

//edges conecting the states
struct Edge* heads;
unsigned char headsSize;

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
    states = realloc(states, sizeof(struct State) * (statesSize + 1));
    states[statesSize] = state;
    statesSize++;
}

//adds a head to the head array
void addHead(struct Edge newHead)
{
    heads = realloc(heads, sizeof(struct Edge) * (headsSize + 1));
    heads[headsSize] = newHead;
    headsSize++;
}

//Adds an edge to the respective list
void addEdgeToList(struct Edge head, struct Edge newEdge)
{
    if(!head.tail)
    {
        head.tail = (struct Edge*)malloc(sizeof(struct Edge));
        head.tail = &newEdge;
    }else
    {
        addEdgeToList(*head.tail, newEdge);
    }
}

// makes the specified move in the board given by parameter.
// returns the hash of the move if the move was sucsessfull, 
// and 0 otherwise.
unsigned char move(unsigned char direction, char piece, struct State currentState)
{
    // this hash has the first 2 digits as the direction and the rest as the piece ascii
    unsigned char hash;

    //this hash is has the x in the first 4 digits and the y in the last 2
    unsigned char* pieceLocations = (unsigned char*)malloc(0);

    // a board representing the 
    char board[5][4];

    char pieceSize = 0;

    //multi pourpous for
    for(int i = 0; i < 20; i++)
    {
        // gets the size of the piece
        if(piece == currentState.board[i])
            pieceSize++;

        //gets the board and places it in the matriz
        board[i / 4][i % 4] = piece;

        // gets the logations of the piece
        unsigned char x = i % 4;
        unsigned char y = i / 4;

        x = x << 4;

        // creates the location hash and ads it to the locations array
        pieceLocations = realloc(pieceLocations, pieceSize);
        pieceLocations[i] = x ^ y;
    }

    // modifies the board with the move
    for(int i = 0; i < pieceSize;i++)
    {
        
        // depending on the direction, we need to doit one way or the other
        if(direction == LEFT || direction == UP)
        {
            // gets location
            unsigned char location = pieceLocations[i];
            unsigned char x = location >> 4;
            unsigned char y = location ^ (x << 4);

            if(x != 0 && board[y][x - 1] == 32 && direction == LEFT)
            {
                // changes the board tiles
                unsigned char temporal = board[y][x];
                board[y][x] = board[y][x - 1];
                board[y][x - 1] = temporal;

                hash = direction ^ piece;
            }
            else if(y != 0 && board[y - 1][x] == 32 && direction == UP)
            {
                unsigned char temporal = board[y][x];
                board[y][x] = board[y - 1][x];
                board[y - 1][x] = temporal;

                hash = direction ^ piece;
            }
            else
            {
                hash = 0;
            }
        }
        else if(direction == RIGHT || direction == DOWN)
        {
            unsigned char location = pieceLocations[pieceSize - 1 - i];
            unsigned char x = location >> 4;
            unsigned char y = location ^ (x << 4);

            if(x != 3 && board[y][x + 1] == 32 && direction == RIGHT)
            {
                unsigned char temporal = board[y][x];
                board[y][x] = board[y][x + 1];
                board[y][x + 1] = temporal;

                hash = direction ^ piece;
            }
            else if(y != 4 && board[y + 1][x] == 32 && direction == DOWN)
            {
                unsigned char temporal = board[y][x];
                board[y][x] = board[y + 1][x];
                board[y + 1][x] = temporal;

                hash = direction ^ piece;
            }
            else
            {
                hash = 0;
            }
        }
    }

    return hash;
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

    heads = (struct Edge*)malloc(0);
    headsSize = 0;

    //adds initial state
    addState(initial);

    printState(states[0]);
    return 0;
}