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

int main()
{

	// Attempt to read in sequence database file, create if they don't exist
	// If they exist, Perform trailer / record check on database files
	// If they exist, Perform record size check on each line in database files
		
	int rsResult = readSequenceNumbers();
	if (!rsResult)
	{
		Plog.logError("Main", "Unable to successfully load sequence numbers.  Bailing");
		return 1;
	}

	// Attempt to open database files, create if they don't exist
	// If they exist, Perform trailer / record check on database files
	// If they exist, Perform record size check on each line in database files

	int ldResult = loadDatabaseIntoMemory();
	if (!ldResult)
	{
		Plog.logError("Main", "Unable to successfully load all databases.  Bailing");
		return 1;
	}	
	
	displayMainMenu();	

	int svResult = saveDatabaseToDisk();
	if (!svResult)
	{
		Plog.logError("Main", "Unable to successfully save all databases.  Bailing");
		return 1;
	}

	return 0;
}
