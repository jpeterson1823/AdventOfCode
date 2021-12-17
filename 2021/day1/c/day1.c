#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// PROTOTYPES
void buf_check(void* buffer);
char* get_input(size_t init_size);
int part1(char* str);
int part2(char* str);


int main() {
	// get puzzle input from file
	char* str = get_input(100);

	printf("Increases: %i\n", part2(str));
	
	free(str);
	return 0;
}







// As a challenge, I didn't allow myself to use "atoi".
int part1(char* str) {
	// check each depth reading and count how many times the reading increases
	// from the previous reading
	char first_check = 1;
	int count = 0;
	int depth_pos = 0;
	char* prev_depth = (char*)malloc(sizeof(char) * 10);
	buf_check(prev_depth);
	char* curr_depth = (char*)malloc(sizeof(char) * 10);
	buf_check(curr_depth);
	for (int str_pos = 0; str_pos < strlen(str); str_pos++) {
		switch (str[str_pos]) {
			case '\n':
				// add null-terminator and remove excess alloc'd data
				curr_depth[depth_pos++] = '\0';
				curr_depth = realloc(curr_depth, depth_pos);

				// if increased since last reading, increment count if not on first check
				if (atoi(curr_depth) > atoi(prev_depth)) {
					if (first_check)
						first_check = 0;
					else
						count++;
				}
				// reset depth_pos
				depth_pos = 0;

				// Instead of using for loops to deepcopy, mess with the memory allocation... lol.
				// free memory at prev_depth since it is no longer needed
				free(prev_depth);
				// set prev_depth's pointer to the address of the first char of curr_depth
				prev_depth = &curr_depth[0];
				// allocate new memory for curr_depth.
				curr_depth = (char*)malloc(sizeof(char)*10);
				buf_check(curr_depth);
			break;
			default:
				curr_depth[depth_pos++] = str[str_pos];
			break;
		}
	}

	// free allocated memory
	free(prev_depth);
	free(curr_depth);

	// return number of increases
	return count;
}


int part2(char* str) {
	// get number of measurements taken by counting the number of newline chars
	int num_measure = 0;
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == '\n') num_measure++;
	
	// convert str array into int array
	int dptr = 0;
	int vptr = 0;
	int* data = (int*)malloc(sizeof(int) * num_measure);
	char* vstr = malloc(sizeof(*vstr) * 10);
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') {
			// add null-terminator and remove excess allocated memory
			vstr[vptr++] = '\0';
			vstr = realloc(vstr, vptr);
			// convert to string and add to data
			data[dptr++] = atoi(vstr);
			// free memory, reallocate, and reset index pointer
			free(vstr);
			vstr = malloc(sizeof(*vstr) * 10);
			vptr = 0;
		}
		// otherwise, add char to value string
		else vstr[vptr++] = str[i];
	}

	// Using int array, calculate the sum of both windows. Increment count if increase found.
	int count = 0;
	int psum = -1;
	for (int i = 0; i < dptr-2; i++) {
		int nsum = data[i] + data[i+1] + data[i+2];
		if (nsum > psum && psum != -1)
			count++;
		psum = nsum;
	}

	// return number of increases
	return count;
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

	// close file
	fclose(fp);

	// remove excess allocated memory and return string
	return realloc(str, sizeof(*str)*len);
}
