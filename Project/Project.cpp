// Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Menu.h"


int main()
{
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);
	Menu menu = Menu();
	menu.menuLoop();
    return 0;
}

