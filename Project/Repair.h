#pragma once
#include <string>
#include <iostream>

class Repair
{
public:
	Repair();
	Repair(std::string clientName_, std::string problemDescription_);
	~Repair();

	inline std::string getClient() { return clientName; }
	inline std::string getProblem() { return problemDescription; }
	inline std::string getSolution() { return problemSolution; }
	inline int getTimeSpent() { return timeSpent; }
	inline bool getStatus() { return status; }

	void addFix(std::string solution, int timeSpent_);

	bool operator<(const Repair other) const;

private:
	std::string clientName;
	std::string problemDescription;
	std::string problemSolution;
	int timeSpent;
	bool status;
};

