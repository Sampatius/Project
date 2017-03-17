#include "stdafx.h"
#include "Shop.h"
#include <iomanip>


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

void Shop::topThree(int i)
{
	std::string status, returnString;
	std::sort(repairs.begin(), repairs.end(), [](Repair& lhs, Repair& rhs) {return lhs.getTimeSpent() > rhs.getTimeSpent(); });
	if (repairs[i].getStatus()) {
		status = "Completed";
	}
	else {
		status = "Pending";
	}
	std::cout << std::left << std::setw(20) << repairs[i].getClient() << std::setw(20) << std::to_string(repairs[i].getTimeSpent()) << std::setw(20) << status << std::endl;
}

void Shop::printRepair(int i)
{
	std::sort(repairs.begin(), repairs.end());
	std::string status, stringRepair;
	if (repairs[i].getStatus()) {
		status = "Completed";
	}
	else {
		status = "Pending";
	}
	std::cout  << std::left << std::setw(20) << repairs[i].getClient() << std::setw(20) << status << std::endl;
}

int Shop::getSize()
{
	return repairs.size();
}
