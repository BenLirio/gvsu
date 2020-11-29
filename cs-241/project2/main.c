#include <stdio.h>
#include <assert.h>
#include "inventory.h"

void test();

int main()
{
	test();
	/*
	int action;
	Item head;
	while (1) {
		printf("1: Create an empty list\t\t2: Insert a product\n");
		printf("%p\n", head);
		scanf("%d", &action);  
		switch(action) {
			case 1:
				head = createEmptyList();
				printf("Action 1\n");
				break;
			case 2:
				printf("Action 2\n");
				break;
			case 3:
				break;
			case 4:
				break;
		}
	}
	*/
}


void test(){

	Products products = newProducts();
	assert(products->head == NULL);

	createEmptyList(products);
	assert(products->head != NULL);
	assert(products->head->next != NULL);

	deleteList(products);

	destroyProducts(products);
};
