#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include "PMACS_Defines.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include "PMACS_File.h"
#include "PMACS_Batch.h"
#include "PMACS_Input.h"
#include "PMACS_String.h"
#include "PMACS_Menu.h"
#include "PMACS_Sales_Reports.h"
#include "PMACS_Utility.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <Windows.h>


bool RunOnlineSalesReport();

bool reportItemByDay(int itemNumber, int period);
bool reportItemByWeek(int itemNumber, int period);
bool reportItemByMonth(int itemNumber, int period);
bool reportItemByYear(int itemNumber, int period);
/////
bool reportStoreByWeek(int itemNumber, int period);
bool reportStoreByDay(int itemNumber, int period);
bool reportStoreByMonth(int itemNumber, int period);
bool reportStoreByYear(int itemNumber, int period);
int periodCheck(char period);



bool RunOnlineSalesReport()

{
	Menu temp;
	temp.setMenuName("Sales Reports");
	temp.addMenuItem('1', "Report on Store");
	temp.addMenuItem('2', "Report on Item");

	char selection = 0; // 0 as in NULL not '0' as in ascii zero

	while (selection != '0')
	{
		selection = temp.displayMenuGetSelection();

		switch (selection)
		{
		case '1':
		{
			int store = RunReportByStoreCheck();
			if (store != -1)
			{
				RunReportByStore(store_data_table[store].store_number);
			}
			else
			{
				temp.displayDialogNoReturn("Store does not exist.");
			}
			break;
		}
		case '2':
		{
			int item = RunReportByItemCheck();
			if (item != -1)
			{
				RunReportByItem(warehouse_table[item].item_number);
			}
			else
			{
				temp.displayDialogNoReturn("Item does not exist.");
			}
			break;
		}
		case '0':
		{
			return 0;
		}
		default:
		{
			break;
		}
		}
	}
}

bool RunReportByStore(int storeNum)
{
	Menu temp;
	temp.setMenuName("Sales Reports by Store");
	temp.addMenuItem('1', "Report by day");
	temp.addMenuItem('2', "Report by week");
	temp.addMenuItem('3', "Report by month");
	temp.addMenuItem('4', "Report by year");

	char selection = 0; // 0 as in NULL not '0' as in ascii zero

	while (selection != '0')
	{
		selection = temp.displayMenuGetSelection();

		int period = periodCheck(selection);
		if (period != -1)							//if time period is accepted
		{			
			switch (selection)
			{
			case '1':
			{
				temp.displayDialogNoReturn("Creating store item report.");
				if (reportStoreByDay(storeNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '2':
			{
				temp.displayDialogNoReturn("Creating store item report.");
				if (reportStoreByWeek(storeNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '3':
			{
				temp.displayDialogNoReturn("Creating store item report.");
				if (reportStoreByMonth(storeNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '4':
			{
				temp.displayDialogNoReturn("Creating store item report.");
				if (reportStoreByYear(storeNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '0':
			{
				return 0;
			}
			default:
			{
				break ;
			}
			}
		}		
	}
}


bool RunReportByItem(int itemNum)
{


	char selection = 0; // 0 as in NULL not '0' as in ascii zero

	while (selection != '0')
	{
		Menu temp;
		temp.setMenuName("Sales Reports by item");
		temp.addMenuItem('1', "Report by day");
		temp.addMenuItem('2', "Report by week");
		temp.addMenuItem('3', "Report by month");
		temp.addMenuItem('4', "Report by year");

		selection = temp.displayMenuGetSelection();

		int period = periodCheck(selection);
		if (period != -1)							//if time period is accepted
		{
			switch (selection)
			{
			case '1':
			{
				temp.displayDialogNoReturn("Creating item report.");
				if (reportItemByDay(itemNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '2':
			{
				temp.displayDialogNoReturn("Creating item report.");
				if (reportItemByWeek(itemNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '3':
			{
				temp.displayDialogNoReturn("Creating item report.");
				if (reportItemByMonth(itemNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case '4':
			{
				temp.displayDialogNoReturn("Creating item report.");
				if (reportItemByYear(itemNum, period))
				{
					temp.displayDialogNoReturn("Report created.");
				}
				else
				{
					temp.displayDialogNoReturn("No transaction data recorded for this period.");
				}
				selection = '0';
				break;
			}
			case 'q':
			{
				return 0;
			}
			default:
			{
				break;
			}
			}
		}
	}
}



int RunReportByStoreCheck()
{
	Menu temp;
	temp.setMenuName("Sales Reports");
	int storeNumber = temp.displayDialogGetEntryInt("Enter the store number for report creation.", 5);
	int index = findStore(storeNumber);
	return index;
}

int RunReportByItemCheck()
{
	Menu temp;
	temp.setMenuName("Sales Reports");
	int itemNumber = temp.displayDialogGetEntryInt("Enter the item number for report creation.", 9);
	int index = findWarehouseItem(itemNumber);
	return index;
}

int periodCheck(char selection)
{
	Menu temp;
	temp.setMenuName("Sales Reports");
	int period = temp.displayDialogGetEntryInt("Enter the time period for the report.", 5);

	switch (selection)
	{
	case '1'://day
	{
		if (period < 1 || period > 30)
		{
			temp.displayDialogNoReturn("Time period not accepted");
			return -1;
		}
		break;
	}
	case '2'://week
	{
		if (period < 1 || period > 52)
		{
			temp.displayDialogNoReturn("Time period not accepted");
			return -1;
		}
		break;
	}
	case '3'://month
	{
		if (period < 1 || period > 12 )
		{
			temp.displayDialogNoReturn("Time period not accepted");
			return -1;
		}
		break;
	}
	default:
	{
		return 0;
	}
	}
	return period;
}



































//Each store's totals for the item
bool reportItemByWeek(int itemNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbyitem.txt", ios::out);

	bool reported = false;

	//header type deal
	int wIndex = findWarehouseItem(itemNumber);
	report << "SALES REPORT ON ITEM " << itemNumber << " - " << trimTrailingLeadingSpaces(warehouse_table[wIndex].item_name) << " FOR WEEK ";
	if (period == systemDate.GetWeekNumber()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}	
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(10) << " " << setw(15) << left << "STORE NUMBER" << setw(15) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	vector<int> storeList = getStoreItemList(itemNumber);
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < storeList.size(); x++)							//for each store that had/has the item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)			//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetYear() == systemDate.GetYear())						//if within the year
			{
				if (transDate.GetWeekNumber() == period &&
					currentStoreNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(itemNumber, x);						//get dollars for item
					quantityTotal += getItemQuantity(itemNumber, x);				//get quantity for item
					reported = true;
				}
			}
		}

 		if (reported)				//output report
		{
			report << setw(10) << " " << setw(17) << currentStoreNumber << setw(15) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}

bool reportItemByDay(int itemNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbyitem.txt", ios::out);

	bool reported = false;

	//header type deal
	int wIndex = findWarehouseItem(itemNumber);
	report << "SALES REPORT ON ITEM " << itemNumber << " - " << trimTrailingLeadingSpaces(warehouse_table[wIndex].item_name) << " FOR ";
	if (period == systemDate.GetDay()) //to date
	{
		report << "TODAY ";
	}
	else		//specified period
	{
		report << "DAY " << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(10) << " " << setw(15) << left << "STORE NUMBER" << setw(15) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	vector<int> storeList = getStoreItemList(itemNumber);
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < storeList.size(); x++)							//for each store that had/has the item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)			//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetMonth() == systemDate.GetMonth())						//if within the month
			{
				if (transDate.GetDay() == period &&
					currentStoreNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(itemNumber, x);						//get dollars for item
					quantityTotal += getItemQuantity(itemNumber, x);				//get quantity for item
					reported = true;
				}
			}
		}

 		if (reported)				//output report
		{
			report << setw(10) << " " << setw(17) << currentStoreNumber << setw(15) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}

bool reportItemByMonth(int itemNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbyitem.txt", ios::out);

	bool reported = false;

	//header type deal
	int wIndex = findWarehouseItem(itemNumber);
	report << "SALES REPORT ON ITEM " << itemNumber << " - " << trimTrailingLeadingSpaces(warehouse_table[wIndex].item_name) << " FOR MONTH ";
	if (period == systemDate.GetWeekNumber()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(10) << " " << setw(15) << left << "STORE NUMBER" << setw(15) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	vector<int> storeList = getStoreItemList(itemNumber);
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < storeList.size(); x++)							//for each store that had/has the item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)			//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetYear() == systemDate.GetYear())						//if within the year
			{
				if (transDate.GetMonth() == period &&
					currentStoreNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(itemNumber, x);						//get dollars for item
					quantityTotal += getItemQuantity(itemNumber, x);				//get quantity for item
					reported = true;
				}
			}

		}

 		if (reported)				//output report
		{
			report << setw(10) << " " << setw(17) << currentStoreNumber << setw(15) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}

bool reportItemByYear(int itemNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbyitem.txt", ios::out);

	bool reported = false;

	//header type deal
	int wIndex = findWarehouseItem(itemNumber);
	report << "SALES REPORT ON ITEM " << itemNumber << " - " << trimTrailingLeadingSpaces(warehouse_table[wIndex].item_name) << " FOR YEAR ";
	if (period == systemDate.GetYear()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(10) << " " << setw(15) << left << "STORE NUMBER" << setw(15) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	vector<int> storeList = getStoreItemList(itemNumber);
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < storeList.size(); x++)							//for each store that had/has the item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)			//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);
			if (transDate.GetYear() == period &&
				currentStoreNumber == transaction_table[x].store_number)		//if date and store match
			{
				priceTotal += getItemCost(itemNumber, x);						//get dollars for item
				quantityTotal += getItemQuantity(itemNumber, x);				//get quantity for item
				reported = true;
			}
		}

		if (reported)				//output report
		{
			report << setw(10) << " " << setw(17) << currentStoreNumber << setw(15) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}

	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}

	return reported;
}


//all items in the store
bool reportStoreByWeek(int storeNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbystore.txt", ios::out);

	bool reported = false;

	//header type deal
	report << "SALES REPORT ON STORE " << currentStoreNumber << " FOR WEEK ";
	if (period == systemDate.GetWeekNumber()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(5) << " " << setw(15) << left << "ITEM NUMBER" << setw(25) << left << "| ITEM NAME" << setw(20) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < store_inventory_table.size(); x++)							//for each storeinventory item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)						//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetYear() == systemDate.GetYear())						//if within the year
			{
				if (transDate.GetWeekNumber() == period &&
					storeNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(store_inventory_table[x].item_number, x);						//get dollars for item
					quantityTotal += getItemQuantity(store_inventory_table[x].item_number, x);				//get quantity for item
					reported = true;
				}
			}
		}

		int wIndex = findWarehouseItem(store_inventory_table[x].item_number);
		if (reported)				//output report
		{
			//"		item number
			report << setw(5) << left << " "
				<< setw(17) << left << store_inventory_table[x].item_number << setw(25) << left << warehouse_table[wIndex].item_name
				<< setw(20) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}

bool reportStoreByDay(int storeNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbystore.txt", ios::out);

	bool reported = false;

	//header type deal
	report << "SALES REPORT ON STORE " << currentStoreNumber << " FOR DAY ";
	if (period == systemDate.GetDay()) //to date
	{
		report << "TODAY ";
	}
	else		//specified period
	{
		report << "DAY " << period;
		report << endl << "Report Date: " << systemDate.GetDate();
		report << endl << setw(5) << " " << setw(15) << left << "ITEM NUMBER" << setw(25) << left << "| ITEM NAME" << setw(20) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;
	}
	//get store item list
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < store_inventory_table.size(); x++)							//for each storeinventory item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)						//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetMonth() == systemDate.GetYear())						//if within the year
			{
				if (transDate.GetDay() == period &&
					storeNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(store_inventory_table[x].item_number, x);						//get dollars for item
					quantityTotal += getItemQuantity(store_inventory_table[x].item_number, x);				//get quantity for item
					reported = true;
				}
			}
		}

		int wIndex = findWarehouseItem(store_inventory_table[x].item_number);
		if (reported)				//output report
		{
			//"		item number
			report << setw(5) << left << " "
				<< setw(17) << left << store_inventory_table[x].item_number << setw(25) << left << warehouse_table[wIndex].item_name
				<< setw(20) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}

	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;

}

bool reportStoreByMonth(int storeNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbystore.txt", ios::out);

	bool reported = false;

	//header type deal
	report << "SALES REPORT ON STORE " << currentStoreNumber << " FOR MONTH ";
	if (period == systemDate.GetWeekNumber()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(5) << " " << setw(15) << left << "ITEM NUMBER" << setw(25) << left << "| ITEM NAME" << setw(20) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < store_inventory_table.size(); x++)							//for each storeinventory item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)						//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);

			if (transDate.GetYear() == systemDate.GetYear())						//if within the year
			{
				if (transDate.GetMonth() == period &&
					storeNumber == transaction_table[x].store_number)		//if date and store match
				{
					priceTotal += getItemCost(store_inventory_table[x].item_number, x);						//get dollars for item
					quantityTotal += getItemQuantity(store_inventory_table[x].item_number, x);				//get quantity for item
					reported = true;
				}
			}
		}

		int wIndex = findWarehouseItem(store_inventory_table[x].item_number);
		if (reported)				//output report
		{
			//"		item number
			report << setw(5) << left << " "
				<< setw(17) << left << store_inventory_table[x].item_number << setw(25) << left << warehouse_table[wIndex].item_name
				<< setw(20) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}

bool reportStoreByYear(int storeNumber, int period)
{
	//output report
	ofstream report;
	report.open("salesreportbystore.txt", ios::out);

	bool reported = false;

	//header type deal
	report << "SALES REPORT ON STORE " << currentStoreNumber << " FOR YEAR ";
	if (period == systemDate.GetWeekNumber()) //to date
	{
		report << "TO DATE";
	}
	else			//specified period
	{
		report << period;
	}
	report << endl << "Report Date: " << systemDate.GetDate();
	report << endl << setw(5) << " " << setw(15) << left << "ITEM NUMBER" << setw(25) << left << "| ITEM NAME" << setw(20) << left << "| QUANTITY TOTAL " << "| DOLLAR TOTAL" << endl;

	//get store item list
	long double priceTotal = 0.0;
	unsigned long long quantityTotal = 0;

	for (int x = 0; x < store_inventory_table.size(); x++)							//for each storeinventory item
	{
		quantityTotal = 0;
		priceTotal = 0.0;
		long double priceTotal = 0;
		unsigned long long quantityTotal = 0;
		for (int x = transaction_table.size() - 1; x >= 0; x--)						//for each transaction in reverse
		{
			//get transaction date
			Date transDate(transaction_table[x].transaction_date);


			if (transDate.GetYear() == period &&
				storeNumber == transaction_table[x].store_number)										//if year and store match
			{
				priceTotal += getItemCost(store_inventory_table[x].item_number, x);						//get dollars for item
				quantityTotal += getItemQuantity(store_inventory_table[x].item_number, x);				//get quantity for item
				reported = true;
			}
		}

		int wIndex = findWarehouseItem(store_inventory_table[x].item_number);
		if (reported)				//output report
		{
			//"		item number
			report << setw(5) << left << " "
				<< setw(17) << left << store_inventory_table[x].item_number << setw(25) << left << warehouse_table[wIndex].item_name
				<< setw(20) << left << quantityTotal << "$" << setprecision(2) << priceTotal << endl;
		}
	}
	if (!reported)
	{
		report << "No transaction data for this period.";
		return -1;	//no transaction data
	}
	return reported;
}


//add totals
unsigned long long getItemQuantity(int itemNumber, int transaction)
{
	long long amount = 0;
	for (int y = 0; y < transaction_table[transaction].transaction_item_number.size(); y++)		//for each item in the transaction
	{
		if (transaction_table[transaction].transaction_item_number[y] == itemNumber)				//if correct item
		{
			amount += transaction_table[transaction].transaction_item_quantity[y];
		}
	}
	return amount;
}

long double getItemCost(int itemNumber, int transaction)
{
	long long amount = 0;
	for (int y = 0; y < transaction_table[transaction].transaction_item_number.size(); y++)		//for each item in the transaction
	{
		if (transaction_table[transaction].transaction_item_number[y] == itemNumber)				//if correct item
		{
			amount += transaction_table[transaction].transaction_item_price[y];
			amount *= transaction_table[transaction].transaction_item_quantity[y];
		}
	}
	return amount;
}




