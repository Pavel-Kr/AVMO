#include <locale>
#include "matrix.h"


int main()
{
    try {
        setlocale(LC_ALL, "rus");
        Matrix matrix;
        matrix.initFromFile("matrix.txt");
        matrix.basis();
    }
    catch (const char* msg) {
        cout << msg;
    }
}
