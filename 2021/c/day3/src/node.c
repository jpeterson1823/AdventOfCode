#include "../include/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node* node_constructor(char* data, int len) {
	// deepcopy data; use (len+1) to account for null terminator
	char* str = malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < len; i++)
		str[i] = data[i];
	str[len] = '\0';

	// construct node
	node* n = malloc(sizeof(node));
	n->data = str;
	n->next = NULL;

	// return constructed node
	return n;
}

node* node_destructor(node* n) {
	// take note of node's 'next' pointer
	node* next;
	if (n->next == NULL)
		next = NULL;
	else
		next = n->next;

	// free alloc'd str
	free(n->data);
	// free the node itself
	free(n);

	// return the next pointer, NULL or not.
	return next;
}

void node_init(node* self, char* data) {
	self->data = data;
}

void node_print(node* self) {
	printf("node ==> '%s'\n", self->data);
}

// create node interface to aid in ease of use
node_interface Node = {
	.create = node_constructor,
	.destroy = node_destructor,
	.init = node_init,
	.print = node_print
};
