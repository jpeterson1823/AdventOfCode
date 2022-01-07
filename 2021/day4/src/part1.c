#include <stdlib.h>
#include <stdio.h>
#include "../include/cstring.h"
#include "../include/part1.h"
#include "../include/cstring.h"

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
	int num_rows = 5;
	int num_cols = 5;
	int npr = 5; 		// numbers per row
	int step = 3;

	// skip first and second line of input file, as well as other boards according to "num" param
	char* boards = &input[291 + (row_len*num_rows + 1)*num];

	int** board = malloc(sizeof(int*) * 5);
	int bi = 0;
	for (int row = 0; row < num_rows; row++) {
		int* r = malloc(sizeof(int) * npr);
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

void free_board(int** board) {
	for (int i = 0; i < 5; i++)
		free(board[i]);
	free(board);
}

unsigned long hash(int i) {
	return i<<1 / 2;
}

int check_win(int** board, int* draws) {
	printf("Current Board:\n");
	for (int r = 0; r < 5; r++) {
		printf("\t");
		for (int c = 0; c < 5; c++)
			printf("%i ", board[r][c]);
		printf("\n");
	}

	int step = 5;
	for (int draw = 0; draw < 95; draw+=step) {
		// calculate hash
		unsigned long draw_hash = 0;
		for (int i = draw; i < draw+step; i++)
			draw_hash = hash(draws[i]);

		// check each row to see if it's hash matches
		for (int row = 0; row < 5; row++) {
			unsigned long row_hash = 0;
			for (int col = 0; col < 5; col++)
				row_hash += hash(board[row][col]);
			if (row_hash == draw_hash)
				return draw+step;
		}

		for (int col = 0; col < 5; col++) {
			unsigned long col_hash = 0;
			for (int row = 0; row < 5; row++)
				col_hash = hash(board[col][row]);
			if (col_hash == draw_hash)
				return draw+step;
		}

	}

	return -1;
}

int calc_unmarked_sum(int** board, int winning_draw) {
	// TODO
	return NULL;
}

void part1(char* input) {
	// get rolls from first line of file
	int* draws = get_draws(input);


	int best_board = -1;
	int min_moves = 10000;
	int** board;
	for (int i = 0; i < 100; i++) {
		board = get_board(input, i);
		int win = check_win(board, draws);
		free_board(board);

		if (win >= 0) {
			printf("Board %i is a winner, taking %i draws to win.\n", i, win);
			if (win < min_moves) {
				best_board = i;
				min_moves = win;
			}
		}
	}

	printf("Best Board: %i\n", best_board);
	board = get_board(input, best_board);

	free(draws);
}
