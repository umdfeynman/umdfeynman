// Include section
#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include "PMACS_Defines.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include <vector>
#include <iostream>
#include <cmath>

// Globals
// Classes?  Functions?  Modules?  Non-define variables?
// Should tables be globals?  Or in Main?

int displayMainMenu()
{
	// If success return 0
	return 0;
	// If failure return error#	
}

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
	Plog.setContext("Main");	
	int ldResult = loadDatabaseIntoMemory();
	if (!ldResult)
	{
		Plog.logError("Unable to successfully load all databases.  Bailing");
		return 1;
	}	
	
	
	// Display main menu
	/* DisplayMainMenu();
			DisplaySalesMenu
				RunSalesReports
					Transaction*/
	// Exit main menu or exit because of error
	
	// Destroy any remaining objects
	// Close and save in-memory data to database files (Rewrite whole thing?)
	// Close log file
	return 0;
}
