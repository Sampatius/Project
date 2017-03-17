#include "stdafx.h"
#include "Repair.h"


Repair::Repair()
{
}

Repair::Repair(std::string clientName_, std::string problemDescription_) : clientName(clientName_), problemDescription(problemDescription_), 
problemSolution(" "), timeSpent(0), status(false)
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

bool Repair::operator<(const Repair other) const
{
	return status > other.status;
}
