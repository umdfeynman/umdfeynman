// Include section
#include "PMACS_Globals.h"
#include "PMACS_Logger.h"
#include "PMACS_Defines.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Database.h"
#include "PMACS_File.h"
#include "PMACS_Batch.h"
#include "Batch_Inventory_Updates.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

bool ComposeDuplicateControlMessageCheck(int count, char code, int line);

void batchInventoryUpdates()
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
				Plog.logError("UpdateItem:AddItem", "Item number history detected");
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
		int wIndex = findWarehouseItem(d_event[x].item_number);
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
				long long num = stoi(c_event[x].warehouse_reorder_level);
				if (num > 0)
				{
					warehouse_table[wIndex].reorder_level = num;
				}
				else
				{
					Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "warehouse_reorder_level is negative.");						//error
				}
			}

			//change vender number
			if (!StringAllSpaceCheck(c_event[x].vendor_number))//
			{
				if (!StringAllSpaceCheck(c_event[x].vendor_number))
				{
					int num = stoi(c_event[x].vendor_number);
					if (num > 0)
					{
						warehouse_table[wIndex].vendor_number = num;
					}
					else
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "vendor_number is negative.");						//error
					}
				}


				//change reorder quantity		
				if (!StringAllSpaceCheck(c_event[x].warehouse_reorder_quantity))//
				{
					long long num = stoi(c_event[x].warehouse_reorder_quantity);
					if (num > 0)
					{
						warehouse_table[wIndex].reorder_quantity = num;
					}
					else
					{
						Plog.logError("UpdateItem:ChangeItem:ValueRangeCheck:OOPS", "warehouse_reorder_quantity is negative.");						//error
					}
				}

				//change delivery time		
				if (!StringAllSpaceCheck(c_event[x].expected_delivery_time))
				{
					warehouse_table[wIndex].expected_delivery_time = c_event[x].expected_delivery_time;
				}
			}
		}
	}
	inPut.close();
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