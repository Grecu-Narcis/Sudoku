#include "Sudoku.h"
#include "functions.h"

Sudoku::Sudoku() {
	srand(time(0));

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			table[i][j] = 0;

	for (int i = 1; i <= 9; i++)
		values.insert(i);
}

void Sudoku::menu() {
	cout << "Welcome to Sudoku 2021!\n\n";
	cout << "Press 1 to generate a Sudoku board.\n";
	cout << "Press 2 to get the solution for a Sudoku board.\n";

	char option;
	option = _getch();
	if (option == '1') {
		system("cls");
		cout << "Welcome to Sudoku 2021!\n\n";
		/*cout << "Select difficulty:\n";
		cout << "Press 1 for easy.\nPress 2 for medium.\nPress 3 for hard.\n";

		option = _getch();
		if (option >= '1' && option <= '3')
			difficultyLevel = option - '0';

		system("cls");*/
		generateRandomTable();

		fillTable(solutions[0]);

		printTable(solutions[0]);
	}

	else if (option == '2') {
		system("cls");
		cout << "Welcome to Sudoku 2021!\n\n";

		cout << "Enter the path to the text file where is stored the Sudoku board: \n";

		char path[1000];
		cin.get(path, 1000);

		if (readTable(path) == 1) {
			solve(findEmptyCell(make_pair(0, 0)), 1);
			printSolutions();
		}
	}
}

int Sudoku::numberOfEmptyCells() {
	int result = 0, i, j;

	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (table[i][j] == 0)
				++result;

	return result;
}

bool Sudoku::readTable(const char filepath[]) {
	// function to read a sudoku configuration from a specified file path
	ifstream fin(filepath);

	char ch;

	if (fin.good()) {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				fin >> ch;
				table[i][j] = ch - '0';
			}

		return 1;
	}
	else {
		cout << "Couldn't read data from file!";
		system("pause");
		return 0;
	}

	fin.close();
}

void Sudoku::printTable(const vector<pair<pair<int, int>, int>> picks) {
	// function to print the actual configuration
	
	int i, j;
	cout << "   ";
	for (i = 1; i <= 9; i++) {
		cout << i << " ";
		if (i % 3 == 0) cout << " ";
	}

	cout << '\n';

	cout << "  -";
	for (i = 1; i < 20; i++)
		cout << "-";

	cout << '\n';

	for (i = 0; i < 9; i++) {
		cout << i + 1 << "| ";
		for (j = 0; j < 9; j++) {
			int ok = 0;
			for (unsigned a = 0; a < picks.size(); a++)
				if (i == picks[a].first.first && j == picks[a].first.second)
					ok = 1;

			if (ok == 1) {
				changeColor(10); // Green

				cout << table[i][j] << ' ';

				changeColor(7); // White
			}

			else {
				cout << table[i][j] << ' ';
			}

			if ((j + 1) % 3 == 0) cout << ' ';
		}
		cout << '\n';
		if ((i + 1) % 3 == 0) cout << "\n";
	}

	cout << "\n\n";
}

bool Sudoku::isOnLine(int value, int lineIndex, int columnIndex) {
	// check if number is already on the line
	for (int i = 0; i < 9; i++)
		if (table[lineIndex][i] == value && i != columnIndex)
			return 1;

	return 0;
}

bool Sudoku::isOnColumn(int value, int lineIndex, int columnIndex) {
	// check if number is already on the column
	for (int i = 0; i < 9; i++)
		if (table[i][columnIndex] == value && i != lineIndex)
			return 1;

	return 0;
}

bool Sudoku::isOnSquare(int value, int lineIndex, int columnIndex) {
	// check if number is in the "small" square of the table
	// (the 3x3 table which contains the element at line 'lineIndex' and column 'columnIndex'
	int squareI, squareJ;
	squareI = lineIndex / 3 * 3;
	squareJ = columnIndex / 3 * 3;

	for (int i = squareI; i < squareI + 3; i++)
		for (int j = squareJ; j < squareJ + 3; j++)
			if (table[i][j] == value && (i != lineIndex || j != columnIndex))
				return 1;
	return 0;
}

bool Sudoku::isValidPlace(int value, int line, int column) {
	// check if the number placed in the current cell is a valid solution
	if (isOnLine(value, line, column))   return 0;

	if (isOnColumn(value, line, column)) return 0;

	if (isOnSquare(value, line, column)) return 0;

	return 1;
}

pair<int, int> Sudoku::findEmptyCell(pair <int, int> position) {
	int row, column;

	for (row = 0; row < 9; row++)
		for (column = 0; column < 9; column++)
			if (table[row][column] == 0) 
				return make_pair(row, column);
		

	return make_pair(-1, -1);
}

void Sudoku::solve(pair <int, int> indexes, int stopIndex) {
	if (solutionsNumber >= stopIndex) // we have to stop
		return;

	for (auto it = values.begin(); it != values.end(); it++) {
		if (isValidPlace(*it, indexes.first, indexes.second)) { // if k is well placed we go ahead
			table[indexes.first][indexes.second] = *it;
			picks.push_back(make_pair(indexes, *it));

			pair<int, int> nextPosition = findEmptyCell(indexes);

			if (nextPosition == make_pair(-1, -1)) { // is solution
				++solutionsNumber;
				solutions.push_back(picks); // add the solution to the solutions vector
			}
			else { // we fill next empty cell of the board
				solve(nextPosition, stopIndex);
				picks.pop_back();
			}

			table[indexes.first][indexes.second] = 0;
		}
	}
}

void Sudoku::fillTable(vector<pair<pair<int, int>, int>> picks) {
	// this function fill the cell which were empty at the beginning with values from a specific solution of it
	for (unsigned i = 0; i < picks.size(); i++)
		table[picks[i].first.first][picks[i].first.second] = picks[i].second;
} 

void Sudoku::generateRandomTable() {
	int number, row, column;

	int maxTries = 0;

	while (values.size() != 9) {
		number = rand() % 9 + 1;
		values.insert(number);
	}
	solve(findEmptyCell(make_pair(0, 0)), 1);

	fillTable(solutions[0]);

	while (solutionsNumber == 1) {
		row = rand() % 9;
		column = rand() % 9;

		solutions.clear();
		solutionsNumber = 0;

		table[row][column] = 0;

		solve(findEmptyCell(make_pair(0, 0)));
	}
	
}

void Sudoku::printSolutions() {
	if (solutionsNumber == 0)
		cout << "There are no solutions!";

	for (unsigned i = 0; i < solutions.size(); i++) {
		fillTable(solutions[i]);

		cout << "Solution " << i + 1 << ":\n";

		printTable(solutions[i]);
	}
}