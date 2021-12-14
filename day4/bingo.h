
// Extern defines, constants, enums
#define ROWS 5
#define COLS 5
#define MIN 0
#define MAX 99
#define MARK_FALSE ' '
#define MARK_TRUE 'X'

// Public Types
typedef struct bingoCard {
	int won;
	int values[ROWS * COLS];
	char marks[ROWS * COLS];
} bingoCard_t;

// Extern Methods
int clearCard(bingoCard_t*);
int markCards(bingoCard_t*, int, int);
int evalCards(bingoCard_t*, int);
int evalCardsCount(bingoCard_t*, int);
int scoreCard(bingoCard_t*, int);
int evalCard(bingoCard_t*);
