// 
// Advent of Code 2021
// Day 4
//
// Author: S. Tyler Pepper
// Date: 4 Dec 2021
//
// Description: This program reads Bingo input file beginning with one 
//  line of the called numbers in order, followed by some number of game
//  cards. The program then sequentially "calls" the numbers and evaluates
//  each card in search of the LAST winning card.
//
// Implementation: Using C Standard Library functions, implement a modular
//  solution which can perform the basic functions of the game Bingo.
//
// Assumptions: Specifics derived from the input file have been hard coded
//  in this implementation.
//
// Status: Implementation is complete. Compiles without warnings and 
//  produces correct output.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bingo.h"

// Local Static Definitions
#define INPUT_FILE "./input"
#define BUF_LEN 400
#define PULLS 100 
#define CARDS 100

// Local Functions
void loadPulls(FILE*, int*, int);
void loadCards(FILE*, bingoCard_t*, int);
void loadCard(FILE*, bingoCard_t*);

int main() {
	int pulls[PULLS];
	bingoCard_t cards[CARDS], *pCards;
	pCards = &cards[0];
	
	for(int i = 0; i<CARDS; i++){
		clearCard(pCards+i);
	}

	FILE* pFile = fopen(INPUT_FILE, "r");

	// Load all boards into memory
	loadPulls(pFile, pulls, PULLS);
	loadCards(pFile, pCards, CARDS);	
	fclose(pFile);

	// Proceed through all pulls
	for(int i = 0; i<PULLS; i++) {
		int pull = pulls[i];
		// Mark the cards
		markCards(pCards, CARDS, pull);
		// Evaluate cards
		int winner = 0;
		if((winner = evalCardsCount(pCards, CARDS)) == CARDS-1) {
			// Last Winner found
            for(int j=0; j<CARDS; j++) {
                if(!evalCard(pCards+j)) {
                    winner = j;
                }
            }
            
            while (!evalCard(pCards + winner)) {
                int k = 1;
                pull = pulls[i+k];
                markCards(pCards, CARDS, pull);
                k++;
            } 
			int score = scoreCard(pCards + winner, pull);
			printf("The winner is %i, with a score of %i\n", winner, score);
			break;
		}
	}
	return 0;
}

void loadPulls(FILE* pFile, int* pPulls, int pullsLen) {
	char buffer[BUF_LEN];
	fgets(buffer, BUF_LEN, pFile);
	char* token = strtok(buffer, ",");
	while(token) {
		*pPulls = atoi(token);
		pPulls++;
		token = strtok(NULL, ",");
	}
	fgetc(pFile); // Get extra line break
}


void loadCards(FILE* pFile, bingoCard_t* pCards, int cardsLen) {
	for(int i=0; i<cardsLen; i++) {
		loadCard(pFile, pCards+i);
	}
}

void loadCard(FILE* pFile, bingoCard_t* pCard) {
	int buffer[ROWS*COLS];
	for (int row=0; row<ROWS; row++) {
		int i = row*COLS;
		fscanf(pFile, "%i%i%i%i%i", &buffer[i+0], &buffer[i+1], &buffer[i+2], &buffer[i+3], &buffer[i+4]);
	}
	for(int i=0; i< ROWS*COLS; i++) {
		pCard->values[i] = buffer[i];
	}
	fgetc(pFile); // Get extra line break
}
