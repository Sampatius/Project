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

Repair *Shop::getRepair(std::string client)
{
	for (auto i : repairs) {
		if (i.getClient().compare(client)) {
			return &i;
		}
		else {
			return nullptr;
		}
	}
}

Repair *Shop::getRepair(int i)
{
	return &repairs[i];
}

void Shop::performFix(int i, std::string solution, int timeSpent)
{
	repairs[i].addFix(solution, timeSpent);
}

std::string Shop::printRepair(int i)
{
	std::sort(repairs.begin(), repairs.end());
	std::string status, stringRepair;
	if (repairs[i].getStatus()) {
		status = "Completed";
	}
	else {
		status = "Pending";
	}
	stringRepair = repairs[i].getClient() + "\t" + repairs[i].getProblem() + "\t" + repairs[i].getSolution() + "\t" + std::to_string(repairs[i].getTimeSpent()) + "\t" + status;
	return stringRepair;
}

int Shop::getSize()
{
	return repairs.size();
}
