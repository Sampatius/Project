#include "stdafx.h"
#include "Repair.h"


Repair::Repair()
{
}

Repair::Repair(std::string clientName_, std::string problemDescription_) : clientName(clientName_), problemDescription(problemDescription_), 
problemSolution(" "), status("Pending"), timeSpent(0)
{
}

Repair::Repair(std::string clientName_, std::string problemDescription_, std::string problemSolution_, std::string status_, int timeSpent_) : clientName(clientName_), problemDescription(problemDescription_), 
problemSolution(problemSolution_), status(status_), timeSpent(timeSpent_)
{
}


Repair::~Repair()
{
}

void Repair::addFix(std::string solution, int timeSpent_)
{
	problemSolution = solution;
	timeSpent = timeSpent_;
	status = "Completed";
}

bool Repair::operator<(const Repair &other) const
{
	return status < other.status;
}
