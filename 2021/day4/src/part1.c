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
	printf("%s\n", draws_str);

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

void part1(char* input) {
	// get rolls from first line of file
	int* draws = get_draws(input);

	free(draws);
}
