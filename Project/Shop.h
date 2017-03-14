#pragma once
#include "Repair.h"
#include <vector>

class Shop
{
public:
	Shop();
	~Shop();

	void addRepair(std::string clientName, std::string problemDescription);
	void clearRecords();
	
	Repair getRepair(std::string client);
	Repair getRepair(int i);

	void printRepair(int i);
	int getSize();

private:
	std::vector<Repair> repairs;
};

