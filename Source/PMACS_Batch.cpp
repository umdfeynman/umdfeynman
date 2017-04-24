#include "PMACS_Batch.h"
#include "PMACS_Logger.h"
#include "PMACS_Globals.h"
#include "PMACS_AddDeleteTemp.h"
#include "PMACS_String.h"
#include "PMACS_File.h"
#include "PMACS_Utility.h"

bool runOfflineBatchProcess()
{
	bool lastResult = addDeleteStore();
	if (!lastResult)
	{
		Plog.logError("runOfflineBatchProcess", "addDeleteStore failed.  Bailing.");
		return false;
	}

	return true;
}


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
		Plog.logInfo("adddeletestore.txt", "Trailer count it 0");
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