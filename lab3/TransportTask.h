#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
using namespace std;

typedef struct
{
	int price;
	int amount;
} Cell;

class TransportTask
{
private:
	vector<vector<Cell>> cells;
	vector<int> reserves;
	vector<int> needs;
	int consumers;
	int suppliers;

public:
	TransportTask();
	void makeCloseType(int total_needs, int total_reserves);
	bool loadFromFile(const char* filename);
	void print();
	void minCostMethod();
	int undistributedGoods();
	int totalCost();
};

