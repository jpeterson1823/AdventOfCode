#include <stdlib.h>
#include <stdio.h>
#include "../include/part1.h"
#include "../include/part2.h"


// PROTOTYPES
void buf_check(void* buffer);
char* get_input(size_t init_size);


int main() {
	// get puzzle input from file
	char* str = get_input(100);

	part1(str);

	// free allocated memory
	free(str);
	return 0;
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

	// close file pointer
	fclose(fp);

	// remove excess allocated memory and return string
	return realloc(str, sizeof(*str)*len);
}
