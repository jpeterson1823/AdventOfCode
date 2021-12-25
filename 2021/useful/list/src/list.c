#include "../include/list.h"
#include <stdlib.h>
#include <stdio.h>

void list_init(list l) {
	l.current = l.head;
	l.tail = l.head;
}

void list_append(list l, node n) {
	// dynamically deepcopy node 'n'
	node* N = malloc(sizeof(node));

	// add N to the list
	if (l.head == NULL) {
		l.head = N;
		l.len++;
	} else {
		l.tail->next = N;
		l.tail = N;
	}
}

void list_pop(list l) {
	// move to node before last
	l.current = l.head;
	for (int i = 0; i < l.len - 1; i++)
		l.current = l.current->next;
	// free alloc'd memory at tail node
	free(l.tail);
	// set tail to this node
	l.tail = l.current;
	// set current back to head
	l.current = l.head;
	// decrement length counter
	l.len--;
}

void list_remove(list l, int index) {
	perror("NotYetImplementedError: 'list_remove(...)' not yet implemented");
}
