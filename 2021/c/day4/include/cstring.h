#ifndef __CSTRING_H__
#define __CSTRING_H__

// Define cstring datatype
typedef struct _CSTRING cstring;

typedef struct _CSTRING_INTERFACE {
	cstring* (*create)(char* str, int len);
	void (*destroy)(cstring* cstr);
	cstring* (*copy)(cstring* __cstr);
	cstring* (*join)(cstring* cstr1, cstring* cstr2);
	cstring* (*delimitedJoin)(cstring* cstr1, cstring* cstr2, char delimiter);
	cstring* (*substr)(cstring* cstr1, int start, int end);
	cstring* (*strip)(cstring* cstr);
	int (*toi)(cstring* cstr);
	void (*print)(cstring* str);
	void (*namedPrint)(cstring* str, char* name);
} cstring_interface;

struct _CSTRING {
	const char* arr;
	int len;
};

extern cstring_interface cString;

#endif
