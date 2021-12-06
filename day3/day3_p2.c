// 
// Advent of Code 2021
// Day 3 Part 2
//
// Author: S. Tyler Pepper
// Date: 3 Dec 2021
//
// Description: This program takes an input "diagnostic report" which 
//  is a list of of numbers in binary format and derives two metrics
//  from that which are the "O2 generator rate" and "CO2 scrubber rate"
//  per the setup prompt of day 3. Ultimately the "life support rate" 
//  is computed from these, which is the final output.
//
// Implementation: Using C Standard Library functions, implement a
//  multi-pass solution. Intentionally, I have not implemented the 
//  solution using sorting and data structures such as linked lists.
//  This solution maintains a parallel "exclusion array" which marks
//  entries as Included/Excluded for use in further rounds of cal-
//  culation.
//
// Assumptions: Line count is assumed to be less than 2^32 and length
//  of each binary number is assumed to be less than 32 binary digits.
//
// Status: Implementation is complete. Compiles without warnings and 
//  produces correct output.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "./input"
#define BUF_SIZE 32
#define LINE_COUNT 1000
#define INC '0'
#define EXC '1'

void initExcArray(char* excArray, int count);
void strikeExcArray(char** sArray, char* excArray, int len, int pos, char v);
void loadStringArrayFromFile(FILE* pFile, char** sArray, int len);
int findBitMetric(char* excArray, int len);
int countIncLines(char* excArray, int len);
int sbintoi(char* str);

int main() {
	char array[LINE_COUNT * BUF_SIZE];
	char* sArray[LINE_COUNT];
	sArray[0] = &array[0];
	for(int i=1; i<LINE_COUNT; i++) {
		sArray[i] = sArray[i-1] + BUF_SIZE;
	}

	char o2Array[LINE_COUNT];
	char co2Array[LINE_COUNT];
	initExcArray(o2Array, LINE_COUNT);
	initExcArray(co2Array, LINE_COUNT);

	FILE* pFile = fopen(INPUT_FILE, "r");
	loadStringArrayFromFile(pFile, sArray, LINE_COUNT);

	// While it may not be optimal, determination of the rates by
	// subsequent passes provides for a straightforward im-
	// plementation.
	int o2Rate, co2Rate; 
	int i = 0, j = 0;

	// Examine j bit of each i line, and trim list until one remains
	while(countIncLines(o2Array, LINE_COUNT) > 1) {
		// Determine maj bit in each (j) position
		int o2_1Count = 0, o2_0Count = 0;
		char val;
		i = 0;
		while(i<LINE_COUNT) {
			if(o2Array[i] == INC) {
				if(sArray[i][j] == '1')
					o2_1Count++;
				if(sArray[i][j] == '0')
					o2_0Count++;
			}
			i++;
		}
		// Strike off minority value, ties go to the 1s
		if (o2_1Count >= o2_0Count)
			val = '0'; // Strike off all 0s
		else
			val = '1';
		strikeExcArray(sArray, o2Array, LINE_COUNT, j, val);
		j++;
	}
	i = findBitMetric(o2Array, LINE_COUNT);
	o2Rate = sbintoi(sArray[i]);	
	
	i = 0;
	j = 0;
	while((countIncLines(co2Array, LINE_COUNT) > 1) && j < 12 ) {
		// Determine min bit in each (j) position
		int co2_1Count = 0, co2_0Count = 0;
		char val;
		i = 0;
		while(i<LINE_COUNT) {
			if(co2Array[i] == INC) {
				if(sArray[i][j] == '1')
					co2_1Count++;
				if(sArray[i][j] == '0')
					co2_0Count++;
			}
			i++;
		}
		// Strike the majority value, ties go to the 0s
		if (co2_1Count >= co2_0Count)
			val = '1';
		else
			val = '0';
		strikeExcArray(sArray, co2Array, LINE_COUNT, j, val);
		j++;
	}
	i = findBitMetric(co2Array, LINE_COUNT);
	co2Rate = sbintoi(sArray[i]);

	printf("o2 rate = %i co2 rate = %i \n", o2Rate, co2Rate);
	printf("Life Support: %i \n", (o2Rate * co2Rate));
	fclose(pFile);
	return 0;
}

void initExcArray(char* excArray, int len) {
	for (int i = 0; i < len; i++) {
		excArray[i] = INC;
	}
}

void strikeExcArray(char* sArray[], char* excArray, int len, int pos, char v) {
	for (int i = 0; i < len; i++) {
		if (excArray[i] == INC) {
			if (sArray[i][pos] == v )
				excArray[i] = EXC;
		}			
	}
}

void loadStringArrayFromFile(FILE* pFile, char* sArray[], int len) {
	int i = 0;
	while(fgets(sArray[i], BUF_SIZE, pFile) != NULL) {
		for(int j=0; j< BUF_SIZE; j++) {
			if ( (sArray[i][j] == '\n') || (j >= BUF_SIZE-1))
				sArray[i][j] = '\0';
		}
		i++;
	}
}

int findBitMetric(char* excArray, int len) {
	int i = 0;
	while ((excArray[i] == EXC) && (i < len)){
		i++;
	}
	if (i >= len) 
		return -1;
	else
		return i;
}

int countIncLines(char* excArray, int len) {
	int i = 0;
	int count = 0;
	while (i < len) {
		if(excArray[i] == INC)
			count++;
		i++;
	}
	return count;
}

int sbintoi(char* str) {
	int i = 0;
	int num = 0;
	while ((str[i] != '\0') && i < BUF_SIZE ) {
		num *= 2;
		if (str[i] == '1')
			num += 1;
		i++;
	}
	return num;
}
