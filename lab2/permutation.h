#pragma once
#include <vector>
using namespace std;

class Permutation
{
	vector<int> perm;
	int p, n, k;
public:
	Permutation(int n, int k);
	bool next();
	void print();
	int operator [](int index);
	int length();
};