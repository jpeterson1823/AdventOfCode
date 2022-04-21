#include "../include/part1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// strips leading and trailing white spaces
char* str_strip(char* str) {
    // get position of first non-space char
    unsigned int start = 0;
    while (str[start] == ' ' || str[start] == '\n')
        start++;
    
    // get position of last non-space char
    unsigned int end = strlen(str) - 1;
    while (str[end] == ' ' || str[end] == '\n')
        end--;
    
    // create new string and set all chars to null
    char* nstr = malloc(sizeof(char) * (end - start + 2));
    
    // copy string to new string and add null terminator
    strncpy(nstr, &str[start], end+1);
    nstr[end-start + 1] = '\0';
    
    // return pointer to new string
    return nstr;
}


// free's null-terminated array of strings
void free_str_array(char** strarray) {
    char** array = strarray;
    
    while (*array != NULL) {
        free(*array);
        *array = NULL;
        array++;
    }
    
    free(strarray);
    strarray = NULL;
}


// append a char to the end of a dynamically alloc'd string
char* str_dynamic_append(char* str, char c) {
    // calc len of og string
    unsigned int len = strlen(str);
    
    // realloc memory
    str = realloc(str, sizeof(char) * (len + 2));
    if (str == NULL)
        perror("Failed to realloc memory\n");
    
    // append char to end of string and add null terminator
    str[len] = c;
    str[len+1] = '\0';
    
    // return og pointer
    return str;
}


// split string by delimiter; terminated by nullchar string
char** str_split(char* str, char delim) {
    // calc len of string
    unsigned int len = strlen(str);
    
    // return null if string of length 0
    if (len == 0)
        return NULL;
    
    // create string array and element string
    char** strarray;
    char* element;
    
    // create element counter
    unsigned int nelements = 0;
    
    // allocate memory for a single element in the string array
    strarray = malloc(sizeof(char*));
    
    // set element pointer to NULL to avoid hanging
    element = NULL;
    
    // loop through string
    while(*str != '\0') {
        // add char to element if it's not the delimiter
        if (*str != delim) {
            // initialize element if it isn't already
            if (element == NULL) {
                // allocate memory for empty string and add null terminator
                element = malloc(sizeof(char));
                *element = '\0';
            }
            // dynamically append char to end of element string
            element = str_dynamic_append(element, *str);
        }
        // otherwise, add to strarray
        else {
            // set element to the value at the current position in array
            strarray[nelements++] = element;
            // allocate memory for another string in the array
            strarray = realloc(strarray, sizeof(char*) * (nelements + 1));
            // set element to NULL
            element = NULL;
        }
        // increment str
        str++;
    }
    
    // if element isn't null, then there is another element to add
    if (element != NULL) {
        strarray[nelements++] = element;
        strarray = realloc(strarray, sizeof(char*) * (nelements + 1));
        element = NULL;
    }
    
    // add null terminator to end of string array
    strarray[nelements] = NULL;
    
    // return pointer to string array
    return strarray;
}


// part one of advent of code day 8.
void part1(char* input) {
    // split input by newline
    char** sinput = str_split(input, '\n');
    
    // create counter for occurrences
    int count = 0;
    
    // loop through all input
    char** iptr = sinput;
    while (*iptr != NULL) {
        // create temp var to store split into display and output strings
        char** temp = str_split(*iptr, '|');
        
        // create list of display data from stripped display string
        char* dstr = str_strip(temp[0]);
        char** display = str_split(dstr, ' ');
        free(dstr);
        
        // create list of output data from stripped output string
        char* ostr = str_strip(temp[1]);
        printf("%s", ostr);
        char** output = str_split(ostr, ' ');
        free(ostr);
        
        // free temp array as it's no longer needed
        free_str_array(temp);
        
        // count all occurrences of the display command for numbers 1, 4, 7, and8
        char** ptr = output;
        int len;
        while (*ptr != NULL) {
            len = strlen(*ptr);
            printf("str: %s \t len: %i\n", *ptr, len);
            if (len == 2 || len == 3 || len == 4 || len == 7)
                count++;
            ptr++;
        }
        printf("Occurrences: %i\n", count);
        
        // free display and output data
        free_str_array(display);
        free_str_array(output);
        
        // increment input pointer
        iptr++;
    }
    
    // free sinput
    free_str_array(sinput);
}