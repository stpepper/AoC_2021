// 
// Advent of Code 2021
// Day 3
//
// Author: S. Tyler Pepper
// Date: 3 Dec 2021
//
// Description: This program takes an input "diagnostic report" which 
//  is a list of of numbers in binary format and derives two metrics
//  from that which are the "gamma rate" and "epsilon rate" per the 
//  setup prompt of day 3. Ultimately the "power" is computed from 
//  these, which is the final output.
//
// Implementation: Using C Standard Library functions, implement a
//  simple loop to parse the input file line by line, accumulating
//  the necessary metrics as we proceed.
//
// Assumptions: Line count is assumed to be less than 2^32 and length
//  of each binary number is assumed to be less than 32 binary digits
//
// Status: Implementation is complete. Compiles without warnings and 
//  produces correct output.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input"
#define BUF_SIZE 34

int main() {
	int gammaRate = 0, epsilonRate = 0;
	int accum[BUF_SIZE];	
	char sInst[BUF_SIZE];
	FILE* pFile = fopen(INPUT_FILE, "r");
	int i = 0, j = 0;

	while(fgets(sInst, sizeof sInst, pFile) != NULL) {
		j = 0;
		while(sInst[j] == '0' || sInst[j] == '1') {
			if(sInst[j] == '1')
				accum[j]++;
			j++;
		}
		i++;
	}
	// Compute gamma by bitwise selection of  MAX[zeros,ones] and 
	// likewise epsilon with MIN[zeros,ones]
	// Calculating decimal equivalent value iteratively.
	j = 0;
	while(accum[j] != 0) {
		gammaRate *= 2;
		epsilonRate *= 2;
		if(accum[j] > (i-accum[j]))
			gammaRate += 1;
		else
			epsilonRate += 1;
		j++;
	}
	printf("gamma = %i; epsilon = %i \n", gammaRate, epsilonRate);
	printf("Power Consumption: %i \n", (gammaRate * epsilonRate));
	fclose(pFile);
	return 0;
}

