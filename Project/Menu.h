#pragma once
#include "Shop.h"
#include <Windows.h>
#include <iomanip>

#undef max

class Menu
{
public:
	Menu();
	~Menu();

	void moveUp(std::vector<std::string> *menu);
	void moveDown(std::vector<std::string> *menu);

	void printMenu(std::vector<std::string> &menu);
	int readKey(std::vector<std::string> *menu);
	void menuLoop();
	void handleEnter(int position);

	void addTask();

	void performFix(int position);
	void topThree();

	void repairsMenu();
	void printAll();

private:
	int position = 0;
	std::vector<std::string> menuOptions;
	Shop shop;
	bool loopTheMenu;
};

