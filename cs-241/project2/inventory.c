#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"

Products newProducts() {
	size_t size = sizeof(struct Products);
	Products products = (Products)malloc(size);
	products->head = NULL;
	return products;
}
void destroyProducts(Products products) {
	free(products);
}

void createEmptyList(Products p) {
	size_t size = sizeof(struct Node);
	Node head = (Node)malloc(size);
	p->head = head;
}

void deleteList(Products p) {
	Node cur = p->head;
	Node prev = NULL;
	while (cur) {
		cur = cur->next;
	}
	p->head = NULL;
}
