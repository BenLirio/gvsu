#ifndef INVENTORY
#define INVENTORY

struct Node {
	struct Node* next;
};

typedef struct Node* Node;

struct Products {
	Node head;
};

typedef struct Products* Products;

Products newProducts();
void destroyProducts();

void createEmptyList(Products);
void deleteList(Products);

#endif
