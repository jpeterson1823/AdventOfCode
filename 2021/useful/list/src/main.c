#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

int main() {
	printf("Creating list...\n");
	list* l = List.create("First", 5);

	printf("Appending list:\n\t");
	List.append(l, "Second", 6);
	List.append(l, "Third", 5);
	List.print(l);

	printf("Removing middle element from list:\n\t");
	List.remove(l, 1);
	List.print(l);

	printf("Popping list:\n\t");
	List.pop(l);
	List.print(l);

	printf("Destroying list...\n");
	List.destroy(l);
	
	return 0;
}
