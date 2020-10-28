#include<stdio.h>
#include<stdlib.h>

struct node 
{
	int data;
	struct node *next;
};

struct node *init ();
void insert(struct node *head, int data); 
void display (struct node *head); 
void deleteAll (struct node *head); 

struct node *init()
{
	// Allocate memory for the head of the linked list
	struct node* head = (struct node*) malloc(sizeof(struct node));
	return head;
}

void insert (struct node *head, int data)
{
	// Allocate memory for the new node
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->data = data;
	struct node* cur = head;
	// Go to the last linked item
	while(cur->next) {
		cur = cur->next;
	}
	// Set the last item's next to the new node
	cur->next = newNode;
}

void display (struct node *head)
{
	struct node * cur = head;
	cur = cur->next;
	while(cur) {
		// Display each node inside
		printf("%d\n", cur->data);
		cur = cur->next;
	}
}

void deleteAll (struct node *head)
{
	struct node * cur = head;
	struct node * prev;
	while(cur->next) {
		prev = cur;
		cur = cur->next;
		// Keep a reference to the prev in order to free it
		free(prev);
	}
	free(cur);
}

int main()
{
	int array[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	struct node *head;
	head = init();
	int i;
	for (i=0;i<10;i++) 
	{
		insert(head, array[i]);
	}
	display(head);
	deleteAll(head);
	
	return 1;
}
