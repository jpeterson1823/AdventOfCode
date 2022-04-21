#include <stdio.h>
#include <stdlib.h>
#include "../include/cstring.h"

cstring* __cstr_create(char* str, int len) {
	// alloc mem for cstr struct and it's char array
	cstring* cstr = malloc(sizeof(cstring));
	char* arr = malloc(sizeof(char)*(len + 1));

	// set length
	cstr->len = len;

	// deepcopy str to arr
	for (int i = 0; i < len; i++)
		arr[i] = str[i];
	// add null-terminator
	arr[len] = '\0';

	// set cstr.arr to str
	cstr->arr = arr;

	return cstr;
}

void __cstr_destroy(cstring* cstr) {
	free((char*)cstr->arr);
	free(cstr);
	cstr = NULL;
}

cstring* __cstr_copy(cstring* cstr) {
	return __cstr_create((char*)cstr->arr, cstr->len);
}

cstring* __cstr_join(cstring* cstr1, cstring* cstr2) {
	cstring* joined = malloc(sizeof(cstring));
	joined->len = cstr1->len + cstr2->len;

	int j = 0;
	char* arr = malloc(sizeof(char) * (cstr1->len + cstr2->len + 1));
	for (int i = 0; i < cstr1->len; i++)
		arr[j++] = cstr1->arr[i];
	for (int i = 0; i < cstr2->len; i++)
		arr[j++] = cstr2->arr[i];
	arr[j] = '\0';

	joined->arr = arr;

	return joined;
}

cstring* __cstr_delimited_join(cstring* cstr1, cstring* cstr2, char delimiter) {
	cstring* joined = malloc(sizeof(cstring));
	joined->len = cstr1->len + cstr2->len + 1;
	
	int j = 0;
	char* arr = malloc(sizeof(char) * (cstr1->len + cstr2->len + 2));
	for (int i = 0; i < cstr1->len; i++)
		arr[j++] = cstr1->arr[i];
	arr[j++] = delimiter;
	for (int i = 0; i < cstr2->len; i++)
		arr[j++] = cstr2->arr[i];
	arr[j] = '\0';

	joined->arr = arr;

	return joined;
}

void __cstr_print(cstring* str) {
	printf("String: %s\tlen=%i\n", str->arr, str->len);
}

void __cstr_named_print(cstring* str, char* name) {
	printf("%s: %s\tlen=%i\n", name, str->arr, str->len);
}

cstring* __cstr_substr(cstring* cstr, int start, int end) {
	if (start >= 0 && end <= cstr->len)
		return cString.create((char*)&cstr->arr[start], end - start);
	else
		return NULL;
}

cstring* __cstr_strip(cstring* cstr) {
	int start = -1;
	int end = -1;
	for (int i = 0; i < cstr->len; i++) {
		char ch = cstr->arr[i];
		if (start == -1 && (ch != ' ' && ch != '\n'))
			start = i;
		if (start != -1 && end == -1 && (ch == ' ' || ch == '\n'))
			end = i;
	}
	if (end == -1)
		end = cstr->len;

	return cString.substr(cstr, start, end);
}

int __cstr_toi(cstring* cstr) {
	int n = 0;
	for (int i = 0; i < cstr->len; i++) {
		n += (cstr->arr[i] - '0');
		if (i < cstr->len - 1)
			n*=10;
	}
	return n;
}


cstring_interface cString = {
	.create = __cstr_create,
	.destroy = __cstr_destroy,
	.copy = __cstr_copy,
	.join = __cstr_join,
	.print = __cstr_print,
	.namedPrint = __cstr_named_print,
	.delimitedJoin = __cstr_delimited_join,
	.substr = __cstr_substr,
	.toi = __cstr_toi,
	.strip = __cstr_strip
};
