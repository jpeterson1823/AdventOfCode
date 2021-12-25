#ifndef __LIST_H__
#define __LIST_H__

/**
 * Node datatype
 *
 * @param data		pointer to data for the node
 * @param next		pointer to the next Node
 */
typedef struct Node {
	void* data;
	struct Node* next;
} node;

/**
 * Linked List datatype
 *
 * @param head 			first element in the list
 * @param tail 			last element in the list
 * @param current		pointer for the currently selected item
 * @param numElements	number of elements in the list currently
 */
typedef struct LinkedList {
	node* head;
	node* tail;
	node* current;
	int len;
} list;

void node_init(node* n, void* data, node* next);

void list_init(list l);
void list_append(list l, node n);
void list_pop(list l);
void list_remove(list l, int index);

#endif
