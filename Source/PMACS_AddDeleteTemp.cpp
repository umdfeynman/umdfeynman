#include "PMACS_AddDeleteTemp.h"
#include "PMACS_Defines.h"
#include "PMACS_File.h"
#include "PMACS_Globals.h"
#include "PMACS_Utility.h"
#include "PMACS_String.h"

bool addDeleteStore()
{
	ifstream addDeleteFile;
    
    if(openFile("adddeletestore.txt", addDeleteFile))
    {
        Plog.logInfo("adddeletestore.txt", "File opened successfully.");
    }
    else
    {
		Plog.logWarn("adddeletestore.txt", "File does not exist or unable to read.");
    }
    
    if(!headerCheck(addDeleteFile))
    {
        Plog.logError("adddeletestore.txt", "Header read failed.");
        return false;
    }
    
    if(!sequenceCheck(addDeleteFile, g_adddeletestore))
    {
        Plog.logError("adddeletestore.txt", "Sequence out of order.");
        return false;
    }
    
    int trailerResult;
    trailerResult = trailerCheck(addDeleteFile);
    
    if(trailerResult == -1)
    {
       Plog.logError("adddeletestore.txt", "Unable to locate trailer or trailer count mismatch"); 
    }
    if(trailerResult == 0)
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
    
	std::cout << ADS_Events.size();
	return true;
}

/*
Add_Delete_Store_Event prevItem
prevItem.action = 'Z'
int currStore = 0
int itemCounter = 0
For each item in Add_Delete_Store_Event
	if item.action == A
		If prevItem.action == I | A
			Out of sequence, log
		currStore = item.store_number
		Add store based on item
	if item.action == D
		If prevItem.action == I | A
			Out of sequence, log
		Delete store based on item
	if item.action == I
		If prevItem.action != A || I
			Out of sequence, don't process (break)
		itemCounter++
		Process I based on item under currStore (add to store inventory)
	if item.action == C
		If prevItem.action != I
			Out of sequence, don't process (break)
		Process C (record count)
		itemCounter = 0
		currStore = 0
	else
		Log error "invalid action code"
	prevItem = item
*/