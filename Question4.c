#include "files.h"

#define VISITED 1
#define NOT_VISITED 0


void makeEmptyList(chessPosList *list)
{
    list->head = list->tail = NULL;
}

void addNodeToEnd(chessPosList *lst, chessPosCell *node)
{
    if (lst->head == NULL)
    {
        lst->head = lst->tail = node;
    }
    else
    {
        lst->tail->next = node;
        lst->tail = node;
    }
    node->next = NULL;
}

void addNewPositionToEnd(chessPosList *lst, chessPos pos)
{
    chessPosCell *newNode = (chessPosCell *)malloc(sizeof(chessPosCell));
    if(newNode==NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }

    newNode->position[0] = pos[0];
    newNode->position[1] = pos[1];

    newNode->next = NULL;
    addNodeToEnd(lst, newNode);
}

void addPosToBoard(int **board, chessPos pos)
{
    int row = pos[1] - '1';
    int col = pos[0] - 'A';

    board[row][col] = VISITED; // marking the position as visited
}

void freeBoard(int **board, int rows)
{
    for (int i = 0; i < rows; i++) // iterates over each row
    {
        free(board[i]);
    }
    free(board); // freeing the array after freeing all the rows
}

bool isAllBoardVisited(int **board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == NOT_VISITED)
            {
                return false; // if one of the positions on the board have not been visited, the program returns FALSE
            }
        }
    }
    return true;
}

chessPosList *copyList(chessPosList *lst)
{
    chessPosList *newList;

    chessPosCell *cell = lst->head;

    newList = (chessPosList *)malloc(sizeof(chessPosList));
    if(newList==NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    makeEmptyList(newList);

    while (cell != NULL)
    {
        addNewPositionToEnd(newList, cell->position); // add the new nodes to newList, based on the nodes on lst
        cell = cell->next;
    }

    return newList; // returns the new copied list
}

void freeList(chessPosList *lst)
{
    chessPosCell *curr = lst->head;
    chessPosCell *prev;

    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }

    free(lst);
}

bool isPosNotVisited(chessPos pos, int **board)
{
    int row = pos[1] - '1';
    int col = pos[0] - 'A';

    return (board[row][col] == NOT_VISITED);
}

chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree)
{
    int **visit_board = (int **)calloc(BOARD_SIZE, sizeof(int *));
    if(visit_board==NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        visit_board[i] = (int*) calloc(BOARD_SIZE, sizeof(int)); // initializing all the positions of the chessboard as NOT_VISITED (0)
    }

    chessPosList *lst = (chessPosList *)malloc(sizeof(chessPosList));
    if(lst==NULL)
    {
        printf("Memory allocation failed.");
        exit(1);
    }

    makeEmptyList(lst);

    lst = findKnightPathCoveringAllBoardHelper(path_tree->root, lst, visit_board);

    freeBoard(visit_board, BOARD_SIZE);

    return lst;
}

chessPosList *findKnightPathCoveringAllBoardHelper(treeNode *node, chessPosList *lst, int **visit_board)
{
    treeNodeListCell *current;
    chessPosList *newList;
    chessPosList *result;

    if (!isPosNotVisited(node->position, visit_board)) // if the position of the node was visited in the board, the path is not valid because of pos duplication and the program returns NULL
    {
        return NULL;
    }

    newList = copyList(lst); // copies the list

    addNewPositionToEnd(newList, node->position); // add the new position to the positions list
    addPosToBoard(visit_board, node->position); // marks the new position on the board

    if (isAllBoardVisited(visit_board))
    {
        return newList; // if all the positions on the board have been visited the path has been found
    }

    current = node->next_possible_positions.head; // the program goes over the node's next possible positions and checks if one of the has a valid path
    while (current != NULL)
    {
        result = findKnightPathCoveringAllBoardHelper(current->node, newList, visit_board);

        if (result != NULL)  // if the result is not NULL, a valid path has been found
        {
            freeList(newList);
            return result; // returning the valid path
        }

        current = current->next;
    }

    visit_board[node->position[1] - '1'][node->position[0] - 'A'] = NOT_VISITED; // restarting the position as NOT_VISITED on the board in case there was no valid path and return NULL
    freeList(newList);
    return NULL;
}