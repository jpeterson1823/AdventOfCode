#include "part1.h"
#include "part2.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_SEGS 10


unsigned int str_hash(char* str) {
    unsigned int hash = 0;
    while (*str != '\0') {
        hash += (int)(*str)<<2;
        str++;
    }
    return hash;
}

int determine_number(unsigned int* hashes, char* seven_seg_str) {
    int hash = str_hash(seven_seg_str);
    
    for (int i = 0; i < NUM_SEGS; i++) {
        if (hashes[i] == hash)
            return i;
    }
    return -1;
}


void part2(char* input) {
    unsigned int hashes[NUM_SEGS] = {
        str_hash("cagedb"),
        str_hash("ab"),
        str_hash("gcdfa"),
        str_hash("fbcad"),
        str_hash("eafb"),
        str_hash("cdfbe"),
        str_hash("cdfgeb"),
        str_hash("dab"),
        str_hash("acedgfb"),
        str_hash("cefabd")
    };
    
    // split input by newlines
    char** sinput = str_split(input, '\n');
    char** iptr = sinput;
    
    // loop through all lines of input
    int sum = 0;
    while (*iptr != NULL) {
        // create temp var
        char** temp = str_split(*iptr, '|');
        
        // create output string
        char* ostr = str_strip(temp[1]);
        char** output = str_split(ostr, ' ');
        free(ostr);
        free_str_array(temp);
        
        // loop through all output and add all output values
        char** ptr = output;
        int num = 0;
        while (*ptr != NULL) {
            num *= 10;
            num += determine_number(hashes, *ptr);
            // increment pointer
            ptr++;
        }
        
        // free output data
        free_str_array(output);
        
        // add number to sum
        printf("num: %i\n", num);
        sum += num;
        
        // increment sinput pointer
        iptr++;
    }
    
    printf("Sum: %i\n", sum);
    
    // free sinput
    free_str_array(sinput);
}
