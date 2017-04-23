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
	for (int i = 0; i < store_data_table.length(); i++)
	{
		if (store_data_table[i].store_number == store_number)
			return i;		
	}

	return -1;
}

int findStoreItem(int item_number)
{
	for (int i = 0; i < store_inventory_table.length(); i++)
	{
		if (store_inventory_table[i].item_number == item_number)
			return i;
	}

	return -1;
}

int findWarehouseItem(int item_number)
{
	for (int i = 0; i < warehouse_table.length(); i++)
	{
		if (warehouse_table[i].item_number == item_number)
			return i;
	}

	return -1;
}


