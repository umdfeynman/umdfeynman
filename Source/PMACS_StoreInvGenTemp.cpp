#include <vector>
#include <string>
#include <algorithm>
#include "PMACS_Defines.h"
#include "PMACS_StoreInvGenTemp.h"
#include "PMACS_Globals.h"
#include "PMACS_File.h"
#include "PMACS_Logger.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Utility.h"
#include "PMACS_String.h"

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
    
    while(storeUpdateFile.good() && !storeUpdateFile.eof())
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
    
    for(int i = 0; i< store_inventory_events.size(); i++)
    {
        for(int j = 1; j< 16; j++)
        {
            if(store_inventory_events[i].store_priority == j)
            {
                priorityArray[j].push_back(store_inventory_events[i]);
            }
        }
    } 
    
    for(int i = 0; i<16; i++)
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
            
            int store_item_index = findStoreItem(priorityArray[i][j].item_number);
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
	bool createResult = createFile("leftovers.txt",leftoversFile );
	if (!createResult)
	{
		Plog.logError("storeInventoryGeneration", "Unable to create or write to leftovers.txt");
		return false;		
	}
    insertHeader(leftoversFile, g_leftovers);
    
    int item_counter = 0;
    for(int i=0 ; i< leftovers.size(); i++)
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
		StringIntZeroFill(g_leftovers_txt_store_number_len,leftovers[i].store_number)<<
        StringIntZeroFill(g_leftovers_txt_store_priority_len,leftovers[i].store_priority )<<
        StringIntZeroFill(g_leftovers_txt_item_number_len,leftovers[i].item_number )<<
        StringIntZeroFill(g_leftovers_txt_requested_quantity_len, leftovers[i].requested_quantity) << std::endl << std::flush;
    }
    
    insertTrailer(leftoversFile, item_counter);
    leftoversFile.close();

	return true;
}