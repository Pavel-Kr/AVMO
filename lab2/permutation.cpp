#include <iostream>
#include "permutation.h"

Permutation::Permutation(int n, int k)
{
	perm.resize(k);
	for (int i = 0; i < k; i++) {
		perm[i] = i;
	}
	this->k = k - 1;
	p = k - 1;
	this->n = n - 1;
}

bool Permutation::next()
{
	if (perm[k] < n) {
		p = k;
		perm[p]++;
		return true;
	}
	else {
		p--;
		if (p < 0) return false;
		perm[p]++;
		for (int i = p + 1; i <= k; i++) {
			perm[i] = perm[p] + (i - p);
		}
	}
	return true;
}

void Permutation::print()
{
	for (int i = 0; i < perm.size(); i++) {
		cout << perm[i] << " ";
	}
	cout << endl;
}

int Permutation::operator[](int index)
{
	if (index <= k) return perm[index];
	else throw "Index > length";
}

int Permutation::length()
{
	return k;
}
