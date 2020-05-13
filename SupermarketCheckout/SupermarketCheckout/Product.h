#ifndef product_h.
#define product_h

#include<string>
#include<vector>
#include<tuple>

typedef std::string SKU;

class Product
{
private:
	SKU sku_;
	double price_;
	int inventory_;
	std::tuple<int, double> specialOffers_;

public:
	Product();
	Product(SKU sku, double price);
	Product(SKU sku, double price, std::tuple<int, double>  specialOffers);
	double getPrice();
	SKU getProductName();
	int getNumInStock();
	bool checkoutItem(int numItems);
	void addSpecialOffer(std::tuple<int, double> specialOffer);
	void updateItem(Product item);
	int getInventory();
	std::tuple<int, double>  getSpecialOffers();
};

#endif