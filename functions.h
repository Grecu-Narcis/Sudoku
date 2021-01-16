#pragma once
#include <Windows.h>
#include <cmath>

void changeColor(int k) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

int generateRandomNumber(int lowerBound, int upperBound) {
	//rand()%(upperBound-lowerBound+1) + lowerBound => lowerBound...upperBound

	return (rand() % (upperBound - lowerBound + 1) + lowerBound);
}