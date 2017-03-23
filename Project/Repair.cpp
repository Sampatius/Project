#include "stdafx.h"
#include "Repair.h"


Repair::Repair()
{
}

Repair::Repair(std::string clientName_, std::string problemDescription_) : clientName(clientName_), problemDescription(problemDescription_), 
problemSolution(" "), timeSpent(0), status(false)
{
}

Repair::Repair(std::string clientName_, std::string problemDescription_, std::string problemSolution_, int timeSpent_, bool status_) : clientName(clientName_), problemDescription(problemDescription_), 
problemSolution(problemSolution_), timeSpent(timeSpent_), status(status_)
{
}


Repair::~Repair()
{
}

void Repair::addFix(std::string solution, int timeSpent_)
{
	problemSolution = solution;
	timeSpent = timeSpent_;
	status = true;
}

bool Repair::operator<(const Repair &other) const
{
	return status > other.status;
}

Repair::operator std::string() const
{
	return clientName + " " + problemDescription + " " + problemSolution + " " + std::to_string(timeSpent) + " " + std::to_string(status);
}
