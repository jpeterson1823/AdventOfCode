#include "../include/list.h"
#include "../include/node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

list* list_create(char* data, int len) {
	// alloc memory for list, and check to make sure memory was properly alloc'd
	list* l = malloc(sizeof(list));

	// create head node with str as data
	node* n = Node.create(data, len);

	// add node to list as the head node
	l->head = n;

	// initialize other values
	l->current = l->head;
	l->tail = l->head;
	l->len = 1;

	// return constructed list
	return l;
}

void list_destroy(list* l) {
	// go through each node in the list and call it's destructor
	l->current = l->head;
	while (l->current != NULL)
		l->current = Node.destroy(l->current);
	// free alloc'd memory in list itself
	free(l);
}

void list_append(list* l, char* data, int len) {
	// create new node
	node* n = Node.create(data, len);

	// if list is empty, init head
	if (l->head == NULL)
		l->head = n;
	else {
		// set tail's next node to n
		l->tail->next = n;
		// set tail to n
		l->tail = n;
		// increment len
		l->len++;
	}
}

void list_remove(list* l, int index) {
	// check to make sure within bounds
	if (index == l->len) {
		perror("IndexOutOfBoundsError: Attempted to remove element of list outside of list bounds.\n");
	} else {
		// move to element before the one to remove
		l->current = l->head;
		for (int i = 0; i < index-1; i++)
			l->current = l->current->next;
		
		// take note of next's 'next' pointer
		node* next = l->current->next->next;
		// destroy current's next node
		Node.destroy(l->current->next);
		// remove the gap between nodes
		l->current->next = next;
		
		// decrement len
		l->len--;
	}
}

void list_pop(list* l) {
	// decrement len
	l->len--;
	// move to element before the one to delete
	l->current = l->head;
	for (int i = 0; i < l->len-1; i++)
		l->current = l->current->next;

	// set tail to current
	l->tail = l->current;
	// destroy data at current's next pointer
	Node.destroy(l->current->next);
	// set current's pointer to NULL
	l->current->next = NULL;
	// set current back to head
	l->current = l->head;
}

void list_print(list* l) {
	// print str header
	printf("PRINT ==> {");

	// set current pointer to head of list
	l->current = l->head;
	for (int i = 0; i < l->len-1; i++) {
		printf("'%s', ", l->current->data);
		// update current pointer
		l->current = l->current->next;
	}
	// print last element in line with previous formatting
	printf("'%s'}\n", l->current->data);

	// reset current pointer back to head
	l->current = l->head;
}

char* list_get(list* l, int index) {
	if (index >= l->len) {
		fprintf(stderr, "[ OutOfBoundsException ]\n\t==> Attemped to access element outside of list bounds.\n\t==> Exiting...\n");
		exit(-1);
	}
	// set current to head node
	l->current = l->head;
	for (int i = 0; i < index; i++)
		l->current = l->current->next;
	// return the data at the node
	return l->current->data;

}

list* list_copy(list* og) {
	og->current = og->head;
	list* copy = List.create(og->current->data, strlen(og->current->data));

	for (int i = 1; i < og->len; i++) {
		og->current = og->current->next;
		List.append(copy, og->current->data, strlen(og->current->data));
	}

	return copy;
}

list_interface List = {
	.create = list_create,
	.destroy = list_destroy,
	.append = list_append,
	.remove = list_remove,
	.pop = list_pop,
	.get = list_get,
	.print = list_print,
	.copy = list_copy
};
