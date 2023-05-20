#pragma once
#include "matrix.h"
#include "utils.h"

class SimplexMethod : Matrix
{
	int z_row;
	Permutation basis_vars;

	void fixZRow();
	void simplexGauss();
	void reorderBasis();
	void simplexMakeIdentity();
	bool isReference();
	Permutation findRefPlan();
	bool simplexStep();
	void checkMultipleSolutions();
	void printSolution();

public:
	SimplexMethod();
	void initFromFile(const char* filename);
	void print();
	void solve();
};

