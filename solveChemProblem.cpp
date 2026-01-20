#include <iostream>
#include "solveChemProblem.h"
#include "translateProb.h"
#include "fraction.h"
#include <map>
#include "config.h"
#include <string.h>

extern int noElem, *firstPart;
extern fraction *ansMat;
extern std::map<int, int> coefElemSubst[mxN];
extern char **elements;

std::map<int, int> molarMass;
int solMass[mxN + 1];
double realMass[mxN], mols[mxN], volume[mxN];

void initMolarMass()
{
    molarMass[toKey("H")] = 1;
    molarMass[toKey("He")] = 4;
    molarMass[toKey("Li")] = 7;
    molarMass[toKey("Be")] = 9;
    molarMass[toKey("B")] = 11;
    molarMass[toKey("C")] = 12;
    molarMass[toKey("N")] = 14;
    molarMass[toKey("O")] = 16;
    molarMass[toKey("F")] = 19;
    molarMass[toKey("Ne")] = 20;
    molarMass[toKey("Na")] = 23;
    molarMass[toKey("Mg")] = 24;
    molarMass[toKey("Al")] = 27;
    molarMass[toKey("Si")] = 28;
    molarMass[toKey("P")] = 31;
    molarMass[toKey("S")] = 32;
    molarMass[toKey("Cl")] = 35;
    molarMass[toKey("Ar")] = 40;
    molarMass[toKey("K")] = 39;
    molarMass[toKey("Ca")] = 40;
    molarMass[toKey("Sc")] = 45;
    molarMass[toKey("Ti")] = 48;
    molarMass[toKey("V")] = 51;
    molarMass[toKey("Cr")] = 52;
    molarMass[toKey("Mn")] = 55;
    molarMass[toKey("Fe")] = 56;
    molarMass[toKey("Co")] = 59;
    molarMass[toKey("Ni")] = 59;
    molarMass[toKey("Cu")] = 64;
    molarMass[toKey("Zn")] = 65;
    molarMass[toKey("Ga")] = 70;
    molarMass[toKey("Ge")] = 73;
    molarMass[toKey("As")] = 75;
    molarMass[toKey("Se")] = 79;
    molarMass[toKey("Br")] = 80;
    molarMass[toKey("Kr")] = 84;
    molarMass[toKey("Rb")] = 85;
    molarMass[toKey("Sr")] = 88;
    molarMass[toKey("Y")] = 89;
    molarMass[toKey("Zr")] = 91;
    molarMass[toKey("Nb")] = 93;
    molarMass[toKey("Mo")] = 96;
    molarMass[toKey("Tc")] = 98;
    molarMass[toKey("Ru")] = 101;
    molarMass[toKey("Rh")] = 103;
    molarMass[toKey("Pd")] = 106;
    molarMass[toKey("Ag")] = 108;
    molarMass[toKey("Cd")] = 112;
    molarMass[toKey("In")] = 115;
    molarMass[toKey("Sn")] = 119;
    molarMass[toKey("Sb")] = 122;
    molarMass[toKey("Te")] = 128;
    molarMass[toKey("I")] = 127;
    molarMass[toKey("Xe")] = 131;
    molarMass[toKey("Cs")] = 133;
    molarMass[toKey("Ba")] = 137;
    molarMass[toKey("La")] = 139;
    molarMass[toKey("Ce")] = 140;
    molarMass[toKey("Pr")] = 140;
    molarMass[toKey("Nd")] = 144;
    molarMass[toKey("Pm")] = 145;
    molarMass[toKey("Sm")] = 150;
    molarMass[toKey("Eu")] = 152;
    molarMass[toKey("Gd")] = 157;
    molarMass[toKey("Tb")] = 159;
    molarMass[toKey("Dy")] = 162;
    molarMass[toKey("Ho")] = 165;
    molarMass[toKey("Er")] = 167;
    molarMass[toKey("Tm")] = 169;
    molarMass[toKey("Yb")] = 173;
    molarMass[toKey("Lu")] = 175;
    molarMass[toKey("Hf")] = 178;
    molarMass[toKey("Ta")] = 181;
    molarMass[toKey("W")] = 184;
    molarMass[toKey("Re")] = 186;
    molarMass[toKey("Os")] = 190;
    molarMass[toKey("Ir")] = 192;
    molarMass[toKey("Pt")] = 195;
    molarMass[toKey("Au")] = 197;
    molarMass[toKey("Hg")] = 201;
    molarMass[toKey("Tl")] = 204;
    molarMass[toKey("Pb")] = 207;
    molarMass[toKey("Bi")] = 209;
    molarMass[toKey("Po")] = 209;
    molarMass[toKey("At")] = 210;
    molarMass[toKey("Rn")] = 222;
    molarMass[toKey("Fr")] = 223;
    molarMass[toKey("Ra")] = 226;
    molarMass[toKey("Ac")] = 227;
    molarMass[toKey("Th")] = 232;
    molarMass[toKey("Pa")] = 231;
    molarMass[toKey("U")] = 238;
    molarMass[toKey("Np")] = 237;
    molarMass[toKey("Pu")] = 244;
    molarMass[toKey("Am")] = 243;
    molarMass[toKey("Cm")] = 247;
    molarMass[toKey("Bk")] = 247;
    molarMass[toKey("Cf")] = 251;
    molarMass[toKey("Es")] = 252;
    molarMass[toKey("Fm")] = 257;
    molarMass[toKey("Md")] = 258;
    molarMass[toKey("No")] = 259;
    molarMass[toKey("Lr")] = 262;
    molarMass[toKey("Rf")] = 267;
    molarMass[toKey("Db")] = 270;
    molarMass[toKey("Sg")] = 271;
    molarMass[toKey("Bh")] = 270;
    molarMass[toKey("Hs")] = 277;
    molarMass[toKey("Mt")] = 278;
    molarMass[toKey("Ds")] = 281;
    molarMass[toKey("Rg")] = 282;
    molarMass[toKey("Cn")] = 285;
    molarMass[toKey("Nh")] = 286;
    molarMass[toKey("Fl")] = 289;
    molarMass[toKey("Mc")] = 290;
    molarMass[toKey("Lv")] = 293;
    molarMass[toKey("Ts")] = 294;
    molarMass[toKey("Og")] = 294;
}

int mod(int n)
{
    return (n < 0 ? -n : n);
}

void calcMolarMass(int i)
{
    int ans = 0;
    for (auto x : coefElemSubst[i])
    {
        ans += molarMass[x.first] * x.second;
    }

    solMass[i] = mod(ans * ansMat[i].numerator);
}

void solveChemProblem()
{
    initMolarMass();
    int indKnown, quantity, typeKnown;
    std::cout << "Din ce solutie stii cantitatea?";
    std::cin >> indKnown;
    std::cout << "Ce cunosti? (1-masa, 2-volum, 3-moli)";
    std::cin >> typeKnown;
    std::cout << "Cata solutie este?";
    std::cin >> quantity;

    for (int i = 1; i <= noElem; i++)
    {
        calcMolarMass(i);
    }

    if(typeKnown == 1){
        realMass[indKnown] = quantity;
        volume[indKnown] = realMass[indKnown] * solMass[indKnown];
        mols[indKnown] = realMass[indKnown] / solMass[indKnown];
    }
    else if(typeKnown == 2){
        volume[indKnown] = quantity;
        mols[indKnown] = volume[indKnown] / 22.4; // at STP
        realMass[indKnown] = mols[indKnown] * solMass[indKnown];
    }
    else if(typeKnown == 3){
        mols[indKnown] = quantity;
        realMass[indKnown] = mols[indKnown] * solMass[indKnown];
        volume[indKnown] = mols[indKnown] * 22.4; // at STP
    }

    for (int i = 1; i <= noElem; i++)
    {
        if (i == indKnown)
            continue;

        realMass[i] = realMass[indKnown] * solMass[i] / solMass[indKnown];
    }

    for (int i = 1; i <= noElem; i++)
    {
        if (i == indKnown)
            continue;

        mols[i] = realMass[i] / solMass[i];
        volume[i] = mols[i] * 22.4; // at STP
    }

    // TODO: calculate the answer in mols, liters...



    std::cout << "\n";
    for (int i = 1; i <= noElem; i++)
        std::cout << solMass[i] << "   ";
    std::cout << "\n";
    for (int i = 1; i <= noElem; i++)
    {
        if (ansMat[i].numerator != 1)
            std::cout << ansMat[i];
        std::cout << elements[i];
        if (i == noElem)
            continue;

        if (firstPart[i] != firstPart[i + 1] && firstPart[i + 1])
            std::cout << " = ";
        else
            std::cout << " + ";
    }
    std::cout << "\n";
    for (int i = 1; i <= noElem; i++)
        std::cout << realMass[i] << "   ";
    std::cout << "\n";
    for (int i = 1; i <= noElem; i++)
        std::cout << mols[i] << "   ";
    std::cout << "\n";
    for (int i = 1; i <= noElem; i++)
        std::cout << volume[i] << "   ";
    std::cout << "\n";
}