#include "rang.h"
#include "det.h"
#include "config.h"
#include <iostream>

extern int **mat;

int **matAns = new int *[mxN + 1];
int *row = new int[mxN], *col = new int[mxN];

void selectionInsert(int *v, int n, int val)
{
    int aux = n;
    while (aux > 1 && v[aux - 1] > val)
    {
        v[aux] = v[aux - 1];
        aux--;
    }

    v[aux] = val;
}

bool valUsed(int *v, int n, int val)
{
    for (int i = 1; i <= n; i++)
        if (v[i] == val)
            return true;
    return false;
}

bool verifySetUp(int i, int j, int n)
{
    int auxRow[mxN + 2], auxCol[mxN + 2];
    for (int i = 1; i < n; i++)
        auxRow[i] = row[i];
    for (int i = 1; i < n; i++)
        auxCol[i] = col[i];
    auxRow[n] = 0;
    auxCol[n] = 0;

    selectionInsert(auxRow, n, i);
    selectionInsert(auxCol, n, j);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            matAns[i][j] = mat[auxRow[i]][auxCol[j]];

    return (det(n, matAns) != 0);
}

int rangMatrix(int n, int m)
{
    int rang;
    for (int i = 1; i <= mxN; i++)
        matAns[i] = new int[mxN + 1];
    bool searching, finished = false;
    int rangMax = (n < m ? n : m);

    for (rang = 0; rang < rangMax && !finished; rang++)
    {
        searching = true;
        for (int i = 1; i <= n && searching; i++)
        {
            if (valUsed(row, rang, i))
                continue;
            for (int j = 1; j <= m && searching; j++)
            {
                if (valUsed(col, rang, j))
                    continue;

                if (verifySetUp(i, j, rang + 1))
                {
                    searching = false;

                    selectionInsert(row, rang + 1, i);
                    selectionInsert(col, rang + 1, j);
                }
            }
        }

        if (searching)
        {
            return rang;
        }
    }

    return rang;
}