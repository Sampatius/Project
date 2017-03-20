#include "stdafx.h"
#include "Shop.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

//Add repair with given client name and problem
void Shop::addRepair(std::string clientName, std::string problemDescription)
{
	Repair repair(clientName, problemDescription);
	repairs.push_back(repair);
}

void Shop::initRepairs(Repair repair)
{
	repairs.push_back(repair);
}

//Clears all repairs from the records
void Shop::clearRecords()
{
	repairs.clear();
}

//Returns a repair object
Repair *Shop::getRepair(int i)
{
	return &repairs[i];
}

//Performs fix to selected repair with given solution and time
void Shop::performFix(int i, std::string solution, int timeSpent)
{
	repairs[i].addFix(solution, timeSpent);
}

//Sorts out the top three hardest repairs and prints it out
void Shop::topThree(int i)
{
	std::string status, returnString;
	if (repairs.empty()) {
		std::cout << "No repairs." << std::endl;
	}
	else {
		std::sort(repairs.begin(), repairs.end(), [](Repair& lhs, Repair& rhs) {return lhs.getTimeSpent() > rhs.getTimeSpent(); });
		if (repairs[i].getStatus()) {
			status = "Completed";
		}
		else {
			status = "Pending";
		}
		std::cout << std::left << std::setw(20) << repairs[i].getClient() << std::setw(20) << std::to_string(repairs[i].getTimeSpent()) << std::setw(20) << status << std::endl;
	}
}

//Formats the selected repair to printable form and then prints it
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

//Returns the size of the repairs vector
int Shop::getSize()
{
	return repairs.size();
}

//Write in to a file
std::istream & operator>>(std::ifstream & in, Shop& shop)
{
	std::string line;
	std::string clientName, problemDescription, problemSolution;
	int timeSpent = 0;
	bool status = false;
	std::fstream f;
	f.open("test.txt");
	if (f.fail()) {
		// throw error here
		std::cout << "Error: Could not open file." << std::endl;
		return in;
	}
	while (!f.eof()) {
		std::getline(f, line);
		std::istringstream iss(line);
		std::getline(iss, clientName, ':');
		std::getline(iss, problemDescription, ':');
		std::getline(iss, problemSolution, ':');
		std::getline(iss, std::to_string(timeSpent), ':');
		std::getline(iss, std::to_string(status), ':');
		Repair repair(clientName, problemDescription, problemSolution, timeSpent, status);
		shop.initRepairs(repair);
	}
	f.close();
	return in;
}

//Read from a file
std::ostream & operator<<(std::ostream & out, Shop& shop)
{
	std::ofstream f;
	f.open("test.txt");
	for (int i = 0; i < shop.getRepairs().size(); i++) {
		f << shop.getRepair(i)->getClient() + ":" + shop.getRepair(i)->getProblem() + ":" + shop.getRepair(i)->getSolution() + ":" + std::to_string(shop.getRepair(i)->getTimeSpent()) + ":" + std::to_string(shop.getRepair(i)->getStatus()) << std::endl;
	}
	f.close();
	return out;
}
