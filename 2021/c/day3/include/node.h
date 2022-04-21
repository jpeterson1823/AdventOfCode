#ifndef __NODE_H__
#define __NODE_H__

typedef struct NODE node;


typedef struct NODE_INTERFACE {
	node* (*create)(char*data, int len);
	node* (*destroy)(node* n);
	void (*init)(node* self, char* data);
	void (*print)(node* self);
} node_interface;

struct NODE {
	char* data;
	node* next;
};

extern node_interface Node;

#endif
