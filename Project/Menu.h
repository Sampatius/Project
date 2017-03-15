#pragma once
#include "Shop.h"
#include <Windows.h>

class Menu
{
public:
	Menu();
	~Menu();

	void moveUp(std::vector<std::string> *menu);
	void moveDown(std::vector<std::string> *menu);

	void printMenu();
	void readKey();
	void menuLoop();
	void handleEnter();

	void addTask();

	void repairsMenu();
	void printAll();

private:
	int position = 0;
	std::vector<std::string> menuOptions;
	Shop shop;
	bool loopTheMenu;
};

