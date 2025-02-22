#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void main()
{
    int columnNum;
    chessPos cp;
    pathTree cpTree;
    chessPosList *cpList;
    scanf(" %c", &cp[0]);
    scanf(" %d", &columnNum);
    if (cp[0] < 'A' || cp[0] > 'E' || columnNum > 5 || columnNum < 1)
    {
        printf("Invalid input");
    }
    else
    {
        cp[1] = columnNum + '0';
        cpTree = findAllPossibleKnightPaths(&cp);
        cpList = findKnightPathCoveringAllBoard(&cpTree);
        if (cpList == NULL) {
            printf("No knight's tour");
            return;
        }
        display(cpList);

        // Free the allocated memory for the list
        chessPosCell *curr = cpList->head;
        while (curr != NULL) {
            chessPosCell *temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(cpList);
    }

}