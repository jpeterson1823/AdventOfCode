#ifndef __LIST_H__
#define __LIST_H__
#include "node.h"

typedef struct LINKED_LIST list;

typedef struct LIST_INTERFACE {
	list* (*create)(char* data, int len);
	void (*destroy)(list* l);
	void (*append)(list* l, char* data, int len);
	void (*remove)(list* l, int index);
	void (*print)(list* l);
	void (*pop)(list* l);
} list_interface;

struct LINKED_LIST {
	node* head;
	node* tail;
	node* current;
	int len;
};

extern list_interface List;

#endif
