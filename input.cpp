#include <iostream>
#include "input.h"
#include "translateProb.h"
#include "config.h"
#include <map>

extern int **mat;

const int mxC = 100001;

char **elements = new char *[100];
int *firstPart = new int[mxN];
int noElem = 0;
char ecuation[mxC];

bool iCanContinue(int i)
{
    if (ecuation[i] == ' ')
        return true;
    return (ecuation[i] != '+' && ecuation[i] != '=');
}

char toUpper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch + ('A' - 'a');

    return ch;
}

void input()
{
    for (int i = 1; i <= 100; i++)
        elements[i] = new char[mxC];
    int ind = 1, l = 1;
    int inFirstPart = 1;
    std::cout << "Introdu ecuatia pe care vrei sa o egalez: ";
    std::cin.getline(ecuation, mxC - 1);

    while (ecuation[ind] != '\0')
    {
        int aux = 0;
        while (iCanContinue(ind) && ecuation[ind] != '\0')
            l++, ind++;

        noElem++;
        firstPart[noElem] = inFirstPart;
        for (int i = ind - l; i < ind; i++)
        {
            if (ecuation[i] == ' ')
                continue;
            elements[noElem][aux++] = ecuation[i];
        }
        elements[noElem][aux] = '\0';

        if (ecuation[ind] == '=')
            inFirstPart = -1;
        ind++;
        l = 0;
    }

    translate();
}