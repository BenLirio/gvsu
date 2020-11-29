#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER

enum Error {NONE, PRODUCTEXISTS, EMPTYLIST, NOTFOUND, INVALIDINPUT};
typedef enum Error Error;

struct Product {
	char name[128];
	char unit[128];
	int price;
	int quantity;
	struct Product* next;
	struct Product* prev;
};
typedef struct Product* Product;
struct ProductRtn {
	Product product;
	Error err;
};
typedef struct ProductRtn ProductRtn;
	

struct List {
	Product product;
};
typedef struct List* List;

List newList();
Error destroyList(List);

ProductRtn newProduct();
Error destroyProduct(Product);

Error createEmptyList(List);
Error deleteList(List);
Error insertProduct(List, Product);
ProductRtn searchProduct(List, char[128]);
Error deleteProduct(List, char[128]);
Error purchaseProduct(List, char[128]);
Error sellProduct(List, char[128]);

#endif
