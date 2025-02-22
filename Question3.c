#include "files.h"

treeNode *createTreeNode(chessPos position) // creating a new TreeNode
{
    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode)); // allocating memory for the node
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->next_possible_positions.head = newNode->next_possible_positions.tail = NULL; // Initializing an empty list
    newNode->position[0] = position[0]; // updating the position of the node with the ChessPos given as input
    newNode->position[1] = position[1];
    return newNode;
}

void addTreeNodeListCell(treeNodeList *list, treeNode *node) // adding a new node to the given ListCell
{
    treeNodeListCell *newCell = (treeNodeListCell *)malloc(sizeof(treeNodeListCell)); // allocating memory for the node
    if (!newCell)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newCell->node = node; // updating the node with the given treeNode from the input
    newCell->next = NULL; // updating the next as NULL

    if (list->tail) // if the ListCell is not empty, the node wil be added to the end of the list
    {
        list->tail->next = newCell;
    }
    else // if the ListCell is empty, the node will be added as the first node
    {
        list->head = newCell;
    }

    list->tail = newCell; // in any situation, the node will be updated as the tail
}

int isInPath(chessPos *path, int pathLen, chessPos pos) // the function checks if the given ChessPos has already been visited in the path before
{
    for (int i = 0; i < pathLen; i++)
    {
        if (path[i][0] == pos[0] && path[i][1] == pos[1])
        {
            return 1; // return 1 if the pos appears in the path
        }
    }
    return 0;
}

void buildPaths(treeNode *root, chessPosArray ***movesArray, chessPos *path, int pathLen) // the function gets a tree root and builds recursively the tree that contains the possible paths for a given ChessPos
{
    chessPosArray *posArray = movesArray[root->position[0] - 'A'][root->position[1] - '1']; // using the function from the first question, the program gets the relevant possible moves for the given position

    for (int i = 0; i < posArray->size; i++) // the program goes over the array of the possible positions
    {
        if (!isInPath(path, pathLen, posArray->positions[i])) // the program checks if the position of the current index was already in the path, if not the program adds it to the ListCell as a child
        {
            treeNode *child = createTreeNode(posArray->positions[i]);
            addTreeNodeListCell(&root->next_possible_positions, child);

            path[pathLen][0] = posArray->positions[i][0];
            path[pathLen][1] = posArray->positions[i][1];

            buildPaths(child, movesArray, path, pathLen + 1); // the program runs again over each child that have been added these paths to the tree
        }
    }
}

pathTree findAllPossibleKnightPaths(chessPos *startingPosition) // the function gets a specific position on the board and returns a tree that represents all the possible paths for a knight from this position (without round paths)
{
    chessPosArray ***movesArray = validKnightMoves();
    pathTree tree;
    tree.root = createTreeNode(*startingPosition); // initializing the tree by updating starting position
    chessPos path[BOARD_SIZE * BOARD_SIZE];
    path[0][0] = startingPosition[0][0];
    path[0][1] = startingPosition[0][1];
    buildPaths(tree.root, movesArray, path, 1); // starting to build the tree by giving the root, all the possible knight moves, and the start of the path
    return tree; // returning the paths tree after building it
}