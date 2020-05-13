#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iterator>
#include "inventory.h"
#include "CashRegister.h"

// I would have liked to have used an xml files and xml parser for this but I ran out of time to implement that
Inventory parseCheckoutRules(std::string path)
{
	std::string entry;
	std::ifstream infile;
	infile.open(path);

	Inventory storeInventory;

	while (!infile.eof()) 
	{
		getline(infile, entry); 
		std::istringstream iss(entry);
		std::vector<std::string> tokens;

		std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			back_inserter(tokens));

		// Very hacky and assumes a perfectly generated checkoutRules file
		// A xml parser woud fix this issue as we can access tags and set default values before calling function
		if(tokens.size() > 2)
		{
			storeInventory.addItem(Product(tokens[0], atof(tokens[1].c_str()), std::make_pair(atoi(tokens[2].c_str()), atof(tokens[3].c_str()))));
		}
		else
		{
			storeInventory.addItem(Product(tokens[0], atof(tokens[1].c_str())));
		}
	}

	infile.close();

	return storeInventory;
}

int main()
{
	Inventory storeInventory = parseCheckoutRules("checkoutRules.txt");
	CashRegister c_register(storeInventory);

	c_register.scanItem("apples");
	c_register.scanItem("coconuts");
	c_register.scanItem("apples");
	c_register.scanItem("donuts");
	c_register.scanItem("apples");
	c_register.scanItem("donuts");
	c_register.scanItem("donuts");
	c_register.scanItem("apples");
	c_register.scanItem("oranges");
	c_register.scanItem("apples");
	c_register.scanItem("oranges");

	std::cout.precision(2);
	std::cout<< "Total is $" << std::fixed << c_register.getTotal() << std::endl;

	return 0;
}
