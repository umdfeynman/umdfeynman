#include <fstream>
#include <string>
#include <vector>
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_Input.h"
#include "PMACS_String.h"

bool loadDatabaseIntoMemory()
{
	Plog.setContext("loadDatabaseIntoMemory");	
	bool lastResult = readTransaction();
	if (!lastResult)
	{
		Plog.logError("Unable to load transaction database.  Bailing.");
		return false;
	}

	Plog.setContext("loadDatabaseIntoMemory");
	lastResult = readCustomer();
	if (!lastResult)
	{
		Plog.logError("Unable to load customer database.  Bailing.");
		return false;
	}
		
	return true;
}

bool readTransaction()
{
	int lineNumber = 0;
	
	Plog.setContext("readTransaction");
    std::ifstream transactionFile;
    transactionFile.open(g_transaction_file);
    
    if (!transactionFile || !transactionFile.good())
    {
        Plog.logError("Failed to read database file.  Bailing.");
        return false;
    }
    
    std::string readLine;
    std::getline(transactionFile, readLine);
	lineNumber++;
    
    if (readLine.substr(0, 6) != "HTRANS")
    {
		Plog.logError("Failed to find header in file.  Bailing.");
        return false;
    }
    
    if (transactionFile.eof())
    {
		Plog.logWarn("Empty database file.  Continuing.");
        return true;
    }
    
	while (!transactionFile.eof() || !transactionFile)
	{

		std::string s_orderNumber;
		std::string s_originatingCashierNumber;
		std::string s_approvingCashierNumber;
		std::string s_storeNumber;
		std::string s_transactionDate;
		std::string s_accountNumber;
		std::string s_discountPct;
		std::string s_grandTotal;

		std::getline(transactionFile, readLine);
		lineNumber++;
		s_orderNumber = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_originatingCashierNumber = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_approvingCashierNumber = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_storeNumber = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_transactionDate = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_accountNumber = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_discountPct = readLine;
		std::getline(transactionFile, readLine);
		lineNumber++;
		s_grandTotal = readLine;

		std::getline(transactionFile, readLine);
		lineNumber++;
		if (readLine[0] != 'S')
		{
			Plog.logError("Expected S record.  Bailing.  Line number:" + lineNumber);
			return false;
		}

		std::vector<std::string> s_transactionItemNumber;

		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);
			lineNumber++;
			if (readLine[0] != 'E')
				s_transactionItemNumber.push_back(readLine);
		}

		std::getline(transactionFile, readLine);
		lineNumber++;
		if (readLine[0] != 'S')
		{
			Plog.logError("Expected S record.  Bailing.  Line number:" + lineNumber);
			return false;
		}

		std::vector<std::string> s_transactionItemQuantity;
		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);
			lineNumber++;
			if (readLine[0] != 'E')
				s_transactionItemQuantity.push_back(readLine);
		}

		std::getline(transactionFile, readLine);
		lineNumber++;
		if (readLine[0] != 'S')
		{
			Plog.logError("Expected S record.  Bailing.  Line number: " + lineNumber);
			return false;
		}

		std::vector<std::string> s_transactionItemPrice;
		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);
			lineNumber++;
			if (readLine[0] != 'E')
				s_transactionItemPrice.push_back(readLine);
		}

		Transaction inTransaction;
		
		inTransaction.order_number = StringToInt(s_orderNumber);
		inTransaction.originating_cashier_number = StringToInt(s_originatingCashierNumber);
		inTransaction.approving_cashier_number= StringToInt(s_approvingCashierNumber);
		inTransaction.store_number = StringToInt(s_storeNumber);
		inTransaction.transaction_date = s_transactionDate;
		inTransaction.account_number = StringToInt(s_accountNumber);
		inTransaction.discount_pct= StringToInt(s_discountPct);
		inTransaction.grand_total= StringToDouble(s_grandTotal);

	
		for (int i = 0; i < s_transactionItemNumber.size(); i++)
		{			
			inTransaction.transaction_item_number.push_back(StringToInt(s_transactionItemNumber[i]));
		}

		for (int i = 0; i < s_transactionItemQuantity.size(); i++)
		{
			inTransaction.transaction_item_quantity.push_back(StringToLongLong(s_transactionItemQuantity[i]));
		}
	
		for (int i = 0; i < s_transactionItemPrice.size(); i++)
		{
			inTransaction.transaction_item_price.push_back(StringToDouble(s_transactionItemPrice[i]));
		}

		transaction_table.push_back(inTransaction);
		
		std::getline(transactionFile, readLine); // Read past separator

	}
        
    transactionFile.close();
	return true;

	/*
	class Transaction
	{
	public:
	int order_number = -1;  // Key 1
	int originating_cashier_number = -1;
	int approving_cashier_number = -1;
	int store_number = -1;
	std::string transaction_date = "";
	int account_number = -1;
	int discount_pct = -1;  // Discount percent from coupon
	double grand_total = -1.0;  // Transaction total after all discounts applied, for easy generation of grand totals in reporting
	std::vector<int> transaction_item;
	std::vector<long long> transaction_item_quantity;
	std::vector<double> transaction_item_price;  // Item price after individual item discount
	};*/

	//HTRANS
	//-1
	//-1
	//-1
	//-1
	//
	//-1
	//-1
	//-1.0
	//S
	//
	//
	//
	//
	//E
	//S
	//
	//
	//
	//
	//E
	//S - START ARRAY
	// - FIELD
	// - FIELD
	// - FIELD
	//E - END ARRAY
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ (\ * 40)
	//Z - END OF FILE
}

bool readCustomer()
{
	Plog.setContext("readCustomer");
	std::ifstream customerFile;
	customerFile.open(g_customer_file);

	if (!customerFile || !customerFile.good())
	{
		Plog.logError("Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(customerFile, readLine);

	if (readLine.substr(0, 6) != "HCUST")
	{
		Plog.logError("Failed to find header in file.  Bailing.");
		return false;
	}

	if (customerFile.eof())
	{
		Plog.logWarn("Empty database file.  Continuing.");
		return true;
	}

	while (!customerFile.eof() || !customerFile)
	{

		std::string s_accountNumber;
		std::string s_address;
		std::string s_name;
		
		std::getline(customerFile, readLine);
		s_accountNumber = readLine;
		std::getline(customerFile, readLine);
		s_address = readLine;
		std::getline(customerFile, readLine);
		s_name = readLine;		

		std::getline(customerFile, readLine);
		if (readLine[0] != 'S')
		{
			Plog.logError("Expected S record.  Bailing.");
			return false;
		}

		std::vector<std::string> s_customerItemNumber;

		while (readLine[0] != 'E')
		{
			std::getline(customerFile, readLine);
			if (readLine[0] != 'E')
				s_customerItemNumber.push_back(readLine);
		}

		std::getline(customerFile, readLine);
		if (readLine[0] != 'S')
		{
			Plog.logError("Expected S record.  Bailing.");
			return false;
		}

		std::vector<std::string> s_customerItemDate;
		while (readLine[0] != 'E')
		{
			std::getline(customerFile, readLine);
			if (readLine[0] != 'E')
				s_customerItemDate.push_back(readLine);
		}
		
		Customer inCustomer;

		inCustomer.account_number  = StringToInt(s_accountNumber);
		inCustomer.address = s_address;
		inCustomer.name = s_name;

		for (int i = 0; i < s_customerItemNumber.size(); i++)
		{
			inCustomer.cust_items.push_back(StringToInt(s_customerItemNumber[i]));
		}

		for (int i = 0; i < s_customerItemDate.size(); i++)
		{
			inCustomer.item_dates.push_back(StringToInt(s_customerItemDate[i]));
		}

		customer_table.push_back(inCustomer);

		std::getline(customerFile, readLine); // Read past separator

	}

	customerFile.close();
	return true;

	/*
	class Customer
	{
	public:
		int account_number = -1;
		std::string address = "";
		std::string name = "";   
		std::vector<int> cust_items;  // Same index as item_dates
		std::vector<std::string> item_dates; // Same index as cust_items	
	};
	
	
	*/


}

// Note:  Skipping record length check due to file structure, assuming files are immaculate
// Record checks
    // Check record length
    // Header check
    
    
// For each line
    // Create an instance of of a single table item
    // Using defines, store each field in its own string
    // Convert string to proper type for table and store in instance
    // Push instance to empty table






