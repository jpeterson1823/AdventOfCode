#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

int main() {
	printf("Creating list...\n");
	list* og = List.create("First", 5);

	printf("Appending list:\n\t");
	List.append(og, "Second", 6);
	List.append(og, "Third", 5);
	List.print(og);

	printf("Copying list...\n");
	list* copy = List.copy(og);

	printf("%s\n", List.get(copy, 0));

	printf("Destroying lists...\n");
	List.destroy(og);
	List.destroy(copy);
	
	return 0;
}
