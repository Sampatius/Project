#pragma once
#include "Repair.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

class Shop
{
	friend std::istream &operator>> (std::ifstream &in, Shop& shop);
	friend std::ostream &operator<< (std::ostream &out, Shop& shop);
public:
	Shop();
	~Shop();

	void addRepair(std::string clientName, std::string problemDescription);
	void initRepairs(Repair repair);

	void clearRecords();
	Repair *getRepair(int i);
	void performFix(int i, std::string solution, int timeSpent);
	void topThree(int i);
	void printRepair(int i);
	int getSize();

	//Fetch repairs vector for stream operators
	inline std::vector<Repair> getRepairs() { return repairs; }

private:
	std::vector<Repair> repairs;
};

