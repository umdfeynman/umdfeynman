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

class Menu
{
public:
	void setMessage(std::string in_string);
	void setMenuName(std::string in_string);
	void displayHeader();
	void displayFooter();
	void displayMenuNoReturn();
	int displayMenuGetSelection();
	void displayDialogNoReturn(std::string in_string);	
	int displayDialogGetEntryInt(std::string in_string);
	long long displayDialogGetEntryLongLong(std::string in_string);
	std::string displayDialogGetEntryString(std::string in_string);
	void addMenuItem(int selectNumber, std::string menuText);
private:
	std::string errorMessage = "NO ERROR";
	std::string menuName;	
	int console_width = 80;
};

#endif
