#pragma once
#include <vector>
#include <fstream>
#include "Fraction.h"
#include "permutation.h"

class Matrix
{
	vector<vector<Fraction>> matrix;
	vector<vector<Fraction>> saved;
	int rows, cols;
	void printGaussAnswer();
	void save();
	void restore();
	vector<int> findBasisRows(Permutation perm);
	bool makeIdentity(Permutation perm);
	void printBasis();
public:
	Matrix();
	void initFromFile(const char* filename);
	void print();
	void divideRowByFrac(int row, Fraction div);
	void swapRows(int row1, int row2);
	void subtractRowMultiplied(int target, int row, Fraction multiplier);
	int findMaxColIndex(int col, int start_row);
	void gauss();
	void basis();
};