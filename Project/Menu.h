#pragma once
#include "Shop.h"
#include <Windows.h>

class Menu
{
public:
	Menu();
	~Menu();

	void moveUp();
	void moveDown();

	void printMenu();
	void readKey();
	void menuLoop();
	void handleEnter();

	void addTask();

	void printAll();

private:
	int position = 0;
	std::vector<std::string> menuOptions;
	Shop shop;
	bool loopTheMenu;
};

