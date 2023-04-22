#include "TransportTask.h"

TransportTask::TransportTask()
{
	loadFromFile("matrix.txt");
	cout << "Loaded from file:" << endl;
	print();
	int total_needs = 0;
	int total_reserves = 0;
	for (int i = 0; i < suppliers; i++) {
		total_reserves += reserves[i];
	}
	for (int i = 0; i < consumers; i++) {
		total_needs += needs[i];
	}
	cout << "Total needs = " << total_needs << ", total reserves = " << total_reserves << endl;
	if (total_needs != total_reserves) {
		cout << "Open type task, make close" << endl;
		makeCloseType(total_needs, total_reserves);
		print();
	}
	else
		cout << "Close type task" << endl;
}

void TransportTask::makeCloseType(int total_needs, int total_reserves)
{
	if (total_needs < total_reserves) { // Make fictional consumer
		consumers++;
		for (int i = 0; i < suppliers; i++) {
			Cell cell;
			cell.price = 0;
			cell.amount = 0;
			cells[i].push_back(cell);
		}
		needs.push_back(total_reserves - total_needs);
	}
	else if (total_reserves < total_needs) { // Make fictional supplier
		vector<Cell> row;
		for (int i = 0; i < consumers; i++) {
			Cell cell;
			cell.price = 0;
			cell.amount = 0;
			row.push_back(cell);
		}
		cells.push_back(row);
		reserves.push_back(total_needs - total_reserves);
		suppliers++;
	}
}

bool TransportTask::loadFromFile(const char* filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Cannot open file " << filename << endl;
		return false;
	}
	string str;
	file >> suppliers;
	file >> consumers;
	cout << "Suppliers: " << suppliers << ", consumers: " << consumers << endl;
	for (int i = 0; i < suppliers; i++) {
		vector<Cell> row;
		for (int j = 0; j < consumers; j++) {
			Cell cell;
			file >> cell.price;
			cell.amount = 0;
			row.push_back(cell);
		}
		cells.push_back(row);
		int reserve;
		file >> reserve;
		reserves.push_back(reserve);
	}
	for (int i = 0; i < consumers; i++) {
		int need;
		file >> need;
		needs.push_back(need);
	}
	return true;
}

void TransportTask::print()
{
	cout << endl << "Value in cells is amount(price)" << endl << endl;
	for (int i = 0; i < consumers; i++) {
		cout << "\tB" << i + 1;
	}
	cout << "\tReserves" << endl;
	for (int i = 0; i < suppliers; i++) {
		cout << "A" << i + 1;
		for (int j = 0; j < consumers; j++) {
			cout << "\t" << cells[i][j].amount << "(" << cells[i][j].price << ")";
		}
		cout << "\t" << reserves[i] << endl;
	}
	cout << "Needs";
	for (int i = 0; i < consumers; i++) {
		cout << "\t" << needs[i];
	}
	cout << endl << endl;
}

void TransportTask::minCostMethod()
{
	do {
		int min_price = 1E9;
		int min_row = 0;
		int min_col = 0;
		bool found_min = false;
		for (int i = 0; i < suppliers; i++) {
			if (reserves[i] == 0) continue;
			for (int j = 0; j < consumers; j++) {
				if (needs[j] == 0) continue;
				if (cells[i][j].price == 0 && found_min) continue;
				if (cells[i][j].price < min_price) {
					min_price = cells[i][j].price;
					min_row = i;
					min_col = j;
					found_min = true;
				}
			}
		}
		int min_amount = (reserves[min_row] < needs[min_col]) ? reserves[min_row] : needs[min_col];
		cells[min_row][min_col].amount = min_amount;
		reserves[min_row] -= min_amount;
		needs[min_col] -= min_amount;
		print();
	} while (undistributedGoods() > 0);
	cout << "Total cost = " << totalCost() << endl;
}

int TransportTask::undistributedGoods()
{
	int goods = 0;
	for (int i = 0; i < suppliers; i++) {
		goods += reserves[i];
	}
	for (int i = 0; i < consumers; i++) {
		goods += needs[i];
	}
	return goods;
}

int TransportTask::totalCost()
{
	int total = 0;
	for (int i = 0; i < suppliers; i++) {
		for (int j = 0; j < consumers; j++) {
			total += cells[i][j].price * cells[i][j].amount;
		}
	}
	return total;
}
