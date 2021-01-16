#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <unordered_set>

using namespace std; 

class Sudoku {
private:
	int table[9][9];
	vector <pair<pair<int, int>, int>> picks;
	bool foundSolution = 0;
	int solutionsNumber = 0;
	int difficultyLevel = 1;
	unordered_set <int> values;

public:
	vector <vector<pair<pair<int, int>, int>>> solutions;

	Sudoku();
	void menu();
	int numberOfEmptyCells();
	bool readTable(const char filename[]);
	void printTable(const vector<pair<pair<int, int>, int>> picks = vector<pair<pair<int, int>, int>>());
	bool isOnLine(int value, int lineIndex, int columnIndex);
	bool isOnColumn(int value, int lineIndex, int columnIndex);
	bool isOnSquare(int value, int lineIndex, int columnIndex);
	bool isValidPlace(int value, int line, int column);
	pair<int, int> findEmptyCell(pair <int, int> position);
	void solve(pair <int, int> index, int stopIndex = 2);
	void fillTable(vector<pair<pair<int, int>, int>> picks);
	void generateRandomTable();
	void printSolutions();
	
};