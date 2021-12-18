#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// PROTOTYPES
void buf_check(void* buffer);
char* get_input(size_t init_size);
long part1(char* str);
long part2(char* str);


int main() {
	// get puzzle input from file
	char* str = get_input(100);

	printf("Part 1: %ld\n", part2(str));

	// free allocated memory
	free(str);
	return 0;
}


long part1(char* str) {
	// horizontal and vertical position
	long x = 0;
	long y = 0;

	// for each cmd, get it's direction, then the distance traveled.
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		// get direction of movement
		char dir = str[i];

		// move to index of space character
		for (; i < len; i++)
			if (str[i] == ' ') break;

		// get distance traveled
		int dis = atoi(&str[i+1]);

		// update position variables
		switch (dir) {
			case 'f':
				x += dis;
			break;
			
			case 'd':
				y += dis;
			break;

			case 'u':
				y -= dis;
			break;
			
			default:
				printf("Unknown Command Found\n");
				exit(1);
			break;
		}

		// move to new-line character
		for (; i < len; i++)
			if (str[i] == '\n') break;
		
		printf("Direction: %c\n", dir);
		printf("Distance:  %i\n", dis);
		printf("Position: (%ld, %ld)\n\n", x, y);
	}

	// return your horizontal position multiplied times your vertical position
	return x*y;
}


long part2(char* str) {
	// horizontal and vertical position
	long aim = 0;
	long x = 0;
	long y = 0;

	// for each cmd, get it's direction, then the distance traveled.
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		// get direction of movement
		char dir = str[i];

		// move to index of space character
		for (; i < len; i++)
			if (str[i] == ' ') break;

		// get distance traveled
		int dis = atoi(&str[i+1]);

		// update position variables
		switch (dir) {
			case 'f':
				x += dis;
				y += (aim * dis);
			break;
			
			case 'd':
				aim += dis;
			break;

			case 'u':
				aim -= dis;
			break;
			
			default:
				printf("Unknown Command Found\n");
				exit(1);
			break;
		}

		// move to new-line character
		for (; i < len; i++)
			if (str[i] == '\n') break;
		
		printf("Direction: %c\n", dir);
		printf("Distance:  %i\n", dis);
		printf("Position: (%ld, %ld)\n\n", x, y);
	}

	// return your horizontal position multiplied times your vertical position
	return x*y;
}


/**
 * @brief
 * Checks to make sure a buffer's memory was properly allocated. 
 * Exits if memory incorrectly allocated.
 *
 * @param buffer		buffer to be checked
 */
void buf_check(void* buffer) {
	if (buffer == NULL) {
		perror("[ MEM_ERR ] System has no remaining memory to use for buffer. Exiting...\n");
		exit(1);
	}
}


/**
 * @breif
 * Gets the input for AdventOfCode stored in a file named 'input.txt' located in
 * the same directory of this script's execution.
 *
 * @param init_size			initial size of the string buffer
 * @return 					raw text data from file in string format
 */
char* get_input(size_t init_size) {
	// open input file
	FILE* fp;
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		perror("Failed to open 'input.txt'. Is the file in this directory?\n");
		exit(EXIT_FAILURE);
	}

	// create string buffer
	char* str;
	int ch;
	size_t size = 100;
	size_t len = 0;

	// allocate memory for buffer
	str = realloc(NULL, sizeof(*str)*size);
	// check if memory was available for allocation
	buf_check(str);

	// read file contents
	while (EOF != (ch=fgetc(fp))) {
		str[len++] = ch;
		// if out of room in buffer, allocate more memory in increments of 16*type
		if (len == size) {
			// allocate memory for buffer
			str = realloc(str, sizeof(*str)*(size+= 16));
			// check if memory was available for allocation
			buf_check(str);
		}
	}
	// append null-terminator to string
	str[len++] = '\0';

	// remove excess allocated memory and return string
	return realloc(str, sizeof(*str)*len);
}
