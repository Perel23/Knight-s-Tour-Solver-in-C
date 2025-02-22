#include "files.h"

chessPosArray ***validKnightMoves()
{
    int knightMoves[8][2] = // an array of the possible knight moves
            {
                    {-2,  1}, {-1,  2}, { 1,  2}, { 2,  1}, { 2, -1},
                    { 1, -2}, {-1, -2},{-2, -1}

            };

    chessPosArray ***movesArray = (chessPosArray ***)malloc(BOARD_SIZE * sizeof(chessPosArray **)); // allocating memory for the moves array, which is a 2D array of pointers to chessPosArray
    if(movesArray==NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        movesArray[i] = (chessPosArray **)malloc(BOARD_SIZE * sizeof(chessPosArray *));
        if(movesArray[i]==NULL)
        {
            printf("Memory allocation failed.");
            exit(1);
        }
    }

    for (int row = 0; row < BOARD_SIZE; row++) // iterate over each position on the chessboard to generate the possible moves for each position on the board
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            chessPosArray *posArray = (chessPosArray *)malloc(sizeof(chessPosArray));// allocating memory for a chessPosArray to store valid moves from the current position
            if(posArray==NULL)
            {
                printf("Memory allocation failed.");
                exit(1);
            }
            posArray->positions = (chessPos *)malloc(8 * sizeof(chessPos));
            posArray->size = 0;

            for (int move = 0; move < 8; move++) // checking each potential knight move
            {
                int newRow = row + knightMoves[move][0];
                int newCol = col + knightMoves[move][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)  // ensures the move is within the bounds of the chessboard
                {
                    posArray->positions[posArray->size][0] = 'A' + newRow;   // storing the valid move in posArray
                    posArray->positions[posArray->size][1] = '1' + newCol;
                    posArray->size++;
                }

            }

            movesArray[row][col] = posArray; // assigns the posArray to the current position in movesArray
        }
    }

    return movesArray; // returns the completed moves array

}