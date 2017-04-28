// Include section
#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include "PMACS_Defines.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include "PMACS_File.h"
#include "PMACS_Batch.h"
#include "PMACS_Input.h"
#include "PMACS_Menu.h"
#include "PMACS_Utility.h"
#include "PMACS_String.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <Windows.h>


// Globals
// Classes?  Functions?  Modules?  Non-define variables?
// Should tables be globals?  Or in Main?

int main()
{
	// Instantiate table classes
	// warehouse_item_data
	// store_inventory
	// store_data
	// customer
	// coupon
	// Transaction
	
	// Attempt to open database files, create if they don't exist
	// If they exist, Perform trailer / record check on database files
	// If they exist, Perform record size check on each line in database files
	int rsResult = readSequenceNumbers();
	if (!rsResult)
	{
		Plog.logError("Main", "Unable to successfully load sequence numbers.  Bailing");
		return 1;
	}


	int ldResult = loadDatabaseIntoMemory();
	if (!ldResult)
	{
		Plog.logError("Main", "Unable to successfully load all databases.  Bailing");
		return 1;
	}	
	

	std::string dateTest = systemDate.GetDateStream();

	sequenceNumber[0] = 102;
	sequenceNumber[g_returnitems] = 250;
	sequenceNumber[g_storeupdate] = 749;
	sequenceNumber[g_leftovers] = 900;
	sequenceNumber[g_itemreceived] = 249;

	//// Test adddeletestore
	// Add/Delete
	// xStore present and active
	// xStore present and inactive
	// xStore not present
	// xDelete - fields don't match
	// xDelete - fields do match
	// xItem - Warehouse item doesn't exist
	// xItem - Warehouse item does exist
	// xControl - Control record count off
	// 
	//StoreData deleteInstance;
	//deleteInstance.store_number = 1;
	//deleteInstance.address = "4901 Evergreen       ";
	//deleteInstance.city_name = "Dearborn            ";
	//deleteInstance.state_name = "MI";
	//deleteInstance.zip_code = 481269998;
	//deleteInstance.store_priority = 2; // formerly 2
	//deleteInstance.store_status = 'O';
	//store_data_table.push_back(deleteInstance);
	//
	//StoreData deleteInstance2;
	//deleteInstance2.store_number = 7;
	//deleteInstance2.address = "5012 Ferris         ";
	//deleteInstance2.city_name = "Detroit             ";
	//deleteInstance2.state_name = "NE";
	//deleteInstance2.zip_code = 592370009;
	//deleteInstance2.store_priority = 3;
	//deleteInstance2.store_status = 'A';
	//store_data_table.push_back(deleteInstance2);

	//WarehouseItemData whitem1;
	//whitem1.item_number = 10;
	//whitem1.item_description = "item ten";
	//whitem1.item_name = "ten";
	//whitem1.item_status = 'A';
	//whitem1.vendor_number = 1234;
	//whitem1.quantity = 1000000000; // formerly 1000000000
	//warehouse_table.push_back(whitem1);

	//StoreInventory sitem1;
	//sitem1.item_number = 10; // formerly 100
	//sitem1.item_status = 'A';
	//sitem1.quantity = 20000;
	//sitem1.reorder_level = 9000;
	//sitem1.store_number = 1;
	//store_inventory_table.push_back(sitem1);

	//WarehouseItemData whitem2; 
	//whitem2.item_number = 123;
	//whitem2.item_description = "item ten";
	//whitem2.item_name = "ten";
	//whitem2.item_status = 'A';
	//whitem2.vendor_number = 1234;
	//whitem2.quantity = 1000000000;  // formerly 1000000000
	//warehouse_table.push_back(whitem2);

	//StoreInventory sitem2;
	//sitem2.item_number = 123;  // formerly 123
	//sitem2.item_status = 'A';
	//sitem2.quantity = 20000;
	//sitem2.reorder_level = 120000;
	//sitem2.store_number = 1;
	//store_inventory_table.push_back(sitem2);

	//Customer cust1;
	//cust1.account_number = 1;
	//cust1.address = "2301 Swag Lane";
	//cust1.name = "Brian Brianson";
	//customer_table.push_back(cust1);

	displayMainMenu();
	
	


	std::cout << "Sweet man!" << transaction_table.size() << customer_table.size() << warehouse_table.size() << store_inventory_table.size() <<
		store_data_table.size() << coupon_table.size() << sequenceNumber[0] << std::endl;

	

	
	std::cout << "test";

	/*std::string userInput = "";
	bool validatedInput = "nope";

	int max_length = 50;

	// Expected types for input validation
//#define g_type_int 1 OK
//#define g_type_longlong 2 OK
//#define g_type_char_any 3 OK
//#define g_type_char_letter 4 OK
//#define g_type_string_any 5 OK
//#define g_type_string_letter 6
//#define g_type_double 7 OK

	while (userInput != "done")
	{
		std::cout << "Please enter some shit: \n";
		std::getline(cin, userInput);
			
		validatedInput = validateInput(userInput, g_type_int, max_length, 1);
		if (!validatedInput)
		{
			std::cout << "getUserInput returned failure, you entered: [" << userInput << "] with expected type [g_type_string_any] and max length 10" << std::endl;
		}
		else
		{
			std::cout << "getUserInput returned success, you entered: [" << userInput << "] with expected type [g_type_string_any] and max length 10" << std::endl;
		}
	}
	*/

	
	// Display main menu
	/* DisplayMainMenu();
			DisplaySalesMenu
				RunSalesReports
					Transaction*/
	// Exit main menu or exit because of error
	
	// Destroy any remaining objects
	// Close and save in-memory data to database files (Rewrite whole thing?)
	// Close log file

	int svResult = saveDatabaseToDisk();
	if (!svResult)
	{
		Plog.logError("Main", "Unable to successfully save all databases.  Bailing");
		return 1;
	}

	return 0;
}
