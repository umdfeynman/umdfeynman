#ifndef PMACS_MENU_H
#define PMACS_MENU_H

#include <string>
#include <vector>

void displayMainMenu();
void displayPOSMenu();
void displayStoreMenu();
void displayInventoryMenu();
void displaySalesMenu();
void displayBatchMenu();
void displayUtilityMenu();
void selectItem();
void displayUpdateInventoryMenu();
void displayTransactionMenu();

class Menu
{
public:
	void setMessage(std::string in_string);
	void setMenuName(std::string in_string);
	void setErrorMessage(std::string in_string);
	void displayHeader();
	void displayFooter();
	void displayMenuNoReturn(bool useOrderEntryMenu = false);
	char displayMenuGetSelection(bool useOrderEntryMenu = false);
	void displayDialogNoReturn(std::string in_string, int expected_type = -1);
	int displayDialogGetEntryInt(std::string in_string, int max_length = 10);
	char displayDialogGetEntryChar(std::string in_string);
	long long displayDialogGetEntryLongLong(std::string in_string, int max_length = 19);
	std::string displayDialogGetEntryString(std::string in_string, int max_length = 200);
	double Menu::displayDialogGetEntryDouble(std::string in_string, int max_length);
	void addMenuItem(char selectKey, std::string menuText);




private:
	void resetErrorMessage();
	bool findMenuItemKey(char in_key);
	std::string errorMessage = "Welcome to PMACS - Errors displayed down here";
	std::string menuName;
	int console_width = 80;
	std::vector<std::string> menuItemText;
	std::vector<char> menuItemKey;
};

#endif
