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

void Shop::performFix(int i, std::string solution)
{
	repairs[i].addFix(solution);
}

void Shop::printRepair(int i)
{
	std::string status;
	if (repairs[i].getStatus()) {
		status = "Completed";
	}
	else {
		status = "Pending";
	}
	std::cout << repairs[i].getClient() + "\t" + repairs[i].getProblem() + "\t" + repairs[i].getSolution() << repairs[i].getTimeSpent() << "\t" <<  status << std::endl;
}

int Shop::getSize()
{
	return repairs.size();
}
