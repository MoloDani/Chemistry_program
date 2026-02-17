#include "solution.h"
#include "rang.h"
#include "det.h"
#include "config.h"
#include "fraction.h"
#include <iostream>

extern int n, m, **mat, *row, *col, **matAns, *firstPart;
extern char **elements;

int determinant, **auxMat = new int *[mxN + 1], coef[mxN];

fraction *ansMat = new fraction[mxN + 1];

fraction solve(int collumn, int rang)
{
    fraction auxAns;
    for (int i = 1; i <= rang; i++)
        auxMat[i][collumn] = coef[row[i]];

    auxAns = {det(rang, auxMat), determinant};

    for (int i = 1; i <= rang; i++)
        auxMat[i][collumn] = mat[row[i]][col[collumn]];

    return auxAns;
}

bool isInCol(int j, int rangMaxim)
{
    for (int i = 1; i <= rangMaxim; i++)
        if (col[i] == j)
            return true;
    return false;
}

void solution()
{
    int ind, rangMaxim = rangMatrix(n, m);
    for (int i = 1; i <= mxN; i++)
        auxMat[i] = new int[mxN];
    for (int i = 1; i <= rangMaxim; i++)
        for (int j = 1; j <= rangMaxim; j++)
            auxMat[i][j] = mat[row[i]][col[j]];

    // for (int i = 1; i <= rangMaxim; i++)
    // {
    //     for (int j = 1; j <= rangMaxim; j++)
    //         std::cout << auxMat[i][j] << " ";
    //     std::cout << "\n";
    // }

    for (int i = 1; i <= n; i++)
    {
        ind = 1;
        for (int j = 1; j <= m; j++)
        {
            if (isInCol(j, rangMaxim))
                ind++;
            else
            {
                ansMat[j] = 1;
                coef[i] -= mat[i][j];
            }
        }
    }

    determinant = det(rangMaxim, auxMat);

    for (int i = 1; i <= rangMaxim; i++)
    {
        ansMat[col[i]] = solve(i, rangMaxim);
    }

    int auxCoef = 1;

    for (int i = 1; i <= m; i++)
    {
        auxCoef = auxCoef * ansMat[i].denominator / gcd(auxCoef, ansMat[i].denominator);
    }

    for (int i = 1; i <= m; i++)
    {
        ansMat[i] = ansMat[i] * auxCoef;
    }

    // for (int i = 1; i <= m; i++)
    // {
    //     if (ansMat[i].numerator != 1)
    //         std::cout << ansMat[i];
    //     std::cout << elements[i];
    //     if (i == m)
    //         continue;

    //     if (firstPart[i] != firstPart[i + 1] && firstPart[i + 1])
    //         std::cout << " = ";
    //     else
    //         std::cout << " + ";
    // }

    return;
}