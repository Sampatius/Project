#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : loopTheMenu(true)
{
	menuOptions = { "Add task", "Save repairs", "Load repairs", "Perform fix", "Top 3", "Print all", "Clear records", "Exit" };
}


Menu::~Menu()
{
}

//Move cursor up
void Menu::moveUp(std::vector<std::string> *menu)
{
	position--;
	if (position == -1) {
		position = menu->size()-1;
	}
}

//Move cursor down
void Menu::moveDown(std::vector<std::string> *menu)
{
	position++;
	if (position == menu->size()) {
		position = 0;
	}
}

//Print the menu we currently have active and highligh the current position of cursor
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

//Handle arrow key inputs and Enter
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

//Main menu loop
void Menu::menuLoop()
{
	printMenu(menuOptions);
	while (loopTheMenu) {
		handleEnter(readKey(&menuOptions));
		printMenu(menuOptions);
	}
}

//Main menu's switch case for selecting options
void Menu::handleEnter(int position)
{
	switch (position) {
	case 0:
		addTask();
		break;
	case 1:
		saveRepairsToFile();
		break;
	case 2:
		loadRepairsFromFile();
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

//Add new repair task
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

//Perform fix to selected repair task, if selected repair is already completed inform user
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

//Create vector of current repairs with necessary informations and print is as a new menu to select from
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

//Print top three repairs that have taken the longest to solve
void Menu::topThree()
{
	system("cls");
	std::cout << "TOP 3 HARDEST CASES" << std::endl;
	std::cout << "Client name\tTime spent \tCompleted" << std::endl;
	std::cout << "=========================================" << std::endl;
	if (shop.getSize() < 3) {
		for (int i = 0; i < shop.getSize(); i++) {
			shop.topThree(i);
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			shop.topThree(i);
		}
	}
	system("pause");
}

//Print all repairs
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

void Menu::saveRepairsToFile()
{
	std::ofstream fl;
	for (int i = 0; i < shop.getSize(); i++) {
		fl << shop;
	}
}

void Menu::loadRepairsFromFile()
{
	shop.clearRecords();
	std::ifstream fl;
	fl >> shop;
}