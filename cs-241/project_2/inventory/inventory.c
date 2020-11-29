#include "inventory.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

List newList() {
	List list = (List) malloc(sizeof(struct List));
	list->product = NULL;
	return list;
}

Error destroyList(List list) {
	Error err;
	err = destroyProduct(list->product);
	free(list);	
	return err;
}

Error createEmptyList(List list) {
	ProductRtn productRtn;
	productRtn = newProduct("", "", 1, 1);
	list->product = productRtn.product;
	return productRtn.err;
}

ProductRtn newProduct(char name[128], char unit[128], int price, int quantity) {
	ProductRtn productRtn;
	if (price <= 0 || quantity <= 0) {
		productRtn.product = NULL;
		productRtn.err = INVALIDINPUT;
		return productRtn;
	}
	Product product = (Product) malloc(sizeof(struct Product));
	strcpy(product->name, name);
	strcpy(product->unit, unit);
	product->price = price;
	product->quantity = quantity;
	product->next = NULL;
	product->prev = NULL;
	productRtn.product = product;
	productRtn.err = NONE;
	return productRtn;
}

Error destroyProduct(Product product) {
	Error err;
	if (product == NULL)
		return NONE;
	err = destroyProduct(product->next);
	free(product);
	return err;
}

Error insertProduct(List list, Product product) {
	if (list->product == NULL) {
		return EMPTYLIST;
	}
	Product cur = list->product;
	ProductRtn productRtn = searchProduct(list, product->name);
	if (productRtn.err == NONE) {
		return PRODUCTEXISTS;
	}
	while(cur->next) {
		cur = cur->next;
	}
	cur->next = product;
	product->prev = cur;
	return NONE;
}

ProductRtn searchProduct(List list, char name[128]) {
	ProductRtn productRtn;
	if (list->product == NULL) {
		productRtn.product = NULL;
		productRtn.err = EMPTYLIST;
		return productRtn;
	}
	Product cur = list->product;
	while(cur) {
		if (strcmp(cur->name, name) == 0) {
			productRtn.product = cur;
			productRtn.err = NONE;
			return productRtn;
		}
		cur = cur->next;
	}
	productRtn.product = NULL;
	productRtn.err = NOTFOUND;
	return productRtn;
}

Error deleteProduct(List list, char name[128]) {
	if (list->product == NULL) {
		return EMPTYLIST;
	}
	Error err;
	ProductRtn foundProduct;
	foundProduct = searchProduct(list, name);
	if (foundProduct.err != NONE) {
		return foundProduct.err;
	}
	Product prev = foundProduct.product->prev;
	Product next = foundProduct.product->next;
	prev->next = next;
	if (next) {
		next->prev = prev;
	}
	return NONE;
}

Error deleteList(List list) {
	Product product = list->product;
	if(product == NULL) {
		return EMPTYLIST;
	}
	list->product = NULL;
	destroyProduct(product);
	return NONE;
}

Error purchaseProduct(List list, char name[128]) {
	ProductRtn productRtn;
	productRtn = searchProduct(list, name);
	if (productRtn.err != NONE) {
		return productRtn.err;
	}
	productRtn.product->quantity += 1;
	return NONE;
}


Error sellProduct(List list, char name[128]) {
	ProductRtn productRtn;
	productRtn = searchProduct(list, name);
	if (productRtn.err != NONE) {
		return productRtn.err;
	}
	productRtn.product->quantity -= 1;
	if (productRtn.product->quantity == 0) {
		deleteProduct(list, name);
	}
	return NONE;
}
