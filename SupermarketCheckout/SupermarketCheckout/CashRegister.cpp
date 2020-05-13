#include "CashRegister.h"

CashRegister::CashRegister(Inventory inventory)
{
	scannedItems_ = {};
	inventory_ = inventory;
}

void CashRegister::scanItem(SKU item)
{
	if (scannedItems_.count(item) == 0)
	{
		scannedItems_.insert(std::make_pair(item, 1));
	}
	else
	{
		scannedItems_.find(item)->second++;
	}
}

void CashRegister::removeItem(SKU item)
{
	if (scannedItems_.count(item)  >  0)
	{
		scannedItems_.find(item)->second--;

		if (scannedItems_.find(item)->second == 0)
		{
			scannedItems_.erase(scannedItems_.find(item));
		}
	}
}

double CashRegister::getTotal()
{
	double total = 0;
	for (auto product : scannedItems_)
	{
		Product item;
		bool itemFound = inventory_.getItem(product.first, &item);
		if (!itemFound)
		{
			// Error Unknown Item scanned
			continue;
		}
		else
		{
			std::tuple<int, double> specialOffer = item.getSpecialOffers();
			if (std::get<0>(specialOffer) < product.second && std::get<0>(specialOffer) != 0)
			{
				// apply special offer
				total += ((product.second) / std::get<0>(specialOffer)) * std::get<1>(specialOffer);
				total += ((product.second)% std::get<0>(specialOffer)) * item.getPrice();
			}
			else
			{
				total += (product.second) * item.getPrice();
			}
		}
	}

	return total;
}

void CashRegister::updatePricingRules(std::vector<Product> items)
{
	for (auto item : items)
	{
		inventory_.updateItem(item);
	}
}

std::map<SKU, int> CashRegister::getScannedItems()
{
	return scannedItems_;
}
