#pragma once
#include "Repair.h"
#include <vector>
#include <algorithm>
#include <iterator>

class Shop
{
public:
	Shop();
	~Shop();

	void addRepair(std::string clientName, std::string problemDescription);
	void clearRecords();
	
	Repair *getRepair(std::string client);
	Repair *getRepair(int i);

	void performFix(int i, std::string solution, int timeSpent);

	void topThree(int i);

	void printRepair(int i);
	int getSize();

private:
	std::vector<Repair> repairs;
};

