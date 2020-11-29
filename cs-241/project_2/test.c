#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "inventory/inventory.h"

/*
Assumptions
No blank spaces in product names unit
Price and quantity are `int` and user input will be int
Save file will overwrite the old file
Product name is the `id` and is case sensitive
*/

void testCreateEmptyList();
void testInsertProduct();
void testSearchProduct();
void testDeleteProduct();
void testDeleteList();
void testPurchaseProduct();
void testSellProduct();
void testValidateInput();

void check(Error error) {
	assert(error == NONE);
}

int main() {
	testCreateEmptyList();
	testInsertProduct();
	testSearchProduct();
	testDeleteProduct();
	testDeleteList();
	testPurchaseProduct();
	testSellProduct();
	testValidateInput();
	return 0;
}

void testCreateEmptyList() {
	Error err;
	List list = newList();
	assert(list->product == NULL);
	createEmptyList(list);
	assert(list->product != NULL);	
	err = destroyList(list);
	assert(err == NONE);
}

void testInsertProduct() {
	ProductRtn productRtn; 
	Error err;
	List list = newList();

	productRtn = newProduct("water", "gal", 2, 1);
	err = insertProduct(list, productRtn.product);
	assert(err == EMPTYLIST);

	
	createEmptyList(list);
	productRtn = newProduct("water", "gal", 2, 1);
	err = insertProduct(list, productRtn.product);
	assert(err == NONE);
	assert(list->product->next == productRtn.product);
	assert(strcmp(list->product->next->name, "water") == 0);
	assert(strcmp(list->product->next->unit, "gal") == 0);
	assert(list->product->next->price == 2);
	assert(list->product->next->quantity == 1);

	productRtn = newProduct("bread", "loaf", 3, 4);
	err = insertProduct(list, productRtn.product);
	assert(err == NONE);
	assert(list->product->next != productRtn.product);
	assert(list->product->next->next == productRtn.product);
	assert(list->product->next->next->price == 3);

	productRtn = newProduct("asdf", "asdf", 5, 6);
	err = insertProduct(list, productRtn.product);
	assert(err == NONE);
	assert(list->product->next->next->next == productRtn.product);

	destroyList(list);
}

void testSearchProduct() {
	ProductRtn foundProduct;
	ProductRtn productRtn;
	List list = newList();
	createEmptyList(list);

	foundProduct = searchProduct(list, "asdf");
	assert(foundProduct.product == NULL);
	assert(foundProduct.err == NOTFOUND);
	
	productRtn = newProduct("water", "gal", 2, 1);
	insertProduct(list, productRtn.product);

	foundProduct = searchProduct(list, "water");
	assert(productRtn.product == foundProduct.product);
	check(foundProduct.err);

	productRtn = newProduct("bread", "loaf", 3, 4);
	insertProduct(list, productRtn.product);
	foundProduct = searchProduct(list, "bread");
	assert(productRtn.product == foundProduct.product);
	check(foundProduct.err);

	productRtn = newProduct("salt", "oz", 5, 6);
	insertProduct(list, productRtn.product);
	foundProduct = searchProduct(list, "salt");
	assert(productRtn.product == foundProduct.product);
	check(foundProduct.err);
	
	foundProduct = searchProduct(list, "asdfasdf");
	assert(foundProduct.product == NULL);
	assert(foundProduct.err == NOTFOUND);

	destroyList(list);
}

void testDeleteProduct() {
	Error err;
	ProductRtn productRtn;
	List list = newList();
	err = deleteProduct(list, "aaaa");
	assert(err == EMPTYLIST);	

	createEmptyList(list);
	err = deleteProduct(list, "asdf");
	assert(err == NOTFOUND);
	
	productRtn = newProduct("water", "gal", 1, 2);
	insertProduct(list, productRtn.product);
	err = deleteProduct(list, "water");
	assert(err == NONE);
	err = deleteProduct(list, "water");
	assert(err == NOTFOUND);


	productRtn = newProduct("a", "a", 1, 1);
	insertProduct(list, productRtn.product);
	productRtn = newProduct("b", "b", 1, 1);
	insertProduct(list, productRtn.product);
	productRtn = newProduct("c", "c", 1, 1);
	insertProduct(list, productRtn.product);
	
	err = deleteProduct(list, "b");
	assert(err == NONE);
	err = deleteProduct(list, "a");
	assert(err == NONE);
	err = deleteProduct(list, "c");
	assert(err == NONE);

	err = deleteProduct(list, "b");
	assert(err == NOTFOUND);
	err = deleteProduct(list, "a");
	assert(err == NOTFOUND);
	err = deleteProduct(list, "c");
	assert(err == NOTFOUND);

	destroyList(list);
}

void testDeleteList() {
	Error err;
	List list = newList();
	createEmptyList(list);
	err = deleteList(list);
	assert(list->product == NULL);
	err = deleteList(list);
	assert(err == EMPTYLIST);
	destroyList(list);
}

void testPurchaseProduct() {
	Error err;
	ProductRtn productRtn;
	List list = newList();
	createEmptyList(list);


	productRtn = newProduct("water", "gal", 1, 10);
	insertProduct(list, productRtn.product);

	productRtn = searchProduct(list, "water");
	assert(productRtn.product->quantity == 10);
	
	purchaseProduct(list, "water");

	productRtn = searchProduct(list, "water");
	assert(productRtn.product->quantity == 11);

	purchaseProduct(list, "water");
	purchaseProduct(list, "water");
	productRtn = searchProduct(list, "water");
	assert(productRtn.product->quantity == 13);
	
	
	destroyList(list);
}

void testSellProduct() {
	Error err;
	ProductRtn productRtn;
	List list = newList();
	createEmptyList(list);


	productRtn = newProduct("water", "gal", 1, 3);
	insertProduct(list, productRtn.product);

	productRtn = searchProduct(list, "water");
	assert(productRtn.product->quantity == 3);
	
	sellProduct(list, "water");

	productRtn = searchProduct(list, "water");
	assert(productRtn.product->quantity == 2);

	sellProduct(list, "water");
	sellProduct(list, "water");
	productRtn = searchProduct(list, "water");
	assert(productRtn.err == NOTFOUND);
	
	
	destroyList(list);
}

void testValidateInput() {
	ProductRtn productRtn;
	productRtn = newProduct("a", "b", 0, 0);
	assert(productRtn.product == NULL);
	assert(productRtn.err == INVALIDINPUT);
}
