#include "bingo.h"

// Private Function Prototypes
static int markCard(bingoCard_t*, int);

// Public Functions
int clearCard(bingoCard_t* pCard) {
    for(int i=0; i<ROWS*COLS; i++) {
        pCard->values[i] = 0;
        pCard->marks[i] = MARK_FALSE;
    }
    return 0;
}

int markCards(bingoCard_t* pCards, int numCards, int pull) {
    for (int i=0; i<numCards; i++) {
        markCard(pCards+i, pull);
    }
    return 0;
}

int evalCards(bingoCard_t* pCards, int numCards) {
    int winner = -1;
    for(int i=0; i<numCards; i++) {
        if(evalCard(pCards+i)) {
            winner = i;
            break;
        }
    }
    return winner;
}

int evalCardsCount(bingoCard_t* pCards, int numCards) {
    int winnerCount = 0;
    for(int i=0; i<numCards; i++) {
        if(evalCard(pCards+i)) {
            winnerCount += 1;
        }
    }
    return winnerCount;
}

int scoreCard(bingoCard_t* pCard, int pull) {
    // Sum all unmarked numbers and multiply by the last pull
    int sum = 0;
    for(int i = 0; i<(ROWS*COLS); i++) {
        if (pCard->marks[i] == MARK_FALSE) {
            sum += pCard->values[i];
        }
    }
    sum *= pull;
    return sum;
}

int evalCard(bingoCard_t* pCard) {
    int winner = 0;
    // First check rows
    for(int i=0; i<ROWS; i++) {
        int row_check = 1;
        for(int j=0; j<COLS; j++) {
            row_check = row_check && (pCard->marks[(i*COLS)+j] == MARK_TRUE);
        }
        if(row_check) {
            winner = 1;
            break;
        }
    }
    // Next check columns
    for(int i=0; i<COLS; i++) {
        int col_check = 1;
        for(int j=0; j<COLS; j++) {
            col_check = col_check && (pCard->marks[(j*COLS)+i] == MARK_TRUE);
        }
        if(col_check) {
            winner = 1;
            break;
        }
    }
    return winner;
}

// Private Functions
static int markCard(bingoCard_t* pCard, int pull) {
    for(int i=0; i<(ROWS*COLS); i++) {
        if(pCard->values[i] == pull) {
            pCard->marks[i] = MARK_TRUE;
        }
    }
    return 0;
}