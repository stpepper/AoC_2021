// 
// Advent of Code 2021
// Day 2 Part 2
//
// Author: S. Tyler Pepper
// Date: 2 Dec 2021
//
// Description: This program takes an input file of instructions which
//  are a tuple of direction (up, down, forward) and magnitude (integer)
//  per line and determines the ultimate end point.
//  Part 2 varies in that the interpretation of these directions is now
//  different with a third parameter, aim, controlling the depth
// 
// Implementation: Using C Standard Library functions, implement a
//  simple loop to parse the input file line by line, converting to
//  integers to perform the simple cumulative operation.
//
// Assumptions: Starting position is assumed to be (0,0) and the input
//  file is assumed to contain only valid input.
//
// Status: Implementation is complete. Compiles without warnings and 
//  produces correct output.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input"
#define BUF_SIZE 16

#define FORWARD "forward"
#define UP "up"
#define DOWN "down"

int main() {
	int hozPos = 0;
	int depPos = 0;
	int aimPos = 0;
	char sInst[BUF_SIZE];
	char sDirection[BUF_SIZE];
	int magnitude = 0;
	
	FILE* pFile = fopen(INPUT_FILE, "r");

	while(fgets(sInst, sizeof sInst, pFile) != NULL) {
		sscanf(sInst, "%s %i", sDirection, &magnitude);
		//printf("%i\n", magnitude);
		if (strcmp(sDirection, FORWARD) == 0) {
			hozPos += magnitude;
			depPos += aimPos * magnitude;
		}
		if (strcmp(sDirection, UP) == 0) {
			aimPos -= magnitude;
		}
		if (strcmp(sDirection, DOWN) == 0) {
			aimPos += magnitude;	
		}
		//printf("%i\n", hozPos);
	}
	printf("hoz = %i; dep = %i \n", hozPos, depPos);
	printf("final product: %i \n", (hozPos * depPos));
	fclose(pFile);
	return 0;
}

