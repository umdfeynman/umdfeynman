#ifndef PMACS_MENU_H
#define PMACS_MENU_H

#include <string>

void displayMainMenu();
void displayPOSMenu();
void displayStoreMenu();
void displayInventoryMenu();
void displaySalesMenu();
void displayBatchMenu();

class Header
{
public:
	void displayHeader(std::string menuName);
	void setCustomerAccount(int account_num);
	void setStoreNumber(int store_num);
	void setCashierNumber(int cashier_num);

private:
	int account_number = -1;
	int store_number;
	int cashier_number;
};

#endif
