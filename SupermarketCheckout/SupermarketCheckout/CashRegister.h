#ifndef cash_register_h
#define cash_register_h

#include<map>
#include<vector>
#include"Product.h"
#include"Inventory.h"
#include<tuple>

class CashRegister
{
private:
	std::map<SKU, int> scannedItems_;
	Inventory inventory_;

public:
	CashRegister(Inventory inventory);
	void scanItem(SKU item);
	void removeItem(SKU item);
	double getTotal();
	void updatePricingRules(std::vector<Product> items);
	std::map<SKU, int> getScannedItems();
};

#endif