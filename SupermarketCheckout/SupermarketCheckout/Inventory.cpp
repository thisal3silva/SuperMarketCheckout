#include "Inventory.h"
#include<map>

Inventory::Inventory()
{
	inventoryList_ = {};
}

bool Inventory::addItem(Product item)
{
	if (inventoryList_.count(item.getProductName()) == 0)
	{
		inventoryList_.insert(std::make_pair(item.getProductName(), item));
		return true;
	}
	return false;
}

bool Inventory::deleteItem(Product item)
{
	if (inventoryList_.count(item.getProductName()) == 1)
	{
		inventoryList_.erase(inventoryList_.find(item.getProductName()));
		return true;
	}
	return false;
}

bool Inventory::updateItem(Product item)
{
	if (inventoryList_.count(item.getProductName()) == 1)
	{
		(inventoryList_.find(item.getProductName())->second).updateItem(item);
	}
	else
	{
		addItem(item);
	}
	return false;
}

bool Inventory::getItem(SKU sku, Product* product)
{
	if (inventoryList_.count(sku) == 1)
	{
		product->updateItem(inventoryList_.find(sku)->second);
		return true;
	}

	return false;
}

bool Inventory::clearInventory()
{
	inventoryList_.clear();
	return true;
}
