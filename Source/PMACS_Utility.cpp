#include "PMACS_Globals.h"

int getSequenceNumber(int seq_index)
{
	return sequenceNumber[seq_index];
}

int getRecordLength(int rec_index)
{
	return recordLength[rec_index];
}

// UNTESTED !!!!!!
int findStore(int store_number)
{
	for (int i = 0; i < store_data_table.size(); i++)
	{
		if (store_data_table[i].store_number == store_number)
			return i;
	}

	return -1;
}


int findStoreItem(int item_number)
{
	for (int i = 0; i < store_inventory_table.size(); i++)
	{
		if (store_inventory_table[i].item_number == item_number)
			return i;
	}

	return -1;
}

int findWarehouseItem(int item_number)
{
	for (int i = 0; i < warehouse_table.size(); i++)
	{
		if (warehouse_table[i].item_number == item_number)
			return i;
	}

	return -1;
}

//give number and store
int findStoreItem(int item_number, int storeNumber)
{
	for (int i = 0; i < store_inventory_table.size(); i++)						//for all the store items
	{
		if (store_inventory_table[i].store_number == storeNumber)				//match store
		{
			if (store_inventory_table[i].item_number == item_number)			//match item
			{
				return i;														//return index
			}
		}
	}
	return -1;
}

//give itemnumber and character to get list of all containing the item
vector<int> getStoreItemList(int item_number)
{
	vector<int> list; 

	for (int i = 0; i < store_inventory_table.size(); i++)						//for all the store items
	{
		if (store_inventory_table[i].item_number == item_number);				//match number
		{
			list.push_back(i);													//add index to list
		}
	}
	return list;
}