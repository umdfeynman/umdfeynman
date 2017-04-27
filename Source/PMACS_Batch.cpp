#include "PMACS_Batch.h"
#include "PMACS_Logger.h"
#include "PMACS_Globals.h"
#include "PMACS_String.h"
#include "PMACS_File.h"
#include "PMACS_Utility.h"
#include <algorithm>

bool runOfflineBatchProcess()
{
	bool lastResult;
	/*lastResult = massInventoryUpdates();
	if (!lastResult)
	{
	Plog.logError("runOfflineBatchProcess", "massInventoryUpdates failed.  Bailing.");
	return false;
	}*/

	lastResult = addDeleteStore();
	if (!lastResult)
	{
		Plog.logError("runOfflineBatchProcess", "addDeleteStore failed.  Bailing.");
		return false;
	}

	/*lastResult = calculateAccuStock();
	if (!lastResult)
	{
	Plog.logError("runOfflineBatchProcess", "calculateAccuStock failed.  Bailing.");
	return false;
	}*/

	lastResult = warehouseInventoryGeneration();
	if (!lastResult)
	{
		Plog.logError("runOfflineBatchProcess", "warehouseInventoryGeneration failed.  Bailing.");
		return false;
	}

	lastResult = storeInventoryGeneration();
	if (!lastResult)
	{
		Plog.logError("runOfflineBatchProcess", "storeInventoryGeneration failed.  Bailing.");
		return false;
	}

	// Increment system date by 1
	systemDate.ChangeDay(1);

	return true;
}

bool checkAllStoresClosed()
{
	for (int i = 0; i < store_data_table.size(); i++)
	{
		if (store_data_table[i].store_status == 'O')
			return false;
	}

	return true;
}

void openAllStores()
{
	for (int i = 0; i < store_data_table.size(); i++)
	{
		if (store_data_table[i].store_status == 'C')
		{
			store_data_table[i].store_status = 'O';
		}
	}
}

// TODO:  PUT IN HEADER LENGTH (TOO SHORT / TOO LONG) CHECKS
bool addDeleteStore()
{
	ifstream addDeleteFile;

	if (openFile("adddeletestore.txt", addDeleteFile))
	{
		Plog.logInfo("adddeletestore.txt", "File opened successfully.");
	}
	else
	{
		Plog.logWarn("adddeletestore.txt", "File does not exist or unable to read.");
		return true;
	}

	if (!headerCheck(addDeleteFile))
	{
		Plog.logError("adddeletestore.txt", "Header read failed.");
		return false;
	}

	if (!sequenceCheck(addDeleteFile, g_adddeletestore))
	{
		Plog.logError("adddeletestore.txt", "Sequence out of order.");
		return false;
	}

	int trailerResult;
	trailerResult = trailerCheck(addDeleteFile, false);

	if (trailerResult == -1)
	{
		Plog.logError("adddeletestore.txt", "Unable to locate trailer or trailer count mismatch");
	}
	if (trailerResult == 0)
	{
		Plog.logInfo("adddeletestore.txt", "Trailer count is 0");
		return true;
	}

	// Input section
	positionFileForRecords(addDeleteFile);

	std::vector<Add_Delete_Store_Event> ADS_Events;

	std::string inputLine;
	std::string inputString;
	int rowCounter = 1; // Since we already read in header

	while (addDeleteFile.good() && !addDeleteFile.eof())
	{
		std::getline(addDeleteFile, inputLine);
		rowCounter++;

		if (inputLine[0] == 'A')
		{
			Add_Delete_Store_Event addDeleteInstance;
			addDeleteInstance.action_type = 'A';

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_number_pos, g_adddeletestore_txt_a_store_number_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Store number " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_number = StringToInt(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_address_pos, g_adddeletestore_txt_a_store_address_len);
			addDeleteInstance.address = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_city_name_pos, g_adddeletestore_txt_a_store_city_name_len);
			addDeleteInstance.city_name = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_state_pos, g_adddeletestore_txt_a_store_state_len);
			if (!validateAllLetters(inputString))
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: State composed of characters other than letters");
				continue;
			}
			addDeleteInstance.state_name = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_zip_pos, g_adddeletestore_txt_a_store_zip_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Zip code " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.zip_code = StringToInt(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_a_store_priority_pos, g_adddeletestore_txt_a_store_priority_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Store priority " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_priority_level = StringToInt(inputString);

			ADS_Events.push_back(addDeleteInstance);
		}
		else if (inputLine[0] == 'D')
		{
			Add_Delete_Store_Event addDeleteInstance;
			addDeleteInstance.action_type = 'D';

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_number_pos, g_adddeletestore_txt_d_store_number_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Store number " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_number = StringToInt(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_address_pos, g_adddeletestore_txt_d_store_address_len);
			addDeleteInstance.address = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_city_name_pos, g_adddeletestore_txt_d_store_city_name_len);
			addDeleteInstance.city_name = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_state_pos, g_adddeletestore_txt_d_store_state_len);
			if (!validateAllLetters(inputString))
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: State composed of characters other than letters");
				continue;
			}
			addDeleteInstance.state_name = inputString;

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_zip_pos, g_adddeletestore_txt_d_store_zip_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Zip code " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.zip_code = StringToInt(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_d_store_priority_pos, g_adddeletestore_txt_d_store_priority_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Store priority " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_priority_level = StringToInt(inputString);

			ADS_Events.push_back(addDeleteInstance);
		}
		else if (inputLine[0] == 'I')
		{
			Add_Delete_Store_Event addDeleteInstance;
			addDeleteInstance.action_type = 'I';

			inputString = inputLine.substr(g_adddeletestore_txt_i_item_number_pos, g_adddeletestore_txt_i_item_number_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Item number " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.item_number = StringToInt(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_i_store_default_quantity_pos, g_adddeletestore_txt_i_store_default_quantity_len);
			if (StringToLongLong(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Default quantity " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_default_quantity = StringToLongLong(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_i_store_reorder_level_pos, g_adddeletestore_txt_i_store_reorder_level_len);
			if (StringToLongLong(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Reorder level " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_reorder_level = StringToLongLong(inputString);

			inputString = inputLine.substr(g_adddeletestore_txt_i_store_reorder_quantity_pos, g_adddeletestore_txt_i_store_reorder_quantity_len);
			if (StringToLongLong(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Reorder quantity " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_reorder_quantity = StringToLongLong(inputString);

			ADS_Events.push_back(addDeleteInstance);

		}
		else if (inputLine[0] == 'C')
		{

			Add_Delete_Store_Event addDeleteInstance;
			addDeleteInstance.action_type = 'C';

			inputString = inputLine.substr(g_adddeletestore_txt_c_store_overall_item_count_pos, g_adddeletestore_txt_c_store_overall_item_count_len);
			if (StringToInt(inputString) < 0)
			{
				Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: C record count " + inputString + " is negative.");
				continue;
			}
			addDeleteInstance.store_overall_item_count = StringToInt(inputString);

			ADS_Events.push_back(addDeleteInstance);

		}
		else if (inputLine[0] == 'T')
		{
			Plog.logInfo("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Trailer reached");
		}
		else
		{
			Plog.logError("addDeleteStore", "Row [" + std::to_string(rowCounter) + "]: Invalid action code");
		}

	}



	// Create the files
	ofstream addStoreItemsFile;
	ofstream returnItemsFile;

	createFile("addstoreitems.txt", addStoreItemsFile);
	insertHeader(addStoreItemsFile, g_addstoreitems);

	createFile("returnitems.txt", returnItemsFile);
	insertHeader(returnItemsFile, g_returnitems);

	// Process & cleanup

	Add_Delete_Store_Event prevItem;
	prevItem.action_type = 'Z';
	int currStore = 0;
	int currPriority = 0;
	int addItemCounter = 0;
	int controlRecordCounter = 0;
	int deleteItemCounter = 0;

	for (int i = 0; i < ADS_Events.size(); i++)
	{
		if (ADS_Events[i].action_type == 'A')
		{
			if (prevItem.action_type == 'A' || prevItem.action_type == 'I')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Action Code [" + ADS_Events[i].action_type + "]: previous action was [" + prevItem.action_type + "] - out of sequence, continuing");
			}

			// Check if store exists and is active
			int findResult = findStore(ADS_Events[i].store_number);
			if (findResult != -1 && (store_data_table[findResult].store_status == 'O' || store_data_table[findResult].store_status == 'C'))
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Store [" + std::to_string(ADS_Events[i].store_number) + "] already exists and is active, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			// Check if store exists but is deactivated
			if (findResult != -1 && store_data_table[findResult].store_status == 'D')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Store [" + std::to_string(ADS_Events[i].store_number) + "] already exists and is inactive - please create store with a different store number, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			currStore = ADS_Events[i].store_number;
			currPriority = ADS_Events[i].store_priority_level;
			StoreData storeDataInstance;
			storeDataInstance.store_status = 'O';
			storeDataInstance.store_priority = ADS_Events[i].store_priority_level;
			storeDataInstance.store_number = ADS_Events[i].store_number;
			storeDataInstance.address = ADS_Events[i].address;
			storeDataInstance.city_name = ADS_Events[i].city_name;
			storeDataInstance.state_name = ADS_Events[i].state_name;
			storeDataInstance.zip_code = ADS_Events[i].zip_code;

			store_data_table.push_back(storeDataInstance);
		}
		else if (ADS_Events[i].action_type == 'D')
		{
			if (prevItem.action_type == 'A' || prevItem.action_type == 'I')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Action Code [" + ADS_Events[i].action_type + "]: previous action was [" + prevItem.action_type + "] - out of sequence, continuing");
			}

			// Check if store does not exist
			int findResult = findStore(ADS_Events[i].store_number);
			if (findResult == -1)
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Store [" + std::to_string(ADS_Events[i].store_number) + "] does not exist, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			// Check if store exists but is deactivated
			if (findResult != -1 &&
				store_data_table[findResult].store_status == 'D')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Store [" + std::to_string(ADS_Events[i].store_number) + "] already exists and is inactive(deleted), setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			// Check if store exists but any field doesn't match
			if (findResult != -1 &&
				(
					(store_data_table[findResult].store_priority != ADS_Events[i].store_priority_level) ||
					(store_data_table[findResult].store_number != ADS_Events[i].store_number) ||
					(store_data_table[findResult].address != ADS_Events[i].address) ||
					(store_data_table[findResult].city_name != ADS_Events[i].city_name) ||
					(store_data_table[findResult].state_name != ADS_Events[i].state_name) ||
					(store_data_table[findResult].zip_code != ADS_Events[i].zip_code)
					)
				)
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Store [" + std::to_string(ADS_Events[i].store_number) + "]: delete request field mismatch, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}


			for (int j = 0; j < store_inventory_table.size(); j++)
			{
				if (store_inventory_table[j].store_number == ADS_Events[i].store_number)
				{
					deleteItemCounter++;

					int warehouseItemResult = findWarehouseItem(store_inventory_table[j].item_number);

					returnItemsFile << StringIntZeroFill(4, warehouse_table[warehouseItemResult].vendor_number) <<
						StringIntZeroFill(9, store_inventory_table[j].item_number) <<
						StringLongLongZeroFill(10, store_inventory_table[j].quantity) << std::endl << std::flush;

					store_inventory_table[j].item_status = 'D';
				}
			}

			store_data_table[i].store_status = 'D';
		}
		else if (ADS_Events[i].action_type == 'I')
		{
			if (prevItem.action_type != 'A' && prevItem.action_type != 'I')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Action Code [" + ADS_Events[i].action_type + "]: previous action was [" + prevItem.action_type + "] - out of sequence, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			// Check if item exists at warehouse
			if (findWarehouseItem(ADS_Events[i].item_number) == -1)
			{
				controlRecordCounter++;
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Action Code [" + ADS_Events[i].action_type + "]: Item Number [" + std::to_string(ADS_Events[i].item_number) + "] does not exist in item data, skipping");
				continue;
			}

			controlRecordCounter++;
			addItemCounter++;

			StoreInventory storeInventoryInstance;
			storeInventoryInstance.item_number = ADS_Events[i].item_number;
			storeInventoryInstance.reorder_level = ADS_Events[i].store_reorder_level;
			storeInventoryInstance.reorder_quantity = ADS_Events[i].store_reorder_quantity;
			storeInventoryInstance.high_threshold = (float)ADS_Events[i].store_reorder_level * 1.15f;
			storeInventoryInstance.low_threshold = (float)ADS_Events[i].store_reorder_level * 0.85f;
			storeInventoryInstance.store_number = currStore;

			store_inventory_table.push_back(storeInventoryInstance);

			addStoreItemsFile << 'A' << StringIntZeroFill(5, currStore) <<
				StringIntZeroFill(2, currPriority) <<
				StringIntZeroFill(9, ADS_Events[i].item_number) <<
				StringLongLongZeroFill(10, ADS_Events[i].store_default_quantity) << std::endl << std::flush;
		}
		else if (ADS_Events[i].action_type == 'C')
		{
			if (prevItem.action_type != 'I')
			{
				Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Action Code [" + ADS_Events[i].action_type + "]: previous action was [" + prevItem.action_type + "] - out of sequence, setting prev action code to Z and skipping");
				prevItem.action_type = 'Z';
				continue;
			}

			if (ADS_Events[i].store_overall_item_count != controlRecordCounter)
			{
				Plog.logWarn("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Control record count [" + std::to_string(ADS_Events[i].store_overall_item_count) + "]: not equal to number of items: [" + std::to_string(addItemCounter) + "]");
			}

			controlRecordCounter = 0;
			currStore = 0;
			currPriority = 0;
		}
		else
		{
			Plog.logError("addDeleteStore", "Event Item [" + std::to_string(i) + "]: Invalid Action Code [" + std::to_string(ADS_Events[i].action_type) + "], skipping");
		}

		prevItem = ADS_Events[i];

	}



	std::cout << ADS_Events.size();


	insertTrailer(returnItemsFile, deleteItemCounter);
	returnItemsFile.close();
	insertTrailer(addStoreItemsFile, addItemCounter);
	addStoreItemsFile.close();

	return true;
}

bool warehouseInventoryGeneration()
{
	ifstream warehouseInvGenFile;
	bool openResult = openFile("itemreceived.txt", warehouseInvGenFile);

	if (openResult)
	{
		Plog.logInfo("itemreceived.txt", "File opened successfully");
	}
	else
	{
		Plog.logWarn("itemreceived.txt", "No file to read or unable to open file, skipping");
		return true;
	}

	bool headerResult = headerCheck(warehouseInvGenFile);
	if (!headerResult)
	{
		Plog.logError("itemreceived.txt", "Header read failed");
		return false;
	}

	bool sequenceResult = sequenceCheck(warehouseInvGenFile, g_itemreceived);
	if (!sequenceResult)
	{
		Plog.logError("itemreceived.txt", "Sequence out of order");
		return false;
	}

	int trailerResult;
	trailerResult = trailerCheck(warehouseInvGenFile, false);

	if (trailerResult == -1)
	{
		Plog.logError("itemreceived.txt", "Unable to locate trailer or trailer count mismatch");
	}
	if (trailerResult == 0)
	{
		Plog.logInfo("itemreceived.txt", "Trailer count is 0, bailing successfully");
		return true;
	}

	positionFileForRecords(warehouseInvGenFile);

	std::vector<Merge_Vendor_Return_Event> warehouse_invgen_events;

	std::string inputLine;
	std::string inputString;

	while (warehouseInvGenFile.good() && !warehouseInvGenFile.eof())
	{
		Merge_Vendor_Return_Event warehouseInvGenInstance;

		std::getline(warehouseInvGenFile, inputLine);

		if (!validateAllNumbers(inputLine))
		{
			Plog.logError("itemreceived.txt", "Row found without numbers, skipping");
			continue;
		}

		inputString = inputLine.substr(g_returnitems_txt_vendor_number_pos, g_returnitems_txt_vendor_number_len);
		warehouseInvGenInstance.vendor_number = StringToInt(inputString);

		inputString = inputLine.substr(g_returnitems_txt_item_number_pos, g_returnitems_txt_item_number_len);
		warehouseInvGenInstance.item_number = StringToInt(inputString);

		inputString = inputLine.substr(g_returnitems_txt_incoming_quantity_pos, g_returnitems_txt_incoming_quantity_len);
		warehouseInvGenInstance.incoming_quantity = StringToLongLong(inputString);

		warehouse_invgen_events.push_back(warehouseInvGenInstance);
	}

	for (int i = 0; i < warehouse_invgen_events.size(); i++)
	{
		bool itemFound = false;

		int findResult = -1;
		findResult = findWarehouseItem(warehouse_invgen_events[i].item_number);

		if (findResult == -1)
		{
			Plog.logError("itemreceived.txt", "Item [" + std::to_string(warehouse_invgen_events[i].item_number) + "] not found in item data, skipping");
			break;
		}

		// TODO SHOULD WE BE CHECKING IF VENDOR MATCHES??? ASK STEINER
		if (warehouse_invgen_events[i].item_number == warehouse_table[findResult].item_number)
		{
			if (warehouse_invgen_events[i].vendor_number == warehouse_table[findResult].vendor_number)
			{
				warehouse_table[findResult].quantity += warehouse_invgen_events[i].incoming_quantity;
				itemFound = true;
				continue;
			}
			else
			{
				Plog.logError("itemreceived.txt", "Item [" + std::to_string(warehouse_invgen_events[i].item_number) + "] found but vendor_number [" + std::to_string(warehouse_invgen_events[i].vendor_number) + "] does not match warehouse item vendor_number [" + std::to_string(warehouse_table[findResult].vendor_number) + "], skipping");
				continue;
			}
		}
	}

	warehouseInvGenFile.close();
	return true;
}
/*
// File doesn't exist OK
// Item doesn't exist OK
// Vendor doesn't exist OK
*/


/*
xint currStore = 0
xint itemCounter = 0
xFor each item in Add_Delete_Store_Event
x	xif item.action == A
x		If prevItem.action == I | A
x			Out of sequence, log
x		currStore = item.store_number
x		Add store based on item
x	if item.action == D
x		If prevItem.action == I | A
x			Out of sequence, log
x		Delete store based on item
x	if item.action == I
x		If prevItem.action != A || I
x			Out of sequence, don't process (break)
x		itemCounter++
x		Process I based on item under currStore (add to store inventory)
x	if item.action == C
x		If prevItem.action != I
x			Out of sequence, don't process (break)
x		Process C (record count)
x		itemCounter = 0
x		currStore = 0
x	else
x		Log error "invalid action code"
x	prevItem = item
*/

// Test cases:
// File exists?
// Header
// Sequence
// Trailer

// Sort OK

// Batch replenishment:  item quantity at store exceeds reorder level OK

// Warehouse item exists and is active OK
// Store exists OK
// Item exists at store and is active OK
// Item priority matches store priority OK
// Quantity at warehouse is more than requested amount OK


// Warehouse item does not exist OK
// Warehouse item exists and is deactivated OK
// Store does not exist OK
// Item does not exist at store OK
// Item exists at store and is deactivated OK
// Item priority doesn't match store priority OK

// Quantity at warehouse is exactly requested amount OK
// Quantity at warehouse is less than requested amount OK
// Can't create leftovers.txt OK

// TODO:  PUT IN HEADER LENGTH (TOO SHORT / TOO LONG) CHECKS
bool storeInventoryGeneration()
{
	ifstream storeUpdateFile;
	bool openResult = openFile("storeupdate.txt", storeUpdateFile);

	if (openResult)
	{
		Plog.logInfo("storeupdate.txt", "File opened successfully");
	}
	else
	{
		Plog.logWarn("storeupdate.txt", "No file to read or unable to open file, skipping");
		return true;
	}

	bool headerResult = headerCheck(storeUpdateFile);
	if (!headerResult)
	{
		Plog.logError("storeupdate.txt", "Header read failed");
		return false;
	}

	bool sequenceResult = sequenceCheck(storeUpdateFile, g_storeupdate);
	if (!sequenceResult)
	{
		Plog.logError("storeupdate.txt", "Sequence out of order");
		return false;
	}

	int trailerResult;
	trailerResult = trailerCheck(storeUpdateFile, false);

	if (trailerResult == -1)
	{
		Plog.logError("storeupdate.txt", "Unable to locate trailer or trailer count mismatch");
	}
	if (trailerResult == 0)
	{
		Plog.logInfo("storeupdate.txt", "Trailer count is 0, bailing successfully");
		return true;
	}

	positionFileForRecords(storeUpdateFile);

	std::vector<Merge_Add_Online_Batch_Event> store_inventory_events;

	std::string inputLine;
	std::string inputString;

	while (storeUpdateFile.good() && !storeUpdateFile.eof())
	{
		Merge_Add_Online_Batch_Event storeInvGenInstance;

		std::getline(storeUpdateFile, inputLine);
		if (inputLine[0] == 'A' || inputLine[0] == 'O' || inputLine[0] == 'B')
		{
			inputString = inputLine.substr(g_storeupdate_txt_source_code_pos, g_storeupdate_txt_source_code_len);
			//storeInvGenInstance.source_code = inputString[0];
			// convert from A, O, B to g_source_code_add, g_source_code_batch, g_source_code_online for sorting
			switch (inputLine[0])
			{
			case 'A':
				storeInvGenInstance.source_code = g_source_code_add;
				break;
			case 'O':
				storeInvGenInstance.source_code = g_source_code_online;
				break;
			case 'B':
				storeInvGenInstance.source_code = g_source_code_batch;
				break;
			}

			inputString = inputLine.substr(g_storeupdate_txt_store_number_pos, g_storeupdate_txt_store_number_len);
			storeInvGenInstance.store_number = StringToInt(inputString);

			inputString = inputLine.substr(g_storeupdate_txt_store_priority_pos, g_storeupdate_txt_store_priority_len);
			storeInvGenInstance.store_priority = StringToInt(inputString);

			inputString = inputLine.substr(g_storeupdate_txt_item_number_pos, g_storeupdate_txt_item_number_len);
			storeInvGenInstance.item_number = StringToInt(inputString);

			inputString = inputLine.substr(g_storeupdate_txt_requested_quantity_pos, g_storeupdate_txt_requested_quantity_len);
			storeInvGenInstance.requested_quantity = StringToLongLong(inputString);

			store_inventory_events.push_back(storeInvGenInstance);
		}
	}

	struct less_than_source_code
	{
		inline bool operator()(const Merge_Add_Online_Batch_Event& class1, const Merge_Add_Online_Batch_Event& class2)
		{
			return (class1.source_code < class2.source_code);
		}
	};

	std::vector <Merge_Add_Online_Batch_Event> priorityArray[16];

	for (int i = 0; i< store_inventory_events.size(); i++)
	{
		for (int j = 1; j< 16; j++)
		{
			if (store_inventory_events[i].store_priority == j)
			{
				priorityArray[j].push_back(store_inventory_events[i]);
			}
		}
	}

	for (int i = 0; i<16; i++)
	{
		std::sort(priorityArray[i].begin(), priorityArray[i].end(), less_than_source_code());
	}


	std::vector<Merge_Add_Online_Batch_Event> leftovers;

	for (int i = 1; i < 16; i++)
	{
		for (int j = 0; j < priorityArray[i].size(); j++)
		{
			int warehouse_item_index = findWarehouseItem(priorityArray[i][j].item_number);
			if (warehouse_item_index == -1)
			{
				Plog.logError("storeInventoryGeneration", "Item [" + std::to_string(priorityArray[i][j].item_number) + "] does not exist in item data, skipping");
				continue;
			}
			else if (warehouse_table[warehouse_item_index].item_status == 'D')
			{
				Plog.logError("storeInventoryGeneration", "Item [" + std::to_string(priorityArray[i][j].item_number) + "] exists but is deactivated, skipping");
				continue;
			}

			int store_index = findStore(priorityArray[i][j].store_number);
			if (store_index == -1)
			{
				Plog.logError("storeInventoryGeneration", "Store [" + std::to_string(priorityArray[i][j].store_number) + "] does not exist, skipping");
				continue;
			}

			int store_item_index = findStoreItem(priorityArray[i][j].item_number, priorityArray[i][j].store_number);
			if (store_item_index == -1)
			{
				Plog.logError("storeInventoryGeneration", "Item [" + std::to_string(priorityArray[i][j].item_number) + "] does not exist at store [" + std::to_string(priorityArray[i][j].store_number) + "] , skipping");
				continue;
			}
			else if (store_inventory_table[store_item_index].item_status == 'D')
			{
				Plog.logError("storeInventoryGeneration", "Item [" + std::to_string(priorityArray[i][j].item_number) + "] exists at store [" + std::to_string(priorityArray[i][j].store_number) + "] but is deactivated , skipping");
				continue;
			}
			else if (store_data_table[store_index].store_priority != priorityArray[i][j].store_priority)
			{
				Plog.logError("storeInventoryGeneration", "Item [" + std::to_string(priorityArray[i][j].item_number) + "] priority [" + std::to_string(store_data_table[store_index].store_priority) + "] does not match store [" + std::to_string(priorityArray[i][j].store_number) + "] priority [" + std::to_string(store_data_table[store_index].store_priority) + "], skipping");
				continue;
			}
			else if (priorityArray[i][j].source_code == g_source_code_batch && (store_inventory_table[store_item_index].quantity > store_inventory_table[store_item_index].reorder_level))
			{
				Plog.logInfo("storeInventoryGeneration", "Automated replenishment:  Item [" + std::to_string(priorityArray[i][j].item_number) + "] at store [" + std::to_string(priorityArray[i][j].store_number) + "] has quantity [" + std::to_string(store_inventory_table[store_item_index].quantity) + "] which exceeds reorder level of [" + std::to_string(store_inventory_table[store_item_index].reorder_level) + "], skipping");
				continue;
			}

			if (warehouse_table[warehouse_item_index].quantity == priorityArray[i][j].requested_quantity)
			{
				store_inventory_table[store_item_index].quantity += priorityArray[i][j].requested_quantity;
				warehouse_table[warehouse_item_index].quantity = 0;
				// Batch replenishment handles next time
			}
			else if (warehouse_table[warehouse_item_index].quantity < priorityArray[i][j].requested_quantity)
			{
				// Not enough quantity, reset item quantity to what we still need after we fulfill from warehouse.
				priorityArray[i][j].requested_quantity = priorityArray[i][j].requested_quantity - warehouse_table[warehouse_item_index].quantity;
				leftovers.push_back(priorityArray[i][j]);

				store_inventory_table[store_item_index].quantity += warehouse_table[warehouse_item_index].quantity;
				warehouse_table[warehouse_item_index].quantity = 0;
			}
			else if (warehouse_table[warehouse_item_index].quantity > priorityArray[i][j].requested_quantity)
			{
				store_inventory_table[store_item_index].quantity += priorityArray[i][j].requested_quantity;
				warehouse_table[warehouse_item_index].quantity -= priorityArray[i][j].requested_quantity;
			}


		}

	}


	storeUpdateFile.close();

	ofstream leftoversFile;
	bool createResult = createFile("leftovers.txt", leftoversFile);
	if (!createResult)
	{
		Plog.logError("storeInventoryGeneration", "Unable to create or write to leftovers.txt");
		return false;
	}
	insertHeader(leftoversFile, g_leftovers);

	int item_counter = 0;
	for (int i = 0; i< leftovers.size(); i++)
	{
		item_counter++;
		//      
		char sourceCode;
		switch (leftovers[i].source_code)
		{
		case g_source_code_add:
			sourceCode = 'A';
			break;
		case g_source_code_online:
			sourceCode = 'O';
			break;
		case g_source_code_batch:
			sourceCode = 'B';
			break;
		}

		leftoversFile << sourceCode <<
			StringIntZeroFill(g_leftovers_txt_store_number_len, leftovers[i].store_number) <<
			StringIntZeroFill(g_leftovers_txt_store_priority_len, leftovers[i].store_priority) <<
			StringIntZeroFill(g_leftovers_txt_item_number_len, leftovers[i].item_number) <<
			StringIntZeroFill(g_leftovers_txt_requested_quantity_len, leftovers[i].requested_quantity) << std::endl << std::flush;
	}

	insertTrailer(leftoversFile, item_counter);
	leftoversFile.close();

	return true;
}







bool ComposeDuplicateControlMessageCheck(int count, char code, int line)
{
	if (count > 0)
	{
		string message = "Duplicate N";
		message += code;	//action code
		message += " - Type record on line: ";
		message += to_string(line);							//line count
		Plog.logError("UpdateItem:ActionCodeCheck:OOPS", message);
		return true;
	}
	return false;
};

bool massInventoryUpdates()
{
	vector<Update_Item_Data_Event> d_event;
	vector<Update_Item_Data_Event> a_event;
	vector<Change_Data_Event> c_event;
	vector<Update_Item_Data_Event> n_event;

	ifstream inPut;
	if ((!openFile("test4.txt", inPut) || !headerCheck(inPut) || !sequenceCheck(inPut, sequenceNumber[g_items])))
	{
		//abandon ship
		Plog.logError("UpdateProcessStart", "Process aborted. Sequence/header/file read error.");
		return false;
	}

	else
	{
		trailerCheck(inPut, true);
		positionFileForRecords(inPut);

		int NDcount = -1;
		int NAcount = -1;
		int NCcount = -1;
		int lineCount = 1;

		while (!inPut.eof())
		{
			lineCount++;
			string record;
			getline(inPut, record);
			Update_Item_Data_Event update;
			Change_Data_Event change;

			//only process line if N record or trailer if record length is incorrect
			if (correctRecordLength(record, g_items, lineCount) || (record[0] != 'N') || (record[0] != 'T'))
			{
				switch (record[0])
				{
				case 'D':
				{
					if (0 > stoi(record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len)))							//if item number is less than 0
					{
						Plog.logError("UpdateItem:DeleteItem:ValueRangeCheck:OOPS", "Item number is negative.");						//error
					}
					else
					{
						update.action_type = record[0];																					//store action code		
						update.item_number = stoi(record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len));			//store item number
						d_event.push_back(update);
					}
					break;
				}

				case 'A':
				{
					//item number check
					if (0 > stoi(record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len)))							//if item number is less than 0
					{
						Plog.logError("UpdateItem:AddItem:ValueRangeCheck:OOPS", "Item number is negative.");						//error
					}
					//warehouse reorder level check
					else if (0 > stoll(record.substr(g_items_txt_a_warehouse_reorder_level_pos, g_items_txt_a_warehouse_reorder_level_len)))
					{
						Plog.logError("UpdateItem:AddItem:ValueRangeCheck:OOPS", "Warehouse reorder level is negative.");						//error
					}
					//vender number check
					else if (0 > stoll(record.substr(g_items_txt_a_vendor_number_pos, g_items_txt_a_vendor_number_len)))
					{
						Plog.logError("UpdateItem:AddItem:ValueRangeCheck:OOPS", "Vender number is negative.");						//error
					}
					//warehouse reorder quantity check
					else if (0 > stoll(record.substr(g_items_txt_a_warehouse_reorder_quantity_pos, g_items_txt_a_warehouse_reorder_quantity_len)))
					{
						Plog.logError("UpdateItem:AddItem:ValueRangeCheck:OOPS", "Warehouse reorder quantity is negative.");						//error
					}
					else
					{
						//store the stuff 
						update.action_type = record[0];																					//store action code		
						update.item_number = stoi(record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len));			//store item number
						update.item_name = record.substr(g_items_txt_a_item_name_pos, g_items_txt_a_item_name_len);
						update.item_description = record.substr(g_items_txt_a_item_description_pos, g_items_txt_a_item_description_len);
						update.item_dosage = record.substr(g_items_txt_a_item_dosage_pos, g_items_txt_a_item_dosage_len);
						update.warehouse_reorder_level = stoll(record.substr(g_items_txt_a_warehouse_reorder_level_pos, g_items_txt_a_warehouse_reorder_level_len));
						update.vendor_number = stoi(record.substr(g_items_txt_a_vendor_number_pos, g_items_txt_a_vendor_number_len));
						update.warehouse_reorder_quantity = stoll(record.substr(g_items_txt_a_warehouse_reorder_quantity_pos, g_items_txt_a_warehouse_reorder_quantity_len));
						update.expected_delivery_time = record.substr(g_items_txt_a_expected_delivery_time_pos, g_items_txt_a_expected_delivery_time_len);

						//push the thing 
						a_event.push_back(update);
					}
					break;
				}

				case 'C':
				{
					//item number check
					if (0 > stoi(record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len)))							//if item number is less than 0
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "Item number is negative.");						//error
					}
					//warehouse reorder level check
					else if (0 > stoll(record.substr(g_items_txt_a_warehouse_reorder_level_pos, g_items_txt_a_warehouse_reorder_level_len)))
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "Warehouse reorder level is negative.");						//error
					}
					//vender number check
					else if (0 > stoll(record.substr(g_items_txt_a_vendor_number_pos, g_items_txt_a_vendor_number_len)))
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "Vender number is negative.");						//error
					}
					//warehouse reorder quantity check
					else if (0 > stoll(record.substr(g_items_txt_a_warehouse_reorder_quantity_pos, g_items_txt_a_warehouse_reorder_quantity_len)))
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "Warehouse reorder quantity is negative.");						//error
					}
					else
					{
						//put the stuff in
						change.action_type = record[0];																					//store action code		
						change.item_number = (record.substr(g_items_txt_a_item_number_pos, g_items_txt_a_item_number_len));			//store item number
						change.item_name = record.substr(g_items_txt_a_item_name_pos, g_items_txt_a_item_name_len);
						change.item_description = record.substr(g_items_txt_a_item_description_pos, g_items_txt_a_item_description_len);
						change.item_dosage = record.substr(g_items_txt_a_item_dosage_pos, g_items_txt_a_item_dosage_len);
						change.warehouse_reorder_level = (record.substr(g_items_txt_a_warehouse_reorder_level_pos, g_items_txt_a_warehouse_reorder_level_len));
						change.vendor_number = (record.substr(g_items_txt_a_vendor_number_pos, g_items_txt_a_vendor_number_len));
						change.warehouse_reorder_quantity = (record.substr(g_items_txt_a_warehouse_reorder_quantity_pos, g_items_txt_a_warehouse_reorder_quantity_len));
						change.expected_delivery_time = record.substr(g_items_txt_a_expected_delivery_time_pos, g_items_txt_a_expected_delivery_time_len);

						//add the other thing
						c_event.push_back(change);
					}
					break;
				}

				case 'N':
				{
					if (record[1] != 'A' && record[1] != 'C' && record[1] != 'D')																	//not NA|NC|ND
					{
						Plog.logError("UpdateItem:ActionCodeCheck:OOPS", "Invalid N-Type record on line ~INSERT LINE HERE~.");						//error
					}
					else																															//it IS one of those things
					{
						//assign action code
						update.action_type = record[0];

						//assign corresponding code count and action designation
						if (record[1] == 'A')
						{
							update.item_action_count = stoi(record.substr(g_items_txt_n_item_action_count_pos, g_items_txt_n_item_action_count_len));
							update.specific_action_designation = record[1];
							NAcount++;

							if (!ComposeDuplicateControlMessageCheck(NAcount, update.specific_action_designation, lineCount))
							{
								if (update.item_action_count != a_event.size())
								{
									string message = "A Record count does not match expected. Line: ";
									message += to_string(lineCount);
									Plog.logError("UpdateItem:ControlCountCheck:OOPS", message);
								}
							}
						}
						if (record[1] == 'C')
						{
							update.item_action_count = stoi(record.substr(g_items_txt_n_item_action_count_pos, g_items_txt_n_item_action_count_len));
							update.specific_action_designation = record[1];
							NCcount++;
							if (!ComposeDuplicateControlMessageCheck(NCcount, update.specific_action_designation, lineCount))
							{
								if (update.item_action_count != c_event.size())
								{
									string message = "C Record count does not match expected. Line: ";
									message += to_string(lineCount);
									Plog.logError("UpdateItem:ControlCountCheck:OOPS", message);
								}
							}
						}
						if (record[1] == 'D')
						{
							update.item_action_count = stoi(record.substr(g_items_txt_n_item_action_count_pos, g_items_txt_n_item_action_count_len));
							update.specific_action_designation = record[1];
							NDcount++;
							if (!ComposeDuplicateControlMessageCheck(NDcount, update.specific_action_designation, lineCount))
							{
								if (update.item_action_count != d_event.size())
								{
									string message = "D Record count does not match expected. Line: ";
									message += to_string(lineCount);
									Plog.logError("UpdateItem:ControlCountCheck:OOPS", message);
								}
							}
						}

						// add to thing
						n_event.push_back(update);
					}
					break;
				}
				//do nothing
				case 'T':
				{
					break;
				}


				default:
				{
					Plog.logError("UpdateItem:ActionCodeCheck:OOPS", "Invalid action code on line ~INSERT LINE HERE~.");						//error
					break;
				}
				}
			}
		}

		if (NAcount == -1)
		{
			Plog.logError("UpdateItem:ControlCodeCheck:OOPS", "Missing NA record");
		}
		if (NCcount == -1)
		{
			Plog.logError("UpdateItem:ControlCodeCheck:OOPS", "Missing ND record");
		}
		if (NDcount == -1)
		{
			Plog.logError("UpdateItem:ControlCodeCheck:OOPS", "Missing ND record");
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////updates/////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////delete//////////////////////////////////////////
	bool gotSumStawk = false;
	for (int x = 0; x < d_event.size(); x++)
	{
		int wIndex = findWarehouseItem(d_event[x].item_number);
		if ((wIndex == -1) || (warehouse_table[x].item_status == 'D'))							//cant find item or is deactivated
		{
			Plog.logError("UpdateItem:DeleteItem", "Cannot cannot delete item. Cant find item or is deactivated");
			break;
		}
		else if ((wIndex >= 0))																	//item found
		{
			if (warehouse_table[wIndex].quantity != 0)											//has stock
			{
				gotSumStawk = true;
				break;
			}
			else																				//does not have stock
			{
				for (int y = 0; y < store_inventory_table.size(); y++)
				{
					if ((store_inventory_table[y].item_number == d_event[x].item_number)		//if item is found in store table 
						&& (store_inventory_table[y].item_status = 'A'))						//and is active
					{
						if (store_inventory_table[y].quantity != 0)								//and has stock
						{
							gotSumStawk = true;
							break;
						}
					}
				}
			}
		}

		if (!gotSumStawk)
		{
			for (int y = 0; y < store_inventory_table.size(); y++)
			{
				if ((store_inventory_table[y].item_number == d_event[x].item_number)		//if item is found in store table 
					&& (store_inventory_table[y].item_status = 'A'))						//and is active
				{
					store_inventory_table[y].item_status = 'D';								//deactivate items
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////add//////////////////////////////////////////

	for (int x = 0; x < a_event.size(); x++)
	{
		int wIndex = findWarehouseItem(d_event[x].item_number);
		if (wIndex == -1 || (warehouse_table[wIndex].item_status == 'D'))														//cant find it
		{
			if (wIndex != -1 && warehouse_table[wIndex].item_status == 'D')
			{
				//warehouse_table.erase(warehouse_table.begin() + x - 1);			//delete from table to readd
				Plog.logError("UpdateItem:AddItem", "Cannot add deactivated item");
			}
			else
			{
				WarehouseItemData addInv;

				addInv.item_status = 'A';																					//store action code		
				addInv.item_number = a_event[x].item_number;
				addInv.item_name = a_event[x].item_name;
				addInv.item_description = a_event[x].item_description;
				addInv.item_dosage = a_event[x].item_dosage;
				addInv.reorder_level = a_event[x].warehouse_reorder_level;
				addInv.vendor_number = a_event[x].vendor_number;
				addInv.reorder_quantity = a_event[x].warehouse_reorder_quantity;
				addInv.expected_delivery_time = a_event[x].expected_delivery_time;

				warehouse_table.push_back(addInv);
			}
		}
		else
		{
			Plog.logError("UpdateItem:AddItem", "Item already exists");
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////change//////////////////////////////////////////
	for (int x = 0; x < c_event.size(); x++)
	{
		int wIndex = findWarehouseItem(stoi(c_event[x].item_number));
		if (wIndex == -1 || (warehouse_table[wIndex].item_status == 'D'))														//cant find it or D
		{
			Plog.logError("UpdateItem:ChangeItem", "Item does not exist or is deactivated.");
		}
		else							//change item
		{

			//change item name
			if (!StringAllSpaceCheck(c_event[x].item_name))
			{
				warehouse_table[wIndex].item_name = c_event[x].item_name;
			}

			//change item description
			if (!StringAllSpaceCheck(c_event[x].item_description))
			{
				warehouse_table[wIndex].item_description = c_event[x].item_description;
			}

			//change item dosage
			if (!StringAllSpaceCheck(c_event[x].item_dosage))
			{
				warehouse_table[wIndex].item_dosage = c_event[x].item_dosage;
			}

			//change reorder level
			if (!StringAllSpaceCheck(c_event[x].warehouse_reorder_level))//
			{
				warehouse_table[wIndex].reorder_level = stoll(c_event[x].warehouse_reorder_level);
			}

			//change vender number
			if (!StringAllSpaceCheck(c_event[x].vendor_number))//
			{
				warehouse_table[wIndex].vendor_number = stoi(c_event[x].vendor_number);
			}


			//change reorder quantity		
			if (!StringAllSpaceCheck(c_event[x].warehouse_reorder_quantity))//
			{
				warehouse_table[wIndex].reorder_quantity = stoll(c_event[x].warehouse_reorder_quantity);
			}

			//change delivery time		
			if (!StringAllSpaceCheck(c_event[x].expected_delivery_time))
			{
				warehouse_table[wIndex].expected_delivery_time = c_event[x].expected_delivery_time;
			}
		}
	}
	inPut.close();
	return true;
}

// TODO:  AccuStock tests
// Add items to store using default reorder quantity / level / etc
// Adjust quantity manually
// Perform accustock 7 times where quantity > high_thresh
// Perform accustock 7 times where quantity < high_thresh
// Perform accustock 7 times where quantity > low_thresh
// Perform accustock 7 times where quantity < low_thresh
// Perform accustock 7 times where quantity alternates between high & low thresh

bool calculateAccuStock()
{
	for (int i = 0; i < store_inventory_table.size(); i++)
	{
		// High threshold is set to 1.15 * reorder_level, low 0.85 * reorder level by default

		// Depending on if quantity is above or below threshold, 
		if (store_inventory_table[i].quantity > store_inventory_table[i].high_threshold)
			store_inventory_table[i].accustock_direction--;
		if (store_inventory_table[i].quantity < store_inventory_table[i].low_threshold)
			store_inventory_table[i].accustock_direction++;


		// If item quantity goes under the low threshold 7 times, increase reorder quantity
		if (store_inventory_table[i].accustock_direction == 7)
		{
			// Increase by 10%
			int increase_amount = 0.1f * (float)store_inventory_table[i].reorder_quantity;
			store_inventory_table[i].reorder_quantity += increase_amount;
			store_inventory_table[i].accustock_direction = 0;
			store_inventory_table[i].high_threshold += increase_amount;
			store_inventory_table[i].low_threshold += increase_amount;
		}

		// If item quantity goes above the high threshold 7 times, decrease reorder quantity
		if (store_inventory_table[i].accustock_direction == -7)
		{
			// Decrease by 10%
			int decrease_amount = 0.1f * (float)store_inventory_table[i].reorder_quantity;
			store_inventory_table[i].reorder_quantity -= decrease_amount;
			store_inventory_table[i].accustock_direction = 0;
			store_inventory_table[i].high_threshold -= decrease_amount;
			store_inventory_table[i].low_threshold -= decrease_amount;
		}

	}

	return true;
}


