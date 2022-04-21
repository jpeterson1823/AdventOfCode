#include <stdlib.h>
#include <stdio.h>
#include "../include/cstring.h"
#include "../include/parts.h"

int* get_draws(char* input) {
	int len = 0;
	while (input[len] != '\n')
		len++;
	len++;

	char* draws_str = malloc(sizeof(char) * (len+1));
	for (int i = 0; i < len; i++)
		draws_str[i] = input[i];
	draws_str[len] = '\0';

	// convert to int* for easy of use and sanity preservation
	int* draws = malloc(sizeof(int));
	int di = 0;
	int m = 0;
	int n = 0;
	for (int i = 0; i < len; i++) {
		if (draws_str[i] != ',' && draws_str[i] != '\n')
			n++;
		else {
			cstring* N = cString.create((char*)&draws_str[m], n);
			draws[di++] = cString.toi(N);
			cString.destroy(N);
			draws = realloc(draws, sizeof(int) * (di+1));
			m = i+1; 	// increment i to skip comma
			n = 0;
		}
	}
	// terminate end of draws with negative number since there are
	// no negative numbers in bingo.
	draws[di] = -1;

	// free draws_str
	free(draws_str);

	return draws;
}

int** get_board(char* input, int num) {
	int row_len = 15; 	// 5 2-char numbers, 4 spaces, and one return char: 5*2 + 4 + 1 = 15
	int step = 3;

	// skip first and second line of input file, as well as other boards according to "num" param
	char* boards = &input[MAIN_LINE_OFFSET + (row_len*BOARD_H + 1)*num];
	//char* boards = &input[TEST_LINE_OFFSET + (row_len*BOARD_H + 1)*num];

	int** board = malloc(sizeof(int*) * 5);
	int bi = 0;
	for (int row = 0; row < BOARD_H; row++) {
		int* r = malloc(sizeof(int) * BOARD_W);
		int ri = 0;
		for (int i = 0; i < row_len; i+=step) {
			// get number in row as cstring
			cstring* temp = cString.create(&boards[(row_len*row + i)], step-1);
			// remove extra spaces
			cstring* num = cString.strip(temp);
			cString.destroy(temp);
			// convert to int and store in r
			r[ri++] = cString.toi(num);
			cString.destroy(num);
		}
		board[bi++] = r;
	}

	return board;
}

void free_board(Board* board) {
	// free each row array
	for (int i = 0; i < 5; i++)
		free(board->array[i]);
	// free the array itself
	free(board->array);
	// free marked num array if it was used
	if (board->marked != NULL)
		free(board->marked);
	// free board pointer
	free(board);
}

unsigned int num_inside(int* arr, int len, int num) {
	for (int i = 0; i < len; i++)
		if (arr[i] == num)
			return 1;
	return 0;
}

void mark_num(Board* board, int num) {
	for (int row = 0; row < BOARD_W; row++) {
		if (num_inside(board->array[row], BOARD_H, num)) {
			board->marked = realloc(board->marked, sizeof(int) * (board->num_marked + 1));
			board->marked[board->num_marked++] = num;
			return;
		}
	}
}

unsigned int check_win(Board* board) {
	// if board's number of marked numbers is less than 5, then it is impossible to win
	if (board->num_marked < 5)
		return 0;

	// iterate through each row
	for (int row = 0; row < BOARD_H; row++) {
		// create marked number counter
		int marks = 0;
		// iterate through each number in row
		for (int col = 0; col < BOARD_W; col++)
			// if known marked number is within row, add to marked number counter
			if (num_inside(board->marked, board->num_marked, board->array[row][col]))
				marks++;
		// if marks == 5, that means all 5 numbers in the row are marked, a.k.a bingo!
		if (marks == 5)
			return 1;
	}

	// iterate through each col
	for (int col = 0; col < BOARD_W; col++) {
		// create marked number counter
		int marks = 0;
		// iterate through all numbers within the current column
		for (int row = 0; row < BOARD_H; row++) {
			// if current number is inside marked number list, increment marked counter
			if (num_inside(board->marked, board->num_marked, board->array[row][col]))
				marks++;
		}
		// if marks == 5, that means all 5 numbers in the column are marked, a.k.a bingo!
		if (marks == 5)
			return 1;
	}

	// otherwise, board has not yet won
	return 0;
}

void play(Board* board, int* draws) {
	// run through the first 4 draws since a bingo is impossible before the 5th draw.
	for (int i = 0; i < 4; i++)
		mark_num(board, draws[i]);

	// run through all remaining draws and... well, play bingo.
	int draw = 4;

	// loop until end of drawn numbers list
	while (draws[draw] != -1) {
		mark_num(board, draws[draw]);			// Mark the current number
		if (check_win(board)) {					// check if board has won
			board->winning_draw = draws[draw]; 	// if so, save the winning draw
			board->draws = draw+1;				// also save the number of draws taken to win
			return;								// return to force exit of function
		}
		else // draw the next number if board has not won
			draw++;
	}

	// if zero matches, set draws to int's max
	board->draws = 0x7FFFFFFF;
}




void part1(char* input) {
	// get rolls from first line of file
	int* draws = get_draws(input);

	// create list of boards
	Board** boards = malloc(sizeof(Board*) * NUM_BOARDS);
	
	// loop through all boards and play
	for (int i = 0; i < NUM_BOARDS; i++) {
		// create board and set it's array
		Board* b = malloc(sizeof(Board));
		b->array = get_board(input, i);
		b->marked = malloc(sizeof(int));
		b->draws = 0;
		b->num_marked = 0;

		// play the board
		play(b, draws);

		// save board to boards
		boards[i] = b;
	}

	// find index of the board with the lowest number of draws taken to win
	int max_index = 0;
	for (int i = 1; i < NUM_BOARDS; i++)
		if (boards[i]->draws < boards[max_index]->draws)
			max_index = i;
	
	// get the board
	Board* b = boards[max_index];
	printf("Winning Board:\n\t");
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++)
			printf("%i ", b->array[i][j]);
		printf("\n\t");
	}
	printf("Marked: ");
	for (int i = 0; i < b->num_marked; i++)
		printf("%i ", b->marked[i]);
	printf("\n");

	// calculate the sum of all unmarked numbers in the board
	unsigned int unmarked_sum = 0;
	// iterate through each row
	for (int row = 0; row < BOARD_H; row++) {
		// iterate through each number in the current row
		for (int col = 0; col < BOARD_W; col++) {
			// if the current number isn't marked, add it's value to unmarked sum
			if (num_inside(b->marked, b->num_marked, b->array[row][col]) == 0)
				unmarked_sum += b->array[row][col];
		}
	}
	printf("Unmarked Sum: %i\n", unmarked_sum);
	
	// calculate the answer by multiplying the unmarked sum by the winning drawn number
	unsigned long answer = unmarked_sum * b->winning_draw;
	// print the answer to the console
	printf("Answer: %lu\n", answer);

	
	// free alloc'd memory
	free(draws);
	for (int i = 0; i < NUM_BOARDS; i++)
		free_board(boards[i]);
	free(boards);
}

void part2(char* input) {
	// get rolls from first line of file
	int* draws = get_draws(input);

	// create list of boards
	Board** boards = malloc(sizeof(Board*) * NUM_BOARDS);
	
	// loop through all boards and play
	for (int i = 0; i < NUM_BOARDS; i++) {
		// create board and set it's array
		Board* b = malloc(sizeof(Board));
		b->array = get_board(input, i);
		b->marked = malloc(sizeof(int));
		b->draws = 0;
		b->num_marked = 0;

		// play the board
		play(b, draws);

		// save board to boards
		boards[i] = b;
	}

	// find index of the board with the highest number of draws taken to win
	int max_index = 0;
	for (int i = 1; i < NUM_BOARDS; i++)
		if (boards[i]->draws > boards[max_index]->draws)
			max_index = i;
	
	// get the board
	Board* b = boards[max_index];
	printf("Worst Board:\n\t");
	for (int i = 0; i < BOARD_H; i++) {
		for (int j = 0; j < BOARD_W; j++)
			printf("%i ", b->array[i][j]);
		printf("\n\t");
	}
	printf("Marked: ");
	for (int i = 0; i < b->num_marked; i++)
		printf("%i ", b->marked[i]);
	printf("\n");

	// calculate the sum of all unmarked numbers in the board
	unsigned int unmarked_sum = 0;
	// iterate through each row
	for (int row = 0; row < BOARD_H; row++) {
		// iterate through each number in the current row
		for (int col = 0; col < BOARD_W; col++) {
			// if the current number isn't marked, add it's value to unmarked sum
			if (num_inside(b->marked, b->num_marked, b->array[row][col]) == 0)
				unmarked_sum += b->array[row][col];
		}
	}
	printf("Unmarked Sum: %i\n", unmarked_sum);
	
	// calculate the answer by multiplying the unmarked sum by the winning drawn number
	unsigned long answer = unmarked_sum * b->winning_draw;
	// print the answer to the console
	printf("Answer: %lu\n", answer);

	
	// free alloc'd memory
	free(draws);
	for (int i = 0; i < NUM_BOARDS; i++)
		free_board(boards[i]);
	free(boards);
}
