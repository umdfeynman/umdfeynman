#include "PMACS_Menu.h"
#include "PMACS_Utility.h"
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include "PMACS_String.h"
#include "PMACS_Input.h"
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
	system("cls");

	std::cout << "==";


	if (menuName == "")
		std::cout << "NO MENU NAME SET";
	else
		std::cout << menuName;

	std::cout << "==" << std::endl;

	std::cout << "Store Number: ";
	if (currentStoreNumber == -1)
		std::cout << "NO STORE SET";
	else
		std::cout << currentStoreNumber;
	
	std::cout << std::endl;

	std::cout << "Cashier Number: ";
	if (currentCashierNumber == -1)
		std::cout << "NO STORE SET";
	else
		std::cout << currentCashierNumber;

	std::cout << std::endl;

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

	std::cout << std::endl << std::endl;
	
}

void Menu::displayFooter()
{
	std::cout << std::endl << std::endl;

	std::cout << "==";

	std::cout << errorMessage;

	std::cout << "==" << std::endl;
}

void Menu::setMessage(std::string in_string)
{
	errorMessage = in_string;
}

void Menu::setMenuName(std::string in_string)
{
	menuName = in_string;
}

void Menu::setErrorMessage(std::string in_string)
{
	errorMessage = in_string;
}

void Menu::addMenuItem(char selectKey, std::string menuText)
{
	menuItemKey.push_back(selectKey);
	menuItemText.push_back(menuText);
}

void Menu::resetErrorMessage()
{
	errorMessage = "Welcome to PMACS - Errors displayed down here";
}

void Menu::displayMenuNoReturn()
{
	displayHeader();
	
	std::cout << "== Please select from one of the following options: == \n";
	
	for (int i = 0; i < menuItemKey.size(); i++)
	{
		std::cout << "[" << menuItemKey[i] << "]   " << menuItemText[i] << std::endl;
	}

	displayFooter();
}

char Menu::displayMenuGetSelection()
{
	displayMenuNoReturn();

	bool validateResult = false;
	bool foundKey = false;

	std::string getInput;

	while (!validateResult || !foundKey)
	{
		
		std::getline(cin, getInput);
		validateResult = validateInput(getInput, g_type_char_any, 1, 1);
		foundKey = findMenuItemKey(getInput[0]);
		if (!validateResult || !foundKey)
		{
			setErrorMessage("Error:  You did not enter a valid option.  Please try again.");
			displayMenuNoReturn();
		}		

	}
	
	resetErrorMessage();
	return getInput[0];
}

void Menu::displayDialogNoReturn(std::string in_string, int expected_type)
{
	displayHeader();

	std::cout << " ============== Message ============== \n";
	std::cout << in_string << std::endl;
	if (expected_type == -1)
		std::cout << " ============ Press Enter ============ \n";
	else
		std::cout << " ===================================== \n";
	
	displayFooter();

	std::string dummy;
	if (expected_type == -1)
		std::getline(cin, dummy);
}

int Menu::displayDialogGetEntryInt(std::string in_string)
{
	displayDialogNoReturn(in_string, g_type_int);

	bool validateResult = false;
	
	std::string getInput;

	while (!validateResult)
	{
		std::getline(cin, getInput);
		validateResult = validateInput(getInput, g_type_int, 10, 0);
		if (!validateResult)
		{
			setErrorMessage("Error:  Your input could not be validated.  Please try again.");
			displayDialogNoReturn(in_string, g_type_int);
		}
	}	

	resetErrorMessage();
	return StringToInt(getInput);
}

long long Menu::displayDialogGetEntryLongLong(std::string in_string)
{
	displayDialogNoReturn(in_string, g_type_longlong);

	bool validateResult = false;

	std::string getInput;

	while (!validateResult)
	{
		std::getline(cin, getInput);
		validateResult = validateInput(getInput, g_type_longlong, 19, 0);
		if (!validateResult)
		{
			setErrorMessage("Error:  Your input could not be validated.  Please try again.");
			displayDialogNoReturn(in_string, g_type_longlong);
		}
	}

	resetErrorMessage();
	return StringToLongLong(getInput);
}

std::string Menu::displayDialogGetEntryString(std::string in_string)
{
	displayDialogNoReturn(in_string, g_type_string_any);

	bool validateResult = false;

	std::string getInput;

	while (!validateResult)
	{
		std::getline(cin, getInput);
		validateResult = validateInput(getInput, g_type_string_any, 200, 0);
		if (!validateResult)
		{
			setErrorMessage("Error:  Your input could not be validated.  Please try again.");
			displayDialogNoReturn(in_string, g_type_string_any);
		}
	}

	resetErrorMessage();
	return getInput;
}

char Menu::displayDialogGetEntryChar(std::string in_string)
{
	displayDialogNoReturn(in_string, g_type_char_any);

	bool validateResult = false;

	std::string getInput;

	while (!validateResult)
	{
		std::getline(cin, getInput);
		validateResult = validateInput(getInput, g_type_char_any, 1, 0);
		if (!validateResult)
		{
			setErrorMessage("Error:  Your input could not be validated.  Please try again.");
			displayDialogNoReturn(in_string, g_type_char_any);
		}
	}

	resetErrorMessage();
	return getInput[0];
}

bool Menu::findMenuItemKey(char in_key)
{
	for (int i = 0; i < menuItemKey.size(); i++)
	{
		if (menuItemKey[i] == in_key)
			return true;
	}

	return false;
}
