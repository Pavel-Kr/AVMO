#pragma once
#include <vector>
using namespace std;

class Permutation
{
	int p, n, k;
public:
	vector<int> perm;

	Permutation();
	Permutation(int n, int k);
	bool next();
	void print();
	int operator [](int index);
	int length();
	void set(int index, int value);
	bool contains(int value);
};