# Chemistry Solver

A C++ command-line tool that balances chemical equations and then solves the stoichiometry: given one known quantity, it computes the mass, moles, and gas volume of every other species in the reaction.

Written from scratch with no external libraries — the linear algebra, the exact-fraction arithmetic, and the formula parser are all hand-rolled.

## What it does

Give it an unbalanced equation:

```
Introdu ecuatia pe care vrei sa o egalez: Fe + O2 = Fe2O3
```

It balances the equation, then asks which species you know a quantity for, whether that quantity is a mass, a volume, or a mole count, and how much of it there is. It prints the balanced equation along with molar masses, masses, moles, and volumes for every species.

> Prompts are currently in Romanian.

## How it works

Balancing a chemical equation is a linear algebra problem, and that's how the program treats it:

1. **Parse** — the formula string is split on `+` and `=` into species, and each species is broken into its constituent elements and subscripts.
2. **Build the matrix** — each element becomes a row and each species a column, giving a homogeneous system where the unknowns are the stoichiometric coefficients.
3. **Find the rank** — Gaussian elimination determines the rank and which rows and columns are independent, since the system is underdetermined by construction (a balanced equation is unique only up to scale).
4. **Solve with determinants** — coefficients are recovered via Cramer's rule, computing determinants of the reduced system.
5. **Keep it exact** — every coefficient is carried as a `fraction` of integers rather than a floating-point value, so the result is exact and reduces to the smallest whole-number coefficients with no rounding drift.
6. **Stoichiometry** — molar masses are computed from a built-in table covering the periodic table, then the known quantity propagates to every other species by mole ratio. Gas volumes use the molar volume at STP (22.4 L/mol).

## Building

```bash
git clone https://github.com/MoloDani/Chemistry_program.git
cd Chemistry_program
g++ -std=c++17 -O2 *.cpp -o chem
./chem
```

Requires only a C++ compiler.

## Source layout

| File | Responsibility |
|---|---|
| `main.cpp` | Entry point; wires the three phases together |
| `input.cpp` | Reads the equation and splits it into species |
| `translateProb.cpp` | Parses formulas into element/subscript counts and builds the matrix |
| `rang.cpp` | Rank computation by Gaussian elimination |
| `det.cpp` | Determinant computation |
| `solution.cpp` | Solves for the coefficients via Cramer's rule |
| `solveChemProblem.cpp` | Molar mass table and the mass/moles/volume calculations |
| `fraction.h` | Exact rational arithmetic |
| `config.h` | Size limits |

## Roadmap

- [ ] English translation of the prompts, with a language flag
- [ ] Labelled output instead of raw aligned columns
- [ ] Support for parentheses in formulas, e.g. `Ca(OH)2`
- [ ] Hydrates (`CuSO4·5H2O`) and charged species
- [ ] Limiting-reagent detection when more than one quantity is known
- [ ] Non-STP conditions via the ideal gas law
- [ ] Clearer errors for unbalanceable or malformed equations
