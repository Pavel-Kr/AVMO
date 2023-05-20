#include <iostream>
#include "SimplexMethod.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SimplexMethod simplex;
    simplex.initFromFile("matrix.txt");
    simplex.print();
    simplex.solve();
}
