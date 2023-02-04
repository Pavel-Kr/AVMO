#pragma once
#include <vector>
#include <fstream>
#include "Fraction.h"

class Matrix
{
	vector<vector<Fraction>> matrix;
	int rows, cols;
	void printGaussAnswer();
public:
	Matrix();
	void initFromFile(const char* filename);
	void print();
	void divideRowByFrac(int row, Fraction div);
	void swapRows(int row1, int row2);
	void subtractRowMultiplied(int target, int row, Fraction multiplier);
	int findMaxColIndex(int col, int start_row);
	void gauss();
};

