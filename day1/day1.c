// 
// Advent of Code 2021
// Day 1
//
// Author: S. Tyler Pepper
// Date: 1 Dec 2021
//
// Description: This program takes an input file of one measurement
//  per line and computes the number of measurements which increase
//  over the previous measurement.
//
// Implementation: Using C Standard Library functions, implement a
//  simple loop to parse the input file line by line, converting to
//  integers to perform the simple comparison.
//
// Status: Implementation compiles with no warnings and generates
//  valid output.
//
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "./input"
#define BUF_SIZE 8

int main() {
	int count = 0, lastSweep = 0, thisSweep = 0;
	char sSweep[BUF_SIZE];
	
	FILE* pFile = fopen(INPUT_FILE, "r");

	while(fgets(sSweep, sizeof sSweep, pFile) != NULL) {
		lastSweep = thisSweep;
		sscanf(sSweep, "%i", &thisSweep);
		if(thisSweep >= lastSweep)
			count++;
	}
	count--; // There is one extraneous count from the first instance
	printf("final count: %i \n", count);
	fclose(pFile);
	return 0;
}

