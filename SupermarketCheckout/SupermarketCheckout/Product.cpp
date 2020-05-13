#include "Product.h"

Product::Product()
{
	sku_ = "";
	price_ = 0;
	inventory_ = 0;
	specialOffers_ = {};
}

Product::Product(SKU sku, double price)
{
	sku_ = sku;
	price_ = price;
	inventory_ = 0;
	specialOffers_ = {};
}

Product::Product(SKU sku, double price, std::tuple<int, double> specialOffers)
{
	sku_ = sku;
	price_ = price;
	inventory_ = 0;
	specialOffers_ = specialOffers;
}

double Product::getPrice()
{
	return price_;
}

std::string Product::getProductName()
{
	return sku_;
}

int Product::getNumInStock()
{
	return inventory_;
}

bool Product::checkoutItem(int numItems)
{
	// Todo : Implement if required
	/*if (inventory_ < numItems)
	{
		return false;
	}
	else
	{
		inventory_ -= numItems;
	}*/
	return true;
}

void Product::addSpecialOffer(std::tuple<int, double> specialOffer)
{
	specialOffers_ = specialOffer;
}

void Product::updateItem(Product item)
{
	sku_ = item.getProductName();
	price_ = item.getPrice();
	inventory_ = item.getInventory();
	specialOffers_ = item.getSpecialOffers();
}

int Product::getInventory()
{
	return inventory_;
}

std::tuple<int, double> Product::getSpecialOffers()
{
	return specialOffers_;
}
