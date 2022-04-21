#ifndef __PART1_H__
#define __PART1_H__

char* str_strip(char* str);
void free_str_array(char** strarray);
char* str_dynamic_append(char* str, char c);
char** str_split(char* str, char delim);

void part1(char* input);

#endif
