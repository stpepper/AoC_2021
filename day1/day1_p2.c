// 
// Advent of Code 2021
// Day 1 Part 2
//
// Author: S. Tyler Pepper
// Date: 1 Dec 2021
//
// Description: This program takes an input file of one measurement
//  per line and computes the number of measurements which increase
//  over the previous measurement.
//  Part 2 varies in that it uses a 3-sample sliding window for 
//  comparison.
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
	int count = 0, lastSweepSum = 0, thisSweepSum = 0;
	int s1 = 0, s2 = 0, s3 = 0;
	char sSweep[BUF_SIZE];
	
	FILE* pFile = fopen(INPUT_FILE, "r");

	while(fgets(sSweep, sizeof sSweep, pFile) != NULL) {
		s3 = s2;
		s2 = s1;
		sscanf(sSweep, "%i", &s1);
		
		lastSweepSum = thisSweepSum;
		thisSweepSum = s1 + s2 + s3;
		if(thisSweepSum > lastSweepSum)
			count++;
	}
	count-=2; // There are 2  extraneous counts from the first instances
	printf("final count: %i \n", count);
	fclose(pFile);
	return 0;
}

