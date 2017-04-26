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
	std::vector<std::string> menuItems;
	void displayMenu();
	void setCustomerAccount(int account_num);
	void setStoreNumber(int store_num);
	void setCashierNumber(int cashier_num);
	void setMessage(std::string in_string);
	void setMenuName(std::string in_string);
private:
	void displayHeader();
	void displayFooter();
	std::string errorMessage;
	std::string menuName;
	int account_number = -1;
	int store_number;
	int cashier_number;
	int console_width = 80;
};

#endif
