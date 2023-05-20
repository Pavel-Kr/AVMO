#pragma once
#include <vector>
#include <fstream>
#include "Fraction.h"
#include "permutation.h"

class Matrix
{
protected:
	vector<vector<Fraction>> matrix;
	vector<vector<Fraction>> saved;
	void printGaussAnswer();
	void save();
	void restore();
	vector<int> findBasisRows(Permutation perm);
	bool makeIdentity(Permutation perm);
	void swapRows(int row1, int row2);
	void subtractRowMultiplied(int target, int row, Fraction multiplier);
	void divideRowByFrac(int row, Fraction div);
	int findMaxColIndex(int col, int start_row);
	void printBasis();
public:
	int rows, cols;
	Matrix();
	void initFromFile(const char* filename);
	void print();
	void gauss();
	void basis();
	vector<Fraction> operator[](int index);
};