#include <iostream>
#include "rang.h"
#include "det.h"
#include "solution.h"
#include "config.h"
#include "input.h"
#include "fraction.h"
#include "translateProb.h"
#include "solveChemProblem.h"

int **mat = new int *[mxN + 1];
int n, m;

extern int *row, *col;

extern int **matAns;

int main()
{
    for (int i = 1; i <= mxN; i++)
        mat[i] = new int[mxN];
    input();

    solution();

    solveChemProblem();

    return 0;
}
