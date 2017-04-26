#include "PMACS_Menu.h"
#include "PMACS_Utility.h"
#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include <iostream>
#include <iomanip>

void displayMainMenu()
{
	
}

void displayPOSMenu()
{


	// Reset currentAccountNumber because we're leaving
	currentCustomerNumber = -1;
	currentCustomerIndex = -1;
}

void displayStoreMenu()
{

}

void displayInventoryMenu()
{

}

void displaySalesMenu()
{

}

void displayBatchMenu()
{

}

void Menu::displayHeader()
{
	system("clear");
	
	/*std::cout << "/=================================================================================\ ";
	
	std::string menuMarquee = "PMACS - " + menuName;
	int textPosition = (80 - menuMarquee.size()) / 2;

	std::cout << "|";
	for (int i = 0; i < textPosition; i++)
		std::cout << " ";
	
	std::cout << menuMarquee;

	for (int i = textPosition + menuMarquee.size(); i < 80; i++)
		std::cout << " ";
	
	std::cout << "|" << std::endl;

	std::cout << "\=================================================================================/ ";*/

	//  /====================================================\
	//	|                                                    |
	//  \====================================================/
			
	//Take 80 - string length + "PMACS - ", cut that in half, display at that place
	
	/*
	std::string menuName;
	int account_number = -1;
	int store_number = -1;
	int cashier_number = -1;
	int console_width = 80;
*/

	std::cout << "==";


	if (menuName == "")
		std::cout << "NO MENU NAME SET";
	else
		std::cout << menuName;

	std::cout << "==" << std::endl;

	std::cout << "Customer Number: ";
	if (currentCustomerNumber == -1)
		std::cout << "NOT SET";
	else
		std::cout << currentCustomerNumber;

	std::cout << std::endl;

	std::cout << "Customer Name: ";
	if (currentCustomerNumber == -1)
		std::cout << "NO CUSTOMER SET";
	else
		std::cout << customer_table[currentCustomerIndex].name;

	std::cout << std::endl;

	std::cout << "Customer Address: ";
	if (currentCustomerNumber == -1)
		std::cout << "NO CUSTOMER SET";
	else
		std::cout << customer_table[currentCustomerIndex].address;

	std::cout << std::endl;
}

void Menu::displayFooter()
{

}

void Menu::setMessage(std::string in_string)
{
	errorMessage = in_string;
}

void Menu::setMenuName(std::string in_string)
{
	menuName = in_string;
}

void Menu::addMenuItem(int selectNumber, std::string menuText)
{

}

void Menu::displayMenuNoReturn()
{

}

int Menu::displayMenuGetSelection()
{

	return -1;
}

void Menu::displayDialogNoReturn(std::string in_string)
{
	
}

int Menu::displayDialogGetEntryInt(std::string in_string)
{
	return -1;
}

long long Menu::displayDialogGetEntryLongLong(std::string in_string)
{
	return -1;
}

std::string Menu::displayDialogGetEntryString(std::string in_string)
{
	return "";
}

