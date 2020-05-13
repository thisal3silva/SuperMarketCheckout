#include "pch.h"
#include "..//SupermarketCheckout/Product.h"
#include "..//SupermarketCheckout/Inventory.h"
#include "..//SupermarketCheckout/CashRegister.h"
#include<string>


TEST(ProductClassTest, TestConstructor) {

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);
	std::tuple<int, double>  specialOffersEmpty = {};

	Product counstructor1 = Product(item, price);
	Product counstructor2 = Product(item, price, specialOffers);

	EXPECT_EQ(item, counstructor1.getProductName());
	EXPECT_EQ(price, counstructor1.getPrice());
	EXPECT_EQ(specialOffersEmpty, counstructor1.getSpecialOffers());

	EXPECT_EQ(item, counstructor2.getProductName());
	EXPECT_EQ(price, counstructor2.getPrice());
	EXPECT_EQ(specialOffers, counstructor2.getSpecialOffers());

	EXPECT_TRUE(true);
}

TEST(ProductClassTest, TestUpdate) {

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	std::string item2 = "Test1";
	double price2 = 10;
	std::tuple<int, double>  specialOffers2 = std::make_pair(3, 10);

	Product product1 = Product(item, price, specialOffers);

	EXPECT_EQ(item, product1.getProductName());
	EXPECT_EQ(price, product1.getPrice());
	EXPECT_EQ(specialOffers, product1.getSpecialOffers());

	Product product2 = Product(item2, price2, specialOffers2);

	EXPECT_EQ(item2, product2.getProductName());
	EXPECT_EQ(price2, product2.getPrice());
	EXPECT_EQ(specialOffers2, product2.getSpecialOffers());

	product1.updateItem(product2);

	EXPECT_EQ(item2, product1.getProductName());
	EXPECT_EQ(price2, product1.getPrice());
	EXPECT_EQ(specialOffers2, product1.getSpecialOffers());

	EXPECT_TRUE(true);
}

TEST(ProductClassTest, TestGetPrice) {

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	Product product1 = Product(item, price, specialOffers);

	EXPECT_EQ(price, product1.getPrice());
}

TEST(ProductClassTest, TestGetProductName) {

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	Product product1 = Product(item, price, specialOffers);

	EXPECT_EQ(item, product1.getProductName());
}

TEST(InventoryClassTest, TestAddItem) {
	Inventory inventory;

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	Product product1 = Product(item, price, specialOffers);
	Product search;

	inventory.addItem(product1);

	EXPECT_TRUE(inventory.getItem(item, &search));
	EXPECT_EQ(search.getProductName(), product1.getProductName());
	EXPECT_EQ(search.getPrice(), product1.getPrice());
	EXPECT_EQ(search.getSpecialOffers(), product1.getSpecialOffers());
}

TEST(InventoryClassTest, TestDeleteItem) {
	Inventory inventory;

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	Product product1 = Product(item, price, specialOffers);
	Product search;

	inventory.addItem(product1);

	EXPECT_TRUE(inventory.getItem(item, &search));
	EXPECT_EQ(search.getProductName(), product1.getProductName());
	EXPECT_EQ(search.getPrice(), product1.getPrice());
	EXPECT_EQ(search.getSpecialOffers(), product1.getSpecialOffers());

	EXPECT_TRUE(inventory.deleteItem(product1));
	EXPECT_FALSE(inventory.getItem(item, &search));
}

TEST(InventoryClassTest, TestUpdateItem) {
	Inventory inventory;

	std::string item = "Test";
	double price = 9.99;
	std::tuple<int, double>  specialOffers = std::make_pair(2, 12);

	double price2 = 10;
	std::tuple<int, double>  specialOffers2 = std::make_pair(3, 10);

	Product product1 = Product(item, price, specialOffers);
	Product search;

	inventory.updateItem(product1);

	EXPECT_TRUE(inventory.getItem(item, &search));
	EXPECT_EQ(search.getProductName(), product1.getProductName());
	EXPECT_EQ(search.getPrice(), product1.getPrice());
	EXPECT_EQ(search.getSpecialOffers(), product1.getSpecialOffers());

	Product product2 = Product(item, price2, specialOffers2);

	inventory.updateItem(product2);

	EXPECT_TRUE(inventory.getItem(item, &search));
	EXPECT_EQ(price2, product2.getPrice());
	EXPECT_EQ(specialOffers2, product2.getSpecialOffers());
}

TEST(CashRegisterClassTest, TestScanItem) {
	Inventory inventory;
	int numItems = 5;
	for (int i = 1; i < 5; i++)
	{
		// Add 5 items to inventory
		inventory.addItem(Product("test"+std::to_string(i), i));
	}

	CashRegister testRegister(inventory);

	testRegister.scanItem("test1");

	std::map<SKU, int> scannedItemList = testRegister.getScannedItems();
	EXPECT_EQ(1, scannedItemList.size());
	EXPECT_EQ(1, scannedItemList.find("test1")->second);	
}

TEST(CashRegisterClassTest, TestScanMultipleOfSameItem) {
	Inventory inventory;
	int numItems = 5;
	for (int i = 0; i < numItems; i++)
	{
		// Add 5 items to inventory
		inventory.addItem(Product("test" + std::to_string(i), i));
	}

	CashRegister testRegister(inventory);

	for (int i = 0; i < numItems; i++)
	{
		testRegister.scanItem("test1");
	}


	std::map<SKU, int> scannedItemList = testRegister.getScannedItems();
	EXPECT_EQ(1, scannedItemList.size());
	EXPECT_EQ(numItems, scannedItemList.find("test1")->second);
}

TEST(CashRegisterClassTest, TestScanMultipleItems) {
	Inventory inventory;
	int numItems = 5;
	for (int i = 0; i < numItems; i++)
	{
		// Add 5 items to inventory
		inventory.addItem(Product("test" + std::to_string(i), i));
	}

	CashRegister testRegister(inventory);

	for (int i = 0; i < numItems; i++)
	{
		testRegister.scanItem("test" + std::to_string(i));
	}


	std::map<SKU, int> scannedItemList = testRegister.getScannedItems();
	EXPECT_EQ(numItems, scannedItemList.size());
}

TEST(CashRegisterClassTest, TestScanMultipleItemsMultipleTimes) {
	Inventory inventory;
	int numItems = 5;
	for (int i = 0; i < numItems; i++)
	{
		// Add 5 items to inventory
		inventory.addItem(Product("test" + std::to_string(i), i));
	}

	CashRegister testRegister(inventory);

	for (int i = 0; i < numItems; i++)
	{
		testRegister.scanItem("test" + std::to_string(i));
		testRegister.scanItem("test" + std::to_string(i));
	}


	std::map<SKU, int> scannedItemList = testRegister.getScannedItems();
	EXPECT_EQ(numItems, scannedItemList.size());

	for (int i = 0; i < numItems; i++)
	{
		EXPECT_EQ(2, scannedItemList.find("test" + std::to_string(i))->second);
	}
}