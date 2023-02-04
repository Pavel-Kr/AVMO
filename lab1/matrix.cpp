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
	cout << "Результат:\n";
	printGaussAnswer();
	return;
}
