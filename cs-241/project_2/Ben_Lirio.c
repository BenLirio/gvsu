#include <stdio.h>
#include "inventory/inventory.h"

void printOptions();
int getOption();
void one(List);
void two(List);
void three(List);
void four(List);
void five(List);
void six(List);
void seven(List);
void eight(List);
void nine(List);

int main() {
	int input;
	List list = newList();
	while (1) {
		printOptions();
		printf("Enter Option: ");
		scanf("%d", &input);
		switch(input) {
			case 1:
				one(list);
				break;
			case 2:
				two(list);
				break;
			case 3:
				three(list);
				break;
			case 4:
				four(list);
				break;
			case 5:
				five(list);
				break;
			case 6:
				six(list);
				break;
			case 7:
				seven(list);
				break;
			case 8:
				eight(list);
				break;
			case 9:
				nine(list);
				break;
			case 0:
				destroyList(list);
				return 0;
				break;
			default:
				printf("Default\n");
				break;
		}
		printf("\n");
	}
	return 0;
}

void printOptions() {
	printf("1: Create and empty List\t2: Insert a product\n");
	printf("3: Delete a product\t\t4: Delete the entire list\n");
	printf("5: Search a product\t\t6: Display products in the list\n");
	printf("7: Purchase a product\t\t8: Sell a product\n");
	printf("9: Save to file\t\t\t0: Exit\n");
}
void one(List list) {
	Error err = createEmptyList(list);
	if (err != NONE) {
		printf("Error Creating List\n");
	}
	printf("Empty List Created\n");
}
void two(List list) {
	Error err;
	ProductRtn productRtn;
	char name[128];
	char unit[128];
	int price;
	int quantity;
	if (list->product == NULL) {
		printf("Please create an empty list first\n");
		return;
	}
	printf("Enter Product Details (name, unit, price, quantity): ");
	scanf("%s %s %d %d", name, unit, &price, &quantity);
	productRtn = newProduct(name, unit, price, quantity);
	if (productRtn.err != NONE) {
		if (productRtn.err == INVALIDINPUT) {
			printf("Invalid Product\n");
		}
		printf("Did not create product\n");
	} else {
		err = insertProduct(list, productRtn.product);
		if (err != NONE) {
			if (err == EMPTYLIST) {
				printf("Please first create a list\n");
			}
			if (err == PRODUCTEXISTS) {
				printf("Product already exists\n");
			}
			printf("Did not create product\n");
		} else {
			printf("Created Product\n");
		}
	}


}

void three(List list) {
	Error err;
	char name[128];
	printf("Which product would you like to delete? ");
	scanf("%s", name);
	err = deleteProduct(list, name);
	if (err != NONE) {
		if (err == EMPTYLIST) {
			printf("Please first create a list\n");
		}
		if (err == NOTFOUND) {
			printf("Product not found\n");
		}
		printf("Product was not deleted\n");

	} else {
		printf("Product Deleted\n");
	}
}

void four(List list) {
	Error err;
	err = deleteList(list);
	if (err != NONE) {
		if (err == EMPTYLIST) {
			printf("Cannot delete list before it is created\n");
		}
		printf("List was not deleted\n");
	}
	else {
		printf("List deleted\n");
	}
}

void five(List list) {
	char name[128];
	if (list->product == NULL) {
		printf("Please create an empy list frist\n");
	}
	printf("Which product would you like to search for? ");
	scanf("%s", name);
	ProductRtn productRtn;
	productRtn = searchProduct(list, name);
	if (productRtn.err != NONE) {
		if (productRtn.err == EMPTYLIST) {
			printf("Please create a list first\n");
		}
		if (productRtn.err == NOTFOUND) {
			printf("Product Not Found\n");
		}
		printf("Search failed\n");
	}
	else {
		printf("Product Found\n");
	}
}

void six(List list) {
	Product cur = list->product;
	if (cur == NULL) {
		printf("Please create a list first\n");
		return;
	}
	cur = cur->next;
	printf("NAME\tUNIT\tPRICE\tQUANTITY\n");
	while(cur) {
		printf("%s\t%s\t%d\t%d\n", cur->name, cur->unit, cur->price, cur->quantity);
		cur = cur->next;
	}
}

void seven(List list) {
	char name[128];
	if (list->product == NULL) {
		printf("Please create an empy list frist\n");
		return;
	}
	printf("Which product would you like to purchase? ");
	scanf("%s", name);
	Error err;
	err = purchaseProduct(list, name);
	if (err != NONE) {
		if (err == NOTFOUND) {
			printf("You can only purchase a product you already have\n");
		}
		if (err == EMPTYLIST) {
			printf("Please first create a list\n");
		}
	}
	else {
		printf("Purchase Success\n");
	}
}

void eight(List list) {
	char name[128];
	if (list->product == NULL) {
		printf("Please create an empy list frist\n");
	}
	printf("Which product would you like to sell? ");
	scanf("%s", name);
	Error err;
	err = sellProduct(list, name);
	if (err != NONE) {
		if (err == NOTFOUND) {
			printf("You can only sell a product you already have\n");
		}
		if (err == EMPTYLIST) {
			printf("Please first create a list\n");
		}
	}
	else {
		printf("Sell Success\n");
	}
}

void nine(List list) {
	FILE *fp;
	Product cur = list->product;
	if (cur == NULL) {
		printf("Plase create a list first\n");
		return;
	}
	cur = cur->next;
	fp = fopen("save.txt", "w+");
	while(cur) {
		fprintf(fp, "%s,%s,%d,%d\n", cur->name, cur->unit, cur->price, cur->quantity);
		cur = cur->next;
	}
	fclose(fp);
}
