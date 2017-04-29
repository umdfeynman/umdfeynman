#include <fstream>
#include <string>
#include <vector>
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_Input.h"
#include "PMACS_String.h"
#include "PMACS_Date.h"

bool readSequenceNumbers()
{
	std::ifstream sequenceFile;
	sequenceFile.open(g_sequence_file);

	if (!sequenceFile || !sequenceFile.good())
	{
		Plog.logError("readSequence", "Failed to read sequence file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(sequenceFile, readLine);

	if (readLine.substr(0, 9) != "HSEQUENCE")
	{
		Plog.logError("readSequence", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (sequenceFile.eof())
	{
		Plog.logWarn("readSequence", "Empty database file.  Continuing.");
		return true;
	}

	int i = 0;
	while (i < 12 &&(!sequenceFile.eof() || !sequenceFile))
	{
		std::getline(sequenceFile, readLine);
		sequenceNumber[i] = StringToInt(readLine);
		++i;
	}

	sequenceFile.close();
	return true;
}

bool loadDatabaseIntoMemory()
{

	bool lastResult = readTransaction();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load transaction database.  Bailing.");
		return false;
	}

	lastResult = readCustomer();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load customer database.  Bailing.");
		return false;
	}

	lastResult = readWarehouseItemData();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load warehouse database.  Bailing.");
		return false;
	}

	lastResult = readStoreInventory();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load store inventory database.  Bailing.");
		return false;
	}

	lastResult = readStoreData();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load store data database.  Bailing.");
		return false;
	}

	lastResult = readCoupon();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load coupon database.  Bailing.");
		return false;
	}

	lastResult = readConfig();
	if (!lastResult)
	{
		Plog.logError("loadDatabaseIntoMemory", "Unable to load config database.  Bailing.");
		return false;
	}

	return true;
}

bool saveDatabaseToDisk()
{

	bool lastResult = saveTransaction();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save transaction database.  Bailing.");
		return false;
	}

	lastResult = saveCustomer();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save customer database.  Bailing.");
		return false;
	}

	lastResult = saveWarehouseItemData();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save warehouse database.  Bailing.");
		return false;
	}

	lastResult = saveStoreInventory();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save store inventory database.  Bailing.");
		return false;
	}

	lastResult = saveStoreData();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save store data database.  Bailing.");
		return false;
	}

	lastResult = saveCoupon();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save coupon database.  Bailing.");
		return false;
	}

	lastResult = saveConfig();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save config database.  Bailing.");
		return false;
	}

	lastResult = saveSequenceNumbers();
	if (!lastResult)
	{
		Plog.logError("saveDatabaseToDisk", "Unable to save sequence number database.  Bailing.");
		return false;
	}

	return true;
}

bool readConfig()
{
	std::ifstream configFile;
	configFile.open(g_config_file);

	if (!configFile || !configFile.good())
	{
		Plog.logError("readConfig", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(configFile, readLine);

	if (readLine.substr(0, 7) != "HCONFIG")
	{
		Plog.logError("readConfig", "Failed to find header in file.  Bailing.");
		return false;
	}

	std::cout << configFile.tellg() << std::endl;

	if (configFile.eof())
	{
		Plog.logWarn("readConfig", "Empty database file.  Continuing.");
		return true;
	}

	std::string s_systemDate;

	std::getline(configFile, s_systemDate);
	systemDate.NewDate(s_systemDate);

	configFile.close();
	return true;
}

bool readTransaction()
{
	std::ifstream transactionFile;
	transactionFile.open(g_transaction_file);

	if (!transactionFile || !transactionFile.good())
	{
		Plog.logError("readTransaction", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(transactionFile, readLine);


	if (readLine.substr(0, 6) != "HTRANS")
	{
		Plog.logError("readTransaction", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (transactionFile.eof())
	{
		Plog.logWarn("readTransaction", "Empty database file.  Continuing.");
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
		s_orderNumber = readLine;
		std::getline(transactionFile, readLine);
		s_originatingCashierNumber = readLine;
		std::getline(transactionFile, readLine);
		s_approvingCashierNumber = readLine;
		std::getline(transactionFile, readLine);
		s_storeNumber = readLine;
		std::getline(transactionFile, readLine);
		s_transactionDate = readLine;
		std::getline(transactionFile, readLine);
		s_accountNumber = readLine;
		std::getline(transactionFile, readLine);
		s_discountPct = readLine;
		std::getline(transactionFile, readLine);
		s_grandTotal = readLine;

		std::getline(transactionFile, readLine);

		if (readLine[0] != 'S')
		{
			Plog.logError("readTransaction", "Expected S record.  Bailing.  Line number:");
			return false;
		}

		std::vector<std::string> s_transactionItemNumber;

		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);

			if (readLine[0] != 'E')
				s_transactionItemNumber.push_back(readLine);
		}

		std::getline(transactionFile, readLine);

		if (readLine[0] != 'S')
		{
			Plog.logError("readTransaction", "Expected S record.  Bailing.  Line number:");
			return false;
		}

		std::vector<std::string> s_transactionItemQuantity;
		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);

			if (readLine[0] != 'E')
				s_transactionItemQuantity.push_back(readLine);
		}

		std::getline(transactionFile, readLine);

		if (readLine[0] != 'S')
		{
			Plog.logError("readTransaction", "Expected S record.  Bailing.  Line number: ");
			return false;
		}

		std::vector<std::string> s_transactionItemPrice;
		while (readLine[0] != 'E')
		{
			std::getline(transactionFile, readLine);

			if (readLine[0] != 'E')
				s_transactionItemPrice.push_back(readLine);
		}

		Transaction inTransaction;

		inTransaction.order_number = StringToInt(s_orderNumber);
		inTransaction.originating_cashier_number = StringToInt(s_originatingCashierNumber);
		inTransaction.approving_cashier_number = StringToInt(s_approvingCashierNumber);
		inTransaction.store_number = StringToInt(s_storeNumber);
		inTransaction.transaction_date = s_transactionDate;
		inTransaction.account_number = StringToInt(s_accountNumber);
		inTransaction.discount_pct = StringToInt(s_discountPct);
		inTransaction.grand_total = StringToDouble(s_grandTotal);


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
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ (\ * 40) RECORD SEPARATOR
}

bool readCustomer()
{
	std::ifstream customerFile;
	customerFile.open(g_customer_file);

	if (!customerFile || !customerFile.good())
	{
		Plog.logError("readCustomer", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(customerFile, readLine);

	if (readLine.substr(0, 5) != "HCUST")
	{
		Plog.logError("readCustomer", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (customerFile.eof())
	{
		Plog.logWarn("readCustomer", "Empty database file.  Continuing.");
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
			Plog.logError("readCustomer", "Expected S record.  Bailing.");
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
			Plog.logError("readCustomer", "Expected S record.  Bailing.");
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

		inCustomer.account_number = StringToInt(s_accountNumber);
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

bool readWarehouseItemData()
{
	std::ifstream warehouseFile;
	warehouseFile.open(g_warehouse_file);

	if (!warehouseFile || !warehouseFile.good())
	{
		Plog.logError("readWarehouseItemData", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(warehouseFile, readLine);

	if (readLine.substr(0, 10) != "HWAREHOUSE")
	{
		Plog.logError("readWarehouseItemData", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (warehouseFile.eof())
	{
		Plog.logWarn("readWarehouseItemData", "Empty database file.  Continuing.");
		return true;
	}

	while (!warehouseFile.eof() || !warehouseFile)
	{

		std::string s_itemStatus;
		std::string s_itemNumber;
		std::string s_vendorNumber;
		std::string s_itemDosage;
		std::string s_coupledItemNumber;
		std::string s_itemDiscountPercent;
		std::string s_itemName;
		std::string s_itemDescription;
		std::string s_reorderQuantity;
		std::string s_reorderLevel;
		std::string s_expectedDeliveryTime;
		std::string s_quantity;
		std::string s_price;

		std::getline(warehouseFile, readLine);
		s_itemStatus = readLine;
		std::getline(warehouseFile, readLine);
		s_itemNumber = readLine;
		std::getline(warehouseFile, readLine);
		s_vendorNumber = readLine;
		std::getline(warehouseFile, readLine);
		s_itemDosage = readLine;
		std::getline(warehouseFile, readLine);
		s_coupledItemNumber = readLine;
		std::getline(warehouseFile, readLine);
		s_itemDiscountPercent = readLine;
		std::getline(warehouseFile, readLine);
		s_itemName = readLine;
		std::getline(warehouseFile, readLine);
		s_itemDescription = readLine;
		std::getline(warehouseFile, readLine);
		s_reorderQuantity = readLine;
		std::getline(warehouseFile, readLine);
		s_reorderLevel = readLine;
		std::getline(warehouseFile, readLine);
		s_expectedDeliveryTime = readLine;
		std::getline(warehouseFile, readLine);
		s_quantity = readLine;
		std::getline(warehouseFile, readLine);
		s_price = readLine;

		WarehouseItemData inWarehouse;

		inWarehouse.item_status = s_itemStatus[0];
		inWarehouse.item_number = StringToInt(s_itemNumber);
		inWarehouse.vendor_number = StringToInt(s_vendorNumber);
		inWarehouse.item_dosage = s_itemDosage;
		inWarehouse.coupled_item_number = StringToInt(s_coupledItemNumber);
		inWarehouse.item_discount_percent = StringToInt(s_itemDiscountPercent);
		inWarehouse.item_name = s_itemName;
		inWarehouse.item_description = s_itemDescription;
		inWarehouse.reorder_quantity = StringToLongLong(s_reorderQuantity);
		inWarehouse.reorder_level = StringToLongLong(s_reorderLevel);
		inWarehouse.expected_delivery_time = s_expectedDeliveryTime;
		inWarehouse.quantity = StringToLongLong(s_quantity);
		inWarehouse.price = StringToDouble(s_price);

		warehouse_table.push_back(inWarehouse);

		std::getline(warehouseFile, readLine); // Read past separator

	}

	/*
	class WarehouseItemData
	{
	public:
	char item_status = 'A'; // 'D' or 'A'
	int item_number = -1; // Key
	int vendor_number = -1;
	std::string item_dosage = ""; // mg
	int coupled_item_number = -1;
	int item_discount_percent = 0;
	std::string item_name = "";
	std::string item_description = "";
	long long reorder_quantity = -1;  // Default reorder amount
	long long reorder_level = -1;  // When warehouse quantity gets below this, order reorder_quantity
	std::string expected_delivery_time = "";  // Number of days will take be back in stock
	long long quantity = -1;
	double price = 5.0;
	};*/


	warehouseFile.close();
	return true;
}

bool readStoreInventory()
{
	std::ifstream storeInvFile;
	storeInvFile.open(g_storeinv_file);

	if (!storeInvFile || !storeInvFile.good())
	{
		Plog.logError("readStoreInventory", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(storeInvFile, readLine);

	if (readLine.substr(0, 9) != "HSTOREINV")
	{
		Plog.logError("readStoreInventory", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (storeInvFile.eof())
	{
		Plog.logWarn("readStoreInventory", "Empty database file.  Continuing.");
		return true;
	}

	while (!storeInvFile.eof() || !storeInvFile)
	{

		std::string s_itemStatus;
		std::string s_itemNumber;
		std::string s_reorderQuantity;
		std::string s_reorderLevel;
		std::string s_quantity;
		std::string s_storeNumber;
		std::string s_highThreshold;
		std::string s_lowThreshold;
		std::string s_accustockDirection;

		std::getline(storeInvFile, readLine);
		s_itemStatus = readLine;
		std::getline(storeInvFile, readLine);
		s_itemNumber = readLine;
		std::getline(storeInvFile, readLine);
		s_reorderQuantity = readLine;
		std::getline(storeInvFile, readLine);
		s_reorderLevel = readLine;
		std::getline(storeInvFile, readLine);
		s_quantity = readLine;
		std::getline(storeInvFile, readLine);
		s_storeNumber = readLine;
		std::getline(storeInvFile, readLine);
		s_highThreshold = readLine;
		std::getline(storeInvFile, readLine);
		s_lowThreshold = readLine;
		std::getline(storeInvFile, readLine);
		s_accustockDirection = readLine;

		StoreInventory inStoreInv;

		inStoreInv.item_status = s_itemStatus[0];
		inStoreInv.item_number = StringToInt(s_itemNumber);
		inStoreInv.reorder_quantity = StringToLongLong(s_reorderQuantity);
		inStoreInv.reorder_level = StringToLongLong(s_reorderLevel);
		inStoreInv.quantity = StringToLongLong(s_quantity);
		inStoreInv.store_number = StringToInt(s_storeNumber);
		inStoreInv.high_threshold = StringToLongLong(s_highThreshold);
		inStoreInv.low_threshold = StringToLongLong(s_lowThreshold);
		inStoreInv.accustock_direction = StringToLongLong(s_accustockDirection);

		store_inventory_table.push_back(inStoreInv);

		std::getline(storeInvFile, readLine); // Read past separator

	}

	storeInvFile.close();
	return true;
}

bool readStoreData()
{
	std::ifstream storeDataFile;
	storeDataFile.open(g_storedata_file);

	if (!storeDataFile || !storeDataFile.good())
	{
		Plog.logError("readstoreData", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(storeDataFile, readLine);

	if (readLine.substr(0, 10) != "HSTOREDATA")
	{
		Plog.logError("readstoreData", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (storeDataFile.eof())
	{
		Plog.logWarn("readstoreData", "Empty database file.  Continuing.");
		return true;
	}

	while (!storeDataFile.eof() || !storeDataFile)
	{

		std::string s_storeStatus;
		std::string s_storePriority;
		std::string s_storeNumber;
		std::string s_streetAddress;
		std::string s_cityName;
		std::string s_stateName;
		std::string s_zipCode;

		std::getline(storeDataFile, readLine);
		s_storeStatus = readLine;
		std::getline(storeDataFile, readLine);
		s_storePriority = readLine;
		std::getline(storeDataFile, readLine);
		s_storeNumber = readLine;
		std::getline(storeDataFile, readLine);
		s_streetAddress = readLine;
		std::getline(storeDataFile, readLine);
		s_cityName = readLine;
		std::getline(storeDataFile, readLine);
		s_stateName = readLine;
		std::getline(storeDataFile, readLine);
		s_zipCode = readLine;

		StoreData inStoreData;

		inStoreData.store_status = s_storeStatus[0];
		inStoreData.store_priority = StringToInt(s_storePriority);
		inStoreData.store_number = StringToInt(s_storeNumber);
		inStoreData.address = s_streetAddress;
		inStoreData.city_name = s_cityName;
		inStoreData.state_name = s_stateName;
		inStoreData.zip_code = StringToInt(s_zipCode);

		store_data_table.push_back(inStoreData);

		std::getline(storeDataFile, readLine); // Read past separator

	}

	storeDataFile.close();
	return true;

	/*
	class StoreData
	{
	public:
	char store_status = 'O'; // D, O, C - Deactivated, open, or closed
	int store_priority = -1;
	int store_number = -1; // Key 1
	std::string street_address = "";
	std::string city_name = "";
	std::string state_name = "";
	int zip_code = -1;
	};


	*/
}

bool readCoupon()
{
	std::ifstream couponFile;
	couponFile.open(g_coupon_file);

	if (!couponFile || !couponFile.good())
	{
		Plog.logError("readCoupon", "Failed to read database file.  Bailing.");
		return false;
	}

	std::string readLine;
	std::getline(couponFile, readLine);

	if (readLine.substr(0, 7) != "HCOUPON")
	{
		Plog.logError("readCoupon", "Failed to find header in file.  Bailing.");
		return false;
	}

	if (couponFile.eof())
	{
		Plog.logWarn("readCoupon", "Empty database file.  Continuing.");
		return true;
	}

	while (!couponFile.eof() || !couponFile)
	{

		std::string s_couponNumber;
		std::string s_couponDiscountPercent;

		std::getline(couponFile, readLine);
		s_couponNumber = readLine;
		std::getline(couponFile, readLine);
		s_couponDiscountPercent = readLine;

		Coupon inCoupon;

		inCoupon.coupon_number = StringToInt(s_couponNumber);
		inCoupon.discount_pct = StringToInt(s_couponDiscountPercent);

		coupon_table.push_back(inCoupon);

		std::getline(couponFile, readLine); // Read past separator

	}

	couponFile.close();
	return true;
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

bool saveConfig()
{
	std::ofstream configFile;
	configFile.open(g_config_file, ios::out);

	if (!configFile || !configFile.good())
	{
		Plog.logError("writeConfig", "Failed to write database file.  Bailing.");
		return false;
	}

	configFile << "HCONFIG" << endl;

	configFile << systemDate.GetDateStream();

	configFile.close();
	return true;
};

bool saveWarehouseItemData()
{
	//open file for writing
	std::ofstream warehouseFile;
	warehouseFile.open(g_warehouse_file, ios::out);

	//check to make sure file opens properly
	if (!warehouseFile || !warehouseFile.good())
	{
		Plog.logError("writeWarehouseItemData", "Failed to write database file.  Bailing.");
		return false;
	}

	//header
	warehouseFile << "HWAREHOUSE";

	for (int x = 0; x < warehouse_table.size(); x++)
	{
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_status;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_number;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].vendor_number;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_dosage;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].coupled_item_number;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_discount_percent;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_name;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].item_description;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].reorder_quantity;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].reorder_level;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].expected_delivery_time;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].quantity;
		warehouseFile << endl;
		warehouseFile << warehouse_table[x].price;
		warehouseFile << endl;
		warehouseFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";
	}
	return true;
};


// TODO:  POSSIBLY ADDING NEWLINE AT EOF
bool saveStoreInventory()
{
	std::ofstream storeInvFile;
	storeInvFile.open(g_storeinv_file, ios::out);

	//check file opened properly
	if (!storeInvFile || !storeInvFile.good())
	{
		Plog.logError("writeStoreInventory", "Failed to write database file.  Bailing.");
		return false;
	}

	//write header
	storeInvFile << "HSTOREINV";

	//for each store inv entry, write to file
	for (int x = 0; x < store_inventory_table.size(); x++)
	{
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].item_status;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].item_number;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].reorder_quantity;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].reorder_level;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].quantity;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].store_number;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].high_threshold;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].low_threshold;
		storeInvFile << endl;
		storeInvFile << store_inventory_table[x].accustock_direction;
		storeInvFile << endl;
		storeInvFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";

	}
	return true;
};
bool saveStoreData()
{
	std::ofstream storeDataFile;
	storeDataFile.open(g_storedata_file, ios::out);

	if (!storeDataFile || !storeDataFile.good())
	{
		Plog.logError("writestoreData", "Failed to write database file.  Bailing.");
		return false;
	}

	storeDataFile << "HSTOREDATA";


	for (int x = 0; x < store_data_table.size(); x++)
	{
		storeDataFile << endl;
		storeDataFile << store_data_table[x].store_status;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].store_priority;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].store_number;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].address;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].city_name;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].state_name;
		storeDataFile << endl;
		storeDataFile << store_data_table[x].zip_code;
		storeDataFile << endl;
		storeDataFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";
	}
	return true;
};
bool saveCustomer()
{
	std::ofstream customerFile;
	customerFile.open(g_customer_file, ios::out);

	if (!customerFile || !customerFile.good())
	{
		Plog.logError("writeCustomer", "Failed to write database file.  Bailing.");
		return false;
	}

	customerFile << "HCUST";

	for (int x = 0; x < customer_table.size(); x++)
	{
		customerFile << endl;
		customerFile << customer_table[x].account_number;
		customerFile << endl;
		customerFile << customer_table[x].address;
		customerFile << endl;
		customerFile << customer_table[x].name;
		customerFile << endl;

		customerFile << "S";
		customerFile << endl;
		for (int y = 0; y < customer_table[x].cust_items.size(); y++)
		{
			customerFile << customer_table[x].cust_items[y];
			customerFile << endl;
		}
		customerFile << "E";
		customerFile << endl;

		customerFile << "S";
		customerFile << endl;
		for (int z = 0; z < customer_table[x].item_dates.size(); z++)
		{
			customerFile << customer_table[x].item_dates[z];
			customerFile << endl;
		}
		customerFile << "E";
		customerFile << endl;
		customerFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";
	}
	customerFile.close();
	return true;
};
bool saveCoupon()
{
	std::ofstream couponFile;
	couponFile.open(g_coupon_file, ios::out);

	if (!couponFile || !couponFile.good())
	{
		Plog.logError("writeCoupon", "Failed to write database file.  Bailing.");
		return false;
	}

	//coupon_table
	couponFile << "HCOUPON";

	for (int x = 0; x < coupon_table.size(); x++)
	{
		couponFile << endl;
		couponFile << coupon_table[x].coupon_number;
		couponFile << endl;
		couponFile << coupon_table[x].discount_pct;
		couponFile << endl;
		couponFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";
	}

	couponFile.close();
	return true;
};
bool saveTransaction()
{
	std::ofstream transactionFile;
	transactionFile.open(g_transaction_file, ios::out);

	if (!transactionFile || !transactionFile.good())
	{
		Plog.logError("writeTransaction", "Failed to write database file.  Bailing.");
		return false;
	}

	//transaction_table

	transactionFile << "HTRANS";

	for (int x = 0; x < transaction_table.size(); x++)
	{
		transactionFile << endl;
		transactionFile << transaction_table[x].order_number;
		transactionFile << endl;
		transactionFile << transaction_table[x].originating_cashier_number;
		transactionFile << endl;
		transactionFile << transaction_table[x].approving_cashier_number;
		transactionFile << endl;
		transactionFile << transaction_table[x].store_number;
		transactionFile << endl;
		transactionFile << transaction_table[x].transaction_date;
		transactionFile << endl;
		transactionFile << transaction_table[x].account_number;
		transactionFile << endl;
		transactionFile << transaction_table[x].discount_pct;
		transactionFile << endl;
		transactionFile << transaction_table[x].grand_total;
		transactionFile << endl;

		transactionFile << "S";
		transactionFile << endl;
		for (int y = 0; y < transaction_table[x].transaction_item_number.size(); y++)
		{
			transactionFile << transaction_table[x].transaction_item_number[y];
			transactionFile << endl;
		}
		transactionFile << "E";
		transactionFile << endl;

		transactionFile << "S";
		transactionFile << endl;
		for (int y = 0; y < transaction_table[x].transaction_item_quantity.size(); y++)
		{
			transactionFile << transaction_table[x].transaction_item_quantity[y];
			transactionFile << endl;
		}
		transactionFile << "E";
		transactionFile << endl;

		transactionFile << "S";
		transactionFile << endl;
		for (int y = 0; y < transaction_table[x].transaction_item_price.size(); y++)
		{
			transactionFile << transaction_table[x].transaction_item_price[y];
			transactionFile << endl;
		}
		transactionFile << "E";
		transactionFile << endl;
		transactionFile << "///////////////////////////////////////////////////////////////////////////////////////////////////////////";
	}
	transactionFile.close();
	return true;
};

bool saveSequenceNumbers()
{
	std::ofstream sequenceFile;
	sequenceFile.open(g_sequence_file, ios::out);

	if (!sequenceFile || !sequenceFile.good())
	{
		Plog.logError("writesequence", "Failed to write database file.  Bailing.");
		return false;
	}

	//sequence_table
	sequenceFile << "HSEQUENCE";
	sequenceFile << endl;
	
	for (int x = 0; x < 12; x++)
	{	
		sequenceFile << sequenceNumber[x];
		sequenceFile << endl;		
	}

	sequenceFile.close();
	return true;
}
