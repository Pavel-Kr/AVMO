#include "SimplexMethod.h"

void SimplexMethod::fixZRow()
{
	for (int i = 0; i <= basis_vars.length(); i++) {
		subtractRowMultiplied(z_row, i, matrix[z_row][basis_vars[i]]);
	}
}

void SimplexMethod::simplexGauss()
{
	rows--;
	gauss();
	rows++;
}

void SimplexMethod::reorderBasis()
{
	vector<int> basisRows = findBasisRows(basis_vars);
	/*cout << "Basis rows:" << endl;
	for (int i = 0; i < basisRows.size(); i++) {
		cout << basisRows[i] << " ";
	}
	cout << endl;*/
	sort2VectorsBy1st(basisRows, basis_vars.perm);
}

void SimplexMethod::simplexMakeIdentity()
{
	makeIdentity(basis_vars);
	reorderBasis();
}

bool SimplexMethod::isReference()
{
	for (int i = 0; i < rows; i++) {
		if (matrix[i][cols - 1] < Fraction(0)) return false;
	}
	return true;
}

Permutation SimplexMethod::findRefPlan()
{
	simplexGauss();
	print();
	Permutation result(cols - 1, rows - 1);
	rows--;
	do {
		//cout << "Столбцы предполагаемого базиса" << endl;
		//result.print();
		save();
		if (makeIdentity(result)) {
			cout << "\nБазис:\n";
			printBasis();
			if (isReference()) {
				rows++;
				fixZRow();
				return result;
			}
		}
		restore();
	} while (result.next());
	rows++;
	return Permutation(0, 0);
}

SimplexMethod::SimplexMethod()
{
}

void SimplexMethod::initFromFile(const char* filename)
{
	Matrix::initFromFile(filename);
	z_row = rows - 1;
	for (int i = 0; i < cols; i++) {
		if (matrix[z_row][i].isZero()) continue;
		matrix[z_row][i] = -matrix[z_row][i];
	}
	Permutation tmp(cols - 1, rows - 1);
	basis_vars = tmp;
}

void SimplexMethod::print()
{
	cout << "\nСимплекс таблица:\n";
	cout << "\nБП\t1\t";
	for (int i = 0; i < cols - 1; i++) {
		cout << "x" << i + 1 << "\t";
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		if (i == rows - 1) cout << "Z";
		else cout << "x" << basis_vars[i] + 1;
		cout << "\t";
		matrix[i][cols - 1].print();
		for (int j = 0; j < cols - 1; j++) {
			cout << "\t";
			matrix[i][j].print();
		}
		cout << endl;
	}
}

void SimplexMethod::solve()
{
	cout << "\nНаходим опорное решение методом Жордана - Гауссаn\n";
	basis_vars = findRefPlan();
	rows--;
	if (basis_vars.length() < 0) {
		cout << "\nОпорный план не найден, решения не существует\n";
		return;
	}
	reorderBasis();
	rows++;
	cout << "\nРезультат:\n";
	print();
	while (simplexStep())
	{
		print();
	}
}

bool SimplexMethod::simplexStep()
{
	rows--;
	Fraction min_z = 0;
	int min_col = 0;
	bool solutionExists = false;

	for (int i = 0; i < cols - 1; i++) {
		if (matrix[z_row][i] < min_z) {
			min_z = matrix[z_row][i];
			min_col = i;
		}
		if (!matrix[z_row][i].isZero()) solutionExists = true;
	}
	if (!solutionExists) {
		cout << "\nРешения не существует\n";
		return false;
	}
	if (min_z == 0 && min_col == 0) {
		rows++;
		//basis_vars.print();
		cout << "\nНайдено оптимальное решение:\n";
		printSolution();
		rows--;
		checkMultipleSolutions();
		return false;
	}
	cout << "\nМинимальный столбец: " << min_col + 1 << ", значение в Z строке = ";
	matrix[z_row][min_col].print();
	cout << endl;
	Fraction min_rel = 10000000;
	int min_row = 0;
	solutionExists = false;
	cout << "\nСимплекс-отношения:\n\n";
	for (int i = 0; i < rows; i++) {
		Fraction rel = -1;
		// Free variable and element in column must be positive
		if (!matrix[i][cols - 1].isZero() && Fraction(0) < matrix[i][min_col]) {
			rel = matrix[i][cols - 1] / matrix[i][min_col];
			if (rel < min_rel) {
				min_rel = rel;
				min_row = i;
			}
			solutionExists = true;
		}
		rel.print();
		cout << " ";
		
	}
	cout << endl;
	if (!solutionExists) {
		cout << "\nРешения не существует\n";
		return false;
	}
	cout << "\nМинимальное симплекс-отношение = ";
	min_rel.print();
	cout << " в строке " << min_row + 1 << endl;
	//basis_vars.print();
	basis_vars.set(min_row, min_col);
	simplexMakeIdentity();
	rows++;
	fixZRow();
	//print();
	return true;
}

void SimplexMethod::checkMultipleSolutions()
{
	for (int i = 0; i < cols - 1; i++) {
		if (matrix[z_row][i].isZero() && !basis_vars.contains(i)) {
			// There are infinitely many solutions, find another one
			cout << "\nСуществует бесконечное количество решений, найдем еще одно\n";
			int min_col = i;
			cout << "\nМинимальный столбец: " << min_col + 1 << ", значение в Z строке = ";
			matrix[z_row][min_col].print();
			cout << endl;
			Fraction min_rel = 10000000;
			int min_row = 0;
			cout << "\nСимплекс-отношения:\n\n";
			for (int i = 0; i < rows; i++) {
				Fraction rel = -1;
				// Free variable and element in column must be positive
				if (!matrix[i][cols - 1].isZero() && Fraction(0) < matrix[i][min_col]) {
					rel = matrix[i][cols - 1] / matrix[i][min_col];
					if (rel < min_rel) {
						min_rel = rel;
						min_row = i;
					}
				}
				rel.print();
				cout << " ";

			}
			cout << "\n\nМинимальное симплекс-отношение = ";
			min_rel.print();
			cout << " в строке " << min_row + 1 << endl;
			//basis_vars.print();
			basis_vars.set(min_row, min_col);
			simplexMakeIdentity();
			rows++;
			fixZRow();
			print();
			printSolution();
			break;
		}
	}
}

void SimplexMethod::printSolution()
{
	vector<Fraction> result(cols - 1, Fraction(0));
	for (int i = 0; i < rows - 1; i++) {
		result[basis_vars[i]] = matrix[i][cols - 1];
	}
	cout << "\nZmax = Z(";
	for (int i = 0; i < result.size() - 1; i++) {
		result[i].print();
		cout << "; ";
	}
	result[result.size() - 1].print();
	cout << ") = ";
	matrix[z_row][cols - 1].print();
	cout << endl;
}
