// 
// Advent of Code 2021
// Day 1
//
// Author: S. Tyler Pepper
// Date: 1 Dec 2021
// Description: This program takes an input file of one measurement
//  per line and computes the number of measurements which increase
//  over the previous measurement.

#include <stdio.h>

#define INPUT_FILE "./input"

int main() {
	FILE* pFile = fopen(INPUT_FILE, "r");
	fclose(pFile);
	return 0;
}

