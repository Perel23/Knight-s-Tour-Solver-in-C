#ifndef FINAL_PROJECT_FOR_REAL_FILES_H
#define FINAL_PROJECT_FOR_REAL_FILES_H
#ifndef CHESS_PROJECT_FILES_H
#define CHESS_PROJECT_FILES_H

#ifndef UNTITLED_FILES_H
#define UNTITLED_FILES_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_SIZE 5

typedef char chessPos[2];

struct _treeNodeListCell;

typedef struct _chessPosCell {
    chessPos position;
    struct _chessPosCell *next;
} chessPosCell;

typedef struct _chessPosList {
    chessPosCell *head;
    chessPosCell *tail;
} chessPosList;

typedef struct {
    char row;
    char col;
} chessSquare;

typedef struct _chessPosArray
{
    unsigned int size;
    chessPos *positions;
} chessPosArray;

typedef struct _treeNodeList {
    struct _treeNodeListCell *head;
    struct _treeNodeListCell *tail;
} treeNodeList;

typedef struct _treeNode{
    chessPos position;
    treeNodeList next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
    treeNode *node;
    struct _treeNodeListCell *next;
} treeNodeListCell;

typedef struct _pathTree {
    treeNode *root;
} pathTree;

///////////////////////////////////////////////////////////////////////////-Question 1 Functions-///////////////////////////////////////////////////////////////////////////
chessPosArray ***validKnightMoves(); // the function generates all the valid knight moves for each position on the chessboard

///////////////////////////////////////////////////////////////////////////-Question 2 Functions-///////////////////////////////////////////////////////////////////////////
void initializeBoard(chessSquare board[BOARD_SIZE][BOARD_SIZE]); // the function initialize the chess board with default positions
void removeListNode(chessPosCell *prev); // the function removes a node from a chessPosList
void removeDup(chessPosList *lst); // the function removes duplicate positions from a chessPosList
void display(chessPosList *lst); // the function display the chess board with the positions from the list, numbered by their index in the list


////////////////////////////////////////////////////////////////////////-Question 3 Functions-///////////////////////////////////////////////////////////////////////////
treeNode *createTreeNode(chessPos position); // creating a new TreeNode
void addTreeNodeListCell(treeNodeList *list, treeNode *node); // adding a new node to the given ListCell
int isInPath(chessPos *path, int pathLen, chessPos pos); // the function checks if the given ChessPos has already been visited in the path before
void buildPaths(treeNode *root, chessPosArray ***movesArray, chessPos *path, int pathLen); // the function gets a tree root and builds recursively the tree that contains the possible paths for a given ChessPos
pathTree findAllPossibleKnightPaths( chessPos *startingPosition); // the function gets a specific position on the board and returns a tree that represents all the possible paths for a knight from this position (without round paths)

////////////////////////////////////////////////////////////////////////-Question 4 Functions-///////////////////////////////////////////////////////////////////////////
void makeEmptyList(chessPosList *list); // the function an empty list of chess positions
void addNodeToEnd(chessPosList *lst, chessPosCell *node); // the function adds a node to the end of a chessPosList
void addNewPositionToEnd(chessPosList *lst, chessPos pos); // the function creates a new node that holds the data of pos, and adds it to the end of a chessPosList
void addPosToBoard(int **board, chessPos pos); // the function marks the position of pos  as visited in the board
void freeBoard(int **board, int rows); // the function frees memory allocated for the board
bool isAllBoardVisited(int **board); // the function checks if all the positions on the board have been visited
chessPosList *copyList(chessPosList *lst); // the function copies a chessPosList into a new list
void freeList(chessPosList *lst); // the function frees chessPosList
bool isPosNotVisited(chessPos pos, int **board); // the function checks if a position has not been visited
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree); // the function gets a position and returns a path the covers all the board (if there isn't a path, the function returns NULL)
chessPosList *findKnightPathCoveringAllBoardHelper(treeNode *node, chessPosList *lst, int **visit_board); // helper function for findKnightPathCoveringAllBoard

#endif //UNTITLED_FILES_H


#endif //CHESS_PROJECT_FILES_H
#endif //FINAL_PROJECT_FOR_REAL_FILES_H
