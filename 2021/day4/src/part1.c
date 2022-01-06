#include "../include/cstring.h"
#include "../include/part1.h"
#include "../include/cstring.h"

int* get_draws(char* input) {
	int len = 0;
	while (input[len] != '\n')
		len++;

	char* draws_str = malloc(sizeof(char) * len);
	for (int i = 0; i < draws_str; i++)
		draws_str[i] = input[i];

	// convert to int* for easy of use and sanity preservation
	int* draws = malloc(sizeof(int));
	int di = 0;
	int m = 0;
	int n = 0;
	for (int i = 0; i < len; i++) {
		if (draws_str[i] != ',')
			n++;
		if (draws_str[i] == ',') {
			if (n == 0)
				m = i;
			else {
				cstring* N = cString.create((char*)&draws_str[m], n);
				draws[di++] = cString.toi(N);
				cString.destroy(N);
				n = 0;
			}
		}
	}
}

void part1(char* input) {
	// get rolls from first line of file
	char* draws = get_draws(input);
}
