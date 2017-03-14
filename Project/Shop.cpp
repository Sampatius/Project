#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::addRepair(std::string clientName, std::string problemDescription)
{
	Repair repair(clientName, problemDescription);
	repairs.push_back(repair);
}

void Shop::clearRecords()
{
	repairs.clear();
}

Repair Shop::getRepair(std::string client)
{
	for (auto i : repairs) {
		if (i.getClient().compare(client)) {
			return i;
		}
	}
}

Repair Shop::getRepair(int i)
{
	return repairs[i];
}

void Shop::printRepair(int i)
{
	std::cout << repairs[i].getClient() + " " + repairs[i].getProblem() + " " + repairs[i].getSolution() << repairs[i].getTimeSpent() <<  repairs[i].getStatus() << std::endl;
}

int Shop::getSize()
{
	return repairs.size();
}
