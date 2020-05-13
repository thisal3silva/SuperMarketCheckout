#ifndef inventory_h
#define inventory_h

#include<map>
#include"Product.h"

class Inventory
{
private:
	std::map<SKU, Product> inventoryList_;

public:
	Inventory();
	bool addItem(Product item);
	bool deleteItem(Product item);
	bool updateItem(Product item);
	bool getItem(SKU sku, Product* product);
	bool clearInventory();
};
#endif