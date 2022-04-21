#ifndef __PART1_H__
#define __PART1_H__

#define BOARD_W 5
#define BOARD_H 5
#define NUM_BOARDS 100

// offsets are calculated by adding 1 to the length of the first line of the input file
#define MAIN_LINE_OFFSET 291
#define TEST_LINE_OFFSET 72

typedef struct BOARD {
	int** array;
	int* marked;
	int draws;
	int winning_draw;
	int num_marked;
} Board;

int* get_draws(char* input);
int** get_board(char* input, int num);
void free_board(Board* board);
void play(Board* board, int* draws);

unsigned int num_inside(int* arr, int len, int num);

void part1(char* input);
void part2(char* input);

#endif
