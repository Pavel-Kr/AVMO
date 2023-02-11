#include "matrix.h"
#include <locale>

void Matrix::printGaussAnswer()
{
	for (int i = 0; i < rows; i++) {
		bool isAnswer = true;
		for (int j = i; j < cols - 1; j++) {
			if (matrix[i][j].isZero()) continue;
			if (matrix[i][j] == Fraction(1) && isAnswer) {
				cout << "x" << j + 1 << " = ";
				matrix[i][cols - 1].print();
			}
			else {
				if (matrix[i][j] < Fraction(0)) {
					cout << "+";
				}
				(-matrix[i][j]).print();
				cout << "*x" << j + 1 << "";
			}
		}
		cout << endl;
	}
}

void Matrix::save()
{
	for (int i = 0; i < rows; i++) {
		saved[i] = matrix[i];
	}
}

void Matrix::restore()
{
	for (int i = 0; i < rows; i++) {
		matrix[i] = saved[i];
	}
}

void swap(vector<int>& vec, int a, int b) {
	int tmp = vec[a];
	vec[a] = vec[b];
	vec[b] = tmp;
}

void sort2VectorsBy1st(vector<int>& vec1, vector<int>& vec2) {
	for (int i = 0; i < vec1.size() - 1; i++) {
		int min = vec1[i], min_index = i;
		for (int j = i + 1; j < vec1.size(); j++) {
			if (vec1[j] < min) {
				min = vec1[j];
				min_index = j;
			}
		}
		if (i != min_index) {
			swap(vec1, i, min_index);
			swap(vec2, i, min_index);
		}
	}
}

vector<int> Matrix::findBasisRows(Permutation perm)
{
	vector<int> total, columns, res;
	vector<bool> row_taken;
	for (int i = 0; i < rows; i++) {
		int column = perm[i];
		total.push_back(0);
		for (int j = 0; j < rows; j++) {
			if (!matrix[j][column].isZero()) total[i]++;
		}
		columns.push_back(column);
		row_taken.push_back(false);
		res.push_back(0);
	}
	sort2VectorsBy1st(total, columns);
	for (int i = 0; i < rows; i++) {
		int column = columns[i];
		for (int j = 0; j < rows; j++) {
			if (matrix[j][column].isZero()) continue;
			if (row_taken[j]) {
				total[i]--;
				if (total[i] == 0) {
					cout << "Нет базиса" << endl;
					res.clear();
					return res;
				}
			}
			else {
				res[i] = j;
				row_taken[j] = true;
				break;
			}
		}
	}
	sort2VectorsBy1st(columns, res);
	cout << "Строки базиса:" << endl;
	for (int i = 0; i < rows; i++) {
		cout << res[i] << " ";
	}
	cout << endl;
	return res;
}

bool Matrix::makeIdentity(Permutation perm)
{
	vector<int> basisRows = findBasisRows(perm);
	if (basisRows.empty()) return false;
	for (int i = 0; i < rows; i++) {
		int row = basisRows[i], col = perm[i];
		cout << "Деление строки " << row << " на ";
		matrix[row][col].print();
		cout << ":\n";
		divideRowByFrac(row, matrix[row][col]);
		print();
		cout << "Вычитание строки " << row << " из остальных строк:\n";
		for (int j = 0; j < rows; j++) {
			if (j == row) continue;
			subtractRowMultiplied(j, row, matrix[j][col]);
		}
		print();
	}
	return true;
}

void Matrix::printBasis()
{
	cout << "(";
	for (int i = 0; i < cols - 1; i++) {
		bool is_basis = false;
		int row = 0;
		for (int j = 0; j < rows; j++) {
			if (matrix[j][i].isZero()) continue;
			if (matrix[j][i] == Fraction(1) && !is_basis) {
				is_basis = true;
				row = j;
			}
			else {
				is_basis = false;
				break;
			}
		}
		if (is_basis) {
			matrix[row][cols - 1].print();
		}
		else {
			cout << 0;
		}
		if (i < cols - 2) {
			cout << ", ";
		}
	}
	cout << ")" << endl << endl;
}

Matrix::Matrix()
{
}

void Matrix::initFromFile(const char* filename)
{
	ifstream file(filename, ios::in);
	int rows, cols;
	file >> rows;
	file >> cols;
	this->rows = rows;
	this->cols = cols;
	for (int i = 0; i < rows; i++) {
		vector<Fraction> row;
		for (int j = 0; j < cols; j++) {
			int num;
			file >> num;
			row.push_back(Fraction(num));
		}
		matrix.push_back(row);
		saved.push_back(row);
	}
	file.close();
}

void Matrix::print()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j].print();
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::divideRowByFrac(int row, Fraction div)
{
	for (int i = 0; i < cols; i++) {
		matrix[row][i] /= div;
	}
}

void Matrix::swapRows(int row1, int row2)
{
	vector<Fraction> tmp = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = tmp;
}

void Matrix::subtractRowMultiplied(int target, int row, Fraction multiplier)
{
	vector<Fraction> tmp = matrix[row];
	for (int i = 0; i < cols; i++) {
		tmp[i] *= multiplier;
		matrix[target][i] -= tmp[i];
	}
}

int Matrix::findMaxColIndex(int col, int start_row)
{
	Fraction max = abs(matrix[start_row][col]);
	int max_index = start_row;
	for (int i = start_row; i < rows; i++) {
		if (max < abs(matrix[i][col])) {
			max = abs(matrix[i][col]);
			max_index = i;
		}
	}
	return max_index;
}

void Matrix::gauss()
{
	int col = 0;
	for (int i = 0; i < rows; i++) {
		int max_index = findMaxColIndex(col, i);
		if (i != max_index) {
			cout << "Переставление строк " << i << " и " << max_index << ":\n";
			swapRows(i, max_index);
			print();
		}
		else if (matrix[max_index][col].isZero()) {
			int tmp_col = col + 1;
			while (tmp_col < cols - 1) {
				max_index = findMaxColIndex(tmp_col, i);
				if (!matrix[max_index][tmp_col].isZero()) break;
				tmp_col++;
			}
			if (tmp_col == cols - 1) {
				if (!matrix[i][tmp_col].isZero()) {
					cout << "Решения нет" << endl;
					return;
				}
				rows = i;
				break;
			}
			else {
				cout << "Переставление строк " << i << " и " << max_index << ":\n";
				swapRows(i, max_index);
				print();
				col = tmp_col;
			}
		}
		cout << "Деление строки " << i << " на ";
		matrix[i][col].print();
		cout << ":\n";
		divideRowByFrac(i, matrix[i][col]);
		print();
		for (int j = 0; j < rows; j++) {
			if (j == i) continue;
			subtractRowMultiplied(j, i, matrix[j][col]);
		}
		cout << "Вычитание строки " << i << " из остальных строк:\n";
		print();
		col++;
	}
	/*cout << "Результат:\n";
	printGaussAnswer();*/
	return;
}

void Matrix::basis()
{
	gauss();
	cout << "Результат:" << endl;
	print();
	Permutation permutation(cols - 1, rows);
	do {
		cout << "Столбцы предполагаемого базиса" << endl;
		permutation.print();
		save();
		if (makeIdentity(permutation)) {
			cout << "Базис:" << endl;
			printBasis();
		}
		restore();
	} while (permutation.next());
}
