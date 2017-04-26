#ifndef PMACS_WHINVGEN_H
#define PMACS_WHINVGEN_H

#include <string>
#include <fstream>
#include <vector>

#include "PMACS_File.h"
#include "PMACS_Globals.h"
#include "PMACS_Defines.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Logger.h"
#include "PMACS_Utility.h"
#include "PMACS_String.h"

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

// File doesn't exist OK
// Item doesn't exist OK
// Vendor doesn't exist OK



#endif