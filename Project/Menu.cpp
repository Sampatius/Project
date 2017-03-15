#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : loopTheMenu(true)
{
	menuOptions = { "Add task", "Save repairs", "Load repairs", "Perform fix", "Top 3", "Print all", "Clear records", "Exit" };
}


Menu::~Menu()
{
}

void Menu::moveUp()
{
	position--;
	if (position == -1) {
		position = menuOptions.size()-1;
	}
}

void Menu::moveDown()
{
	position++;
	if (position == menuOptions.size()) {
		position = 0;
	}
}

void Menu::printMenu()
{
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	std::cout << "Main menu\n\n";

	for (int i = 0; i < menuOptions.size(); i++) {
		if (i == position) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			std::cout << menuOptions[i] << std::endl;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << menuOptions[i] << std::endl;
		}
	}
}

void Menu::readKey()
{
	BOOL done = FALSE;
	DWORD        mode;
	INPUT_RECORD event;

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hstdin, &mode);

	SetConsoleMode(hstdin, 0);
	
	while (!done) {
		printMenu();
		DWORD count;
		ReadConsoleInput(hstdin, &event, 1, &count);
		if ((event.EventType == KEY_EVENT) && !event.Event.KeyEvent.bKeyDown) {
			switch (event.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP:
				moveUp();
				break;
			case VK_DOWN:
				moveDown();
				break;
			case VK_RETURN:
				while (GetAsyncKeyState(VK_RETURN) & 0x8000 != 0);
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				handleEnter();
				break;
			default:
				done = TRUE;
			}
		}
	}
}

void Menu::menuLoop()
{
	while (loopTheMenu) {
		system("cls");

		printMenu();

		readKey();
	}
}

void Menu::handleEnter()
{
	switch (position) {
	case 0:
		addTask();
		break;
	case 1:
		std::cout << "\n\nSave repairs" << std::endl;
		break;
	case 2:
		std::cout << "\n\nLoad repairs" << std::endl;
		break;
	case 3:
		std::cout << "\n\nPerform fix" << std::endl;
		break;
	case 4:
		std::cout << "\n\nTop 3" << std::endl;
		break;
	case 5:
		printAll();
		break;
	case 6:
		std::cout << "\n\nClear records" << std::endl;
		break;
	case 7:
		std::cout << "\n\nExit" << std::endl;
		break;
	}
}

void Menu::addTask()
{
	std::string clientsName, problemDescription;

	system("cls");
	std::cout << "Enter name of the client: ";
	std::getline (std::cin, clientsName);
	std::cout << std::endl;
	std::cout << "Enter description of the problem: ";
	std::getline (std::cin, problemDescription);
	shop.addRepair(clientsName, problemDescription);
}

void Menu::printAll()
{
	system("cls");
	std::cout << "Client name\tProblem description\tTime spent\tCompleted" << std::endl;
	std::cout << "=================================================================" << std::endl;
	for (int i = 0; i < shop.getSize(); i++) {
		shop.printRepair(i);
	}
	system("pause");
}
