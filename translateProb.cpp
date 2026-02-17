#include "translateProb.h"
#include "config.h"
#include <iostream>
#include <map>

struct elGr
{
    char *el;
    int coef;
};

extern char **elements;
extern int noElem, *firstPart, n, m;

extern int **mat;
int indexElem;

char diffEl[mxN][3];
int noDifElem = 0;
bool elemExists[1000000];

std::map<int, int> coefElemSubst[mxN];

int toKey(const char *el)
{
    if (el[1] == '\0')
        return el[0] * 1000;
    return el[0] * 1000 + el[1];
}

char *toEl(int n)
{
    char *ans = new char;
    ans[0] = char(n / 1000);
    ans[1] = '\0';
    ans[2] = '\0';
    if (n % 1000 != 0)
        ans[1] = char(n % 1000);
    return ans;
}

elGr computeElem(int ind)
{
    // TODO: verify if next character is another element(elements without uppper/lower)
    char *elem = new char;
    int coeficient = 0, indAux = 0;
    while ((elements[ind][indexElem] >= 'a' && elements[ind][indexElem] <= 'z') || (elements[ind][indexElem] >= 'A' && elements[ind][indexElem] <= 'Z') && elements[ind][indexElem] != '\0')
        elem[indAux++] = elements[ind][indexElem++];

    elem[indAux++] = '\0';

    while (elements[ind][indexElem] >= '0' && elements[ind][indexElem] <= '9' && elements[ind][indexElem] != '\0')
        coeficient = coeficient * 10 + (elements[ind][indexElem++] - '0');

    if (coeficient == 0)
        coeficient = 1;
    return elGr{elem, coeficient};
}

bool existingElement(char *el)
{
    bool exista = false;
    for (int i = 1; i <= noDifElem; i++)
    {
        if (el[0] == diffEl[i][0])
        {
            if (el[1] == '\0')
                return true;

            if (el[1] == diffEl[i][1])
                return true;
        }
    }

    return false;
}

void addElement(char *el)
{
    noDifElem++;
    int j;
    for (j = 0; j <= 2 && el[j] != '\0'; j++)
        diffEl[noDifElem][j] = el[j];

    diffEl[noDifElem][j] = '\0';
}

std::map<int, int> computeParanthesis(char *el, int index)
{
    std::map<int, int> ans;
    while (el[index] != '\0')
    {
        int charParc = 0, coef = 0;
        if (el[index] == '(')
        {
            std::map<int, int> mapAux = computeParanthesis((el + index + 1), 0);
            for (auto x : mapAux)
                ans[x.first] += x.second;

            while (el[index] != ')')
                index++;
            index++;
            while (isdigit(el[index]))
                index++;
            continue;
        }

        char elAux[3];
        elAux[1] = '\0';
        elAux[2] = '\0';
        if (isupper(el[index]))
        {
            charParc++;
            elAux[0] = el[index];
            if (islower(el[index + 1]))
            {
                charParc++;
                elAux[1] = el[index + 1];
            }

            while (isdigit(el[index + charParc]))
            {
                coef = coef * 10 + (el[index + charParc] - '0');
                charParc++;
            }

            ans[toKey(elAux)] += (coef ? coef : 1);
            index += charParc;
        }
        else if (el[index] == ')')
        {
            index++;
            while (isdigit(el[index]))
            {
                coef = coef * 10 + (el[index] - '0');
                index++;
            }

            if (coef)
                for (auto x : ans)
                {
                    ans[x.first] *= coef;
                }
        }
    }

    return ans;
}

void translate()
{
    for (int i = 1; i <= noElem; i++)
    {
        std::map<int, int> aux = computeParanthesis(elements[i], 0);
        for (auto x : aux)
        {
            coefElemSubst[i][x.first] = x.second;
            if (!elemExists[x.first])
            {
                elemExists[x.first] = true;
                noDifElem++;
                char *auxiliar = toEl(x.first);
                diffEl[noDifElem][0] = auxiliar[0];
                if (auxiliar[1] != '\0')
                    diffEl[noDifElem][1] = auxiliar[1];
            }
        }
    }

    for (int i = 1; i <= noElem; i++)
        for (int j = 1; j <= noDifElem; j++)
            mat[j][i] = coefElemSubst[i][toKey(diffEl[j])] * firstPart[i];

    n = noDifElem;
    m = noElem;
}