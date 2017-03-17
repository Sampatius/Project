#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : loopTheMenu(true)
{
	menuOptions = { "Add task", "Save repairs", "Load repairs", "Perform fix", "Top 3", "Print all", "Clear records", "Exit" };
}


Menu::~Menu()
{
}

void Menu::moveUp(std::vector<std::string> *menu)
{
	position--;
	if (position == -1) {
		position = menu->size()-1;
	}
}

void Menu::moveDown(std::vector<std::string> *menu)
{
	position++;
	if (position == menu->size()) {
		position = 0;
	}
}

void Menu::printMenu(std::vector<std::string> &menu)
{
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	std::cout << "RepairNator\n" << std::endl;

	for (int i = 0; i < menu.size(); i++) {
		if (i == position) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			std::cout << std::left << std::setw(20) << menu[i] << std::endl;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << std::left << std::setw(20) << menu[i] << std::endl;
		}
	}
}

int Menu::readKey(std::vector<std::string> *menu)
{
	BOOL done = FALSE;
	DWORD        mode;
	INPUT_RECORD event;

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hstdin, &mode);

	SetConsoleMode(hstdin, 0);
	
	while (!done) {
		DWORD count;
		ReadConsoleInput(hstdin, &event, 1, &count);
		if ((event.EventType == KEY_EVENT) && !event.Event.KeyEvent.bKeyDown) {
			switch (event.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP:
				moveUp(menu);
				printMenu(*menu);
				break;
			case VK_DOWN:
				moveDown(menu);
				printMenu(*menu);
				break;
			case VK_RETURN:
				while (GetAsyncKeyState(VK_RETURN) & 0x8000 != 0);
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				return position;
			case VK_ESCAPE:
				break;
			default:
				done = TRUE;
			}
		}
	}
}

void Menu::menuLoop()
{
	printMenu(menuOptions);
	while (loopTheMenu) {
		handleEnter(readKey(&menuOptions));
		printMenu(menuOptions);
	}
}

void Menu::handleEnter(int position)
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
		repairsMenu();
		break;
	case 4:
		topThree();
		break;
	case 5:
		printAll();
		break;
	case 6:
		shop.clearRecords();
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

void Menu::performFix(int position)
{
	std::string solution;
	int timeSpent;
	if (shop.getRepair(position)->getStatus()) {
		std::cout << "The problem has been solved." << std::endl;
		system("pause");
	}
	else {

		system("cls");

		std::cout << "The problem: " << shop.getRepair(position)->getProblem() << std::endl;

		std::cout << "Enter solution to the problem: ";
		getline(std::cin, solution);
		std::cout << "Enter time spent in minutes (1-180): ";
		std::cin >> timeSpent;
		while (std::cin.fail() || timeSpent < 1 || timeSpent > 180) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a value between (1-180): ";
			std::cin >> timeSpent;
		}
		shop.performFix(position, solution, timeSpent);
	}
}

void Menu::repairsMenu()
{
	std::vector<std::string> repairsList;
	std::string status;
	for (int i = 0; i < shop.getSize(); i++) {
		if (shop.getRepair(i)->getStatus()) {
			status = "Completed";
		}
		else {
			status = "Pending";
		}
		repairsList.push_back(shop.getRepair(i)->getClient() + " " + shop.getRepair(i)->getProblem() + " " + status);
	}
	if (repairsList.size() == 0) {
		std::cout << std::endl;
		std::cout << "No repairs listed." << std::endl;
		system("pause");
	}
	else {
		position = 0;
		printMenu(repairsList);
		performFix(readKey(&repairsList));
	}
}

void Menu::topThree()
{
	system("cls");
	std::cout << "TOP 3 HARDEST CASES" << std::endl;
	std::cout << "Client name\tCompleted" << std::endl;
	std::cout << "=============================" << std::endl;
	for (int i = 0; i < 3; i++) {
		shop.topThree(i);
	}
	system("pause");
}

void Menu::printAll()
{
	system("cls");
	std::cout << std::left << std::setw(20) << "Client name" << std::setw(20) << "Completed" << std::endl;
	std::cout << "=============================" << std::endl;
	for (int i = 0; i < shop.getSize(); i++) {
		shop.printRepair(i);
	}
	system("pause");
}
