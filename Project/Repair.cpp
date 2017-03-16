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

void Repair::addFix(std::string solution)
{
	problemSolution = solution;
}
