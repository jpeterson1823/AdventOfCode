#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/list.h"


// PROTOTYPES
void buf_check(void* buffer);
char* get_input(size_t init_size);
long get_rating(list* l, int bitwidth, char module);
void part1(char* str);
void part2(char* str);


int main() {
	// get puzzle input from file
	char* str = get_input(100);

	//part1(str);
	part2(str);

	// free alloc'd memory
	free(str);
	return 0;
}


void part1(char* str) {
	// in the input, each byte is 12 bits long
	short bitwidth = 12;

	// count number of new lines and log their index
	int lines = 0;
	int* nchs = malloc(sizeof(int));
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '\n') {
			// save index, increment lines, and add extra memory
			nchs[lines++] = i;
			nchs = realloc(nchs, sizeof(int) * (lines + 1));
		}
	}
	// remove extra memory from nchs
	nchs = realloc(nchs, sizeof(int) * lines);

	// loop through binary numbers and calculate gamma and epsilon rate
	char* gamma = malloc(sizeof(char) * (bitwidth + 1));
	gamma[bitwidth] = '\0';
	char* epsilon = malloc(sizeof(char) * (bitwidth + 1));
	epsilon[bitwidth] = '\0';
	int n0 = 0;
	int n1 = 0;
	int bi = 0;

	for (int bit = 0; bit < bitwidth; bit++) {
		// use line-1 here because there is no binary num after the last return char
		for (int line = 0; line < lines-1; line++) {
			char ch;
			if (line == 0) // if on first line, bit is before all return chars
				ch = str[bit];
			else // otherwise, must calculate actual position of char in input str
				ch = str[bit + (nchs[line]+1)];

			// count number of 0's and 1's
			if (ch == '0')
				n0++;
			else
				n1++;
		}
		// set bits of gamma and epsilon
		// gamma set to most common bit, epsilon set to least common bit
		if (n1 > n0) {
			gamma[bi] = '1';
			epsilon[bi] = '0';
		}
		else {
			gamma[bi] = '0';
			epsilon[bi] = '1';
		}
		// increment bit index
		bi++;

		// reset counters
		n0 = 0;
		n1 = 0;
	}

	printf("GAMMA BINARY: \t 0b%s\nEPSILON BINARY: 0b%s\n", gamma, epsilon);


	// convert binary values to decimal
	long gval = 0;
	long eval = 0;
	int bit = 0;
	int n = bitwidth - 1;
	// act in reverse order
	while (n >= 0) {
		if (gamma[n] == '1')
			gval += (1 << bit);
		if (epsilon[n] == '1')
			eval += (1 << bit);
		n--;
		bit++;
	}

	printf("GAMMA DECIMAL: \t %ld\nEPSILON DECIMAL: %ld\n", gval, eval);

	// multiply the two values together to get power consumption of submarine.
	printf("Power Consumption: %ld\n", eval*gval);

	// free allocated memory
	free(epsilon);
	free(gamma);
	free(nchs);
}


void part2 (char* str) {
	// create list of all binary numbers
	int bitwidth = 12;
	list* l = List.create(str, bitwidth);
	for (int i = 1; i < strlen(str)/(bitwidth+1); i++)
		List.append(l, &str[(bitwidth+1)*i], bitwidth);

	// create oxy and co2 lists
	list* oxy = List.copy(l);
	list* co2 = List.copy(l);

	printf("OG OxyList: ");
	List.print(oxy);
	
	long oxyrating = get_rating(l, bitwidth, 'o');
	long co2rating = get_rating(l, bitwidth, 'c');
	printf("Oxy Rating: %ld\n", oxyrating);
	printf("Co2 Rating: %ld\n", co2rating);

	printf("Life Support Rating: %ld\n", oxyrating*co2rating);

	List.destroy(l);
	List.destroy(oxy);
	List.destroy(co2);
}

long get_rating(list* og, int bitwidth, char module) {
	// create new list as not to change original
	list* l = List.copy(og);
	
	for (int bitcolumn = 0; bitcolumn < bitwidth; bitcolumn++) {
		int n0 = 0;
		int n1 = 0;
		for (int num = 0; num < l->len; num++) {
			char bit = List.get(l, num)[bitcolumn];
			if (bit == '0')
				n0++;
			else
				n1++;
		}
		printf("n0: %i \tn1: %i\n", n0, n1);

		// determine num
		char num;
		if (module == 'o') {
			if (n0 > n1)
				num = '0';
			else
				num = '1';
		} else {
			if (n0 > n1)
				num = '1';
			else
				num = '0';
		}

		printf("Num: %c\n", num);
		
		// remove nums in l that dont start with num
		list* newL = NULL;
		for (int i = 0; i < l->len; i++) {
			char* n = List.get(l, i);
			if (n[bitcolumn] == num) {
				if(newL == NULL)
					newL = List.create(n, bitwidth);
				else
					List.append(newL, n, bitwidth);
			}
		}

		printf("List is NULL: %i\n", newL==NULL);

		if (newL != NULL) {
			// destroy oxy list
			List.destroy(l);

			// set oxy to point to newOxy
			l = newL;
		}
	}

	// get the numbers for each rating
	// convert binary values to decimal
	char* str = List.get(l, 0);
	long rating = 0;
	int bit = 0;
	int n = bitwidth - 1;
	// act in reverse order
	while (n >= 0) {
		if (str[n] == '1')
			rating += (1 << bit);
		n--;
		bit++;
	}

	// destroy copied list
	List.destroy(l);

	// return the calculated rating
	return rating;
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
