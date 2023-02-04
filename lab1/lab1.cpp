#include "fraction.h"
#include "matrix.h"

int main()
{
    setlocale(LC_ALL, "rus");
    try {
        Matrix matrix;
        matrix.initFromFile("matrix.txt");
        cout << "Исходная матрица:\n";
        matrix.print();
        matrix.gauss();
    }
    catch (const char* msg) {
        cout << "Error: " << msg << endl;
    }
}