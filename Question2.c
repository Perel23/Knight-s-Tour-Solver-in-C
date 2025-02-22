#include "files.h"

#define NOT_ON_LIST 0

void initializeBoard(chessSquare board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].row = 'A' + i; // setting the row and column characters for each square on the board
            board[i][j].col = '1' + j;
        }
    }
}

void removeListNode(chessPosCell *prev)
{
    chessPosCell *toDelete = prev->next;
    prev->next = toDelete->next;
    free(toDelete);
}

void removeDup(chessPosList *lst)
{
    if (lst == NULL || lst->head == NULL) // checking if the list is NULL or empty, if its empty the function returns
    {
        return;
    }
    chessPosCell *curr = lst->head;
    while (curr != NULL)
    {
        chessPosCell *runner = curr;
        while (runner->next != NULL)
        {
            if (curr->position[0] == runner->next->position[0] && curr->position[1] == runner->next->position[1])  // comparing current position with the next positions

            {
                removeListNode(runner); // removing duplicate node
            }
            else
            {
                runner = runner->next;
            }
        }
        curr = curr->next;
    }
}


void display(chessPosList *lst)
{
    removeDup(lst); // removing duplicate positions from the list

    chessSquare board[BOARD_SIZE][BOARD_SIZE]; // initializing the board with default positions
    initializeBoard(board);

    int boardNumbers[BOARD_SIZE][BOARD_SIZE] = {NOT_ON_LIST}; // Initialize the board numbers array

    if (lst == NULL) // checking for NULL list
        return;
    else
    {
        chessPosCell *curr = lst->head;
        int nodeIndex = 1; // initializing the number for the first node in the list

        while (curr != NULL) // assigns numbers to the positions in the list according to their index in the list
        {
            int row = curr->position[0] - 'A';
            int col = curr->position[1] - '1';
            boardNumbers[row][col] = nodeIndex; // assigns each position with its index in the list
            curr = curr->next;
            nodeIndex++;
        }

        // printing the board
        printf("   1  2  3  4  5\n");
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            printf("%c|", 'A' + i);
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (boardNumbers[i][j] == NOT_ON_LIST)
                {
                    printf(" * "); // if the position isn't on the list, the program will print '*' in that spot
                }
                else
                {
                    printf("%2d|", boardNumbers[i][j]); //if the position is on the list, the program will print number assigned to it
                }
            }
            printf("\n");
        }
    }
}