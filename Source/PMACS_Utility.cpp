#include "PMACS_Globals.h"
#include "PMACS_Menu.h"
#include "PMACS_String.h"
#include "PMACS_File.h"
#include "PMACS_Utility.h"

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


int findStoreItem(int item_number, int store_number)
{
	for (int i = 0; i < store_inventory_table.size(); i++)
	{
		if (store_inventory_table[i].item_number == item_number && store_inventory_table[i].store_number == store_number)
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

int findCustomer(int account_number)
{
	for (int i = 0; i < customer_table.size(); i++)
	{
		if (customer_table[i].account_number == account_number)
			return i;
	}

	return -1;
}

bool setCurrentCustomerNumber(int account_number)
{
	Menu temp;

	int findResult = findCustomer(account_number);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Failed to select customer, account not found");
		return false;
	}

	currentCustomerNumber = account_number;
	currentCustomerIndex = findResult;

	return true;
}

bool setCurrentStore(int store_number)
{
	Menu temp;

	int findResult = findStore(store_number);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Failed to select store, store not found");
		return false;
	}

	currentStoreNumber = store_number;
	currentStoreIndex = findResult;

	return true;
}

bool setCurrentItemByNumber(int item_number)
{
	Menu temp;

	int findResult = findWarehouseItem(item_number);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Failed to add item to item selection, item not found");
		return false;
	}

	for (int i = 0; i < currentItemList.size(); i++)
	{
		if (warehouse_table[findResult].item_number == warehouse_table[currentItemList[i]].item_number)
		{
			temp.displayDialogNoReturn("Failed to add item to item selection, item already exists in list");
			return false;
		}
	}

	currentItemList.push_back(findResult);
	currentItemListSize--;

	return true;
}

int findWarehouseItemByItemName(std::string item_name)
{
	for (int i = 0; i < warehouse_table.size(); i++)
	{

		std::string trimmedWarehouseItem = trimTrailingLeadingSpaces(warehouse_table[i].item_name);
		std::string trimmedInputItem = trimTrailingLeadingSpaces(item_name);
		std::string cleanWarehouseItem = upperCase(trimmedWarehouseItem);
		std::string cleanInputItem = upperCase(trimmedInputItem);


		if (cleanInputItem == cleanWarehouseItem)
		{
			return i;
		}
	}
	return -1;
}

// Adds items to currentItemList
bool setCurrentItemByName(std::string item_name)
{
	Menu temp;

	int findResult = findWarehouseItemByItemName(item_name);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Failed to add item to item selection, item not found");
		return false;
	}

	for (int i = 0; i < currentItemList.size(); i++)
	{
		if (warehouse_table[findResult].item_number == warehouse_table[currentItemList[i]].item_number)
		{
			temp.displayDialogNoReturn("Failed to add item to item selection, item already exists in list");
			return false;
		}
	}

	currentItemList.push_back(findResult);
	currentItemListSize--;

	return true;
}

// Clear item selections
void clearItemSelections()
{
	Menu temp;

	temp.displayDialogNoReturn("Item selections cleared");

	currentItemList.clear();
	currentItemListSize = 0;

	return;
}
bool setCurrentCashier(int cashier_number)
{
	currentCashierNumber = cashier_number;

	return true;
}

//give itemnumber and character to get list of all containing the item
vector<int> getStoreItemList(int item_number)
{
	vector<int> list;

	for (int i = 0; i < store_inventory_table.size(); i++)						//for all the store items
	{
		if (store_inventory_table[i].item_number == item_number)				//match number
		{
			list.push_back(i);													//add index to list
		}
	}
	return list;
}

int findCustomerByNameAddress(std::string customer_name, std::string customer_address)
{
	for (int i = 0; i< customer_table.size(); i++)
	{
		std::string cleanCustomerName = upperCase(trimTrailingLeadingSpaces(customer_table[i].name));
		std::string cleanInputCustomerName = upperCase(trimTrailingLeadingSpaces(customer_name));
		std::string cleanCustomerAddress = upperCase(trimTrailingLeadingSpaces(customer_table[i].address));
		std::string cleanInputCustomerAddress = upperCase(trimTrailingLeadingSpaces(customer_address));

		if (cleanCustomerName == cleanInputCustomerName && cleanCustomerAddress == cleanInputCustomerAddress)
		{
			return i;
		}
	}
	return -1;
}
//TEST
void closeAllStores()
{
	for (int i = 0; i < store_data_table.size(); i++)
	{
		if (store_data_table[i].store_status == 'O')
		{
			store_data_table[i].store_status = 'C';
		}
	}
}
//TEST
void closeStore()
{
	store_data_table[currentStoreIndex].store_status = 'C';
}

//TEST
//check coupon
//return index
//if -1, no coupon for that number
int CouponCheck(int couponID)
{
	if (coupon_table.size() == 0)			//no coupons
	{
		return -1;
	}
	else
	{
		for (int x = 0; x < coupon_table.size(); x++)
		{
			if (couponID == coupon_table[x].coupon_number)		//found ID
			{
				return x;
			}
		}
		return -1;
	}
}
//TEST
bool deleteCoupon(int couponID)
{
	int couponIndex = CouponCheck(couponID);

	if (couponIndex == -1)			//coupon doesnt exist, cant delete
	{
		return false;
	}
	else							// found. delete coupon
	{
		coupon_table.erase(coupon_table.begin() + couponIndex);
		return true;
	}
}
//TEST
bool addCoupon(int couponID, int couponDiscount)
{
	if (CouponCheck(couponID) == -1) //no coupon for that ID coupon
	{
		Coupon newCoupon;

		//assign values
		newCoupon.coupon_number = couponID;
		newCoupon.discount_pct = couponDiscount;

		//add to table
		coupon_table.push_back(newCoupon);

		return true;
	}
	return false;  //else failed to make coupon
}



// *********************untested******************************
// caution: use with the assumption that an item existence check has
// already been done
int checkCoupled(int item_one_index, int item_two_index)
{
	if (warehouse_table[item_one_index].coupled_item_number != -1)
	{
		Plog.logInfo("checkCoupledItems", "Item one already has coupling");
		return 1;
	}
	if (warehouse_table[item_two_index].coupled_item_number != -1)
	{
		Plog.logInfo("checkCoupledItems", "Items two already has coupling");
		return 2;
	}
	if (warehouse_table[item_two_index].coupled_item_number != -1 && warehouse_table[item_two_index].coupled_item_number != -1)
	{
		Plog.logInfo("checkCoupledItems", "Both items already have coupling");
		return 3;
	}
	
	
	return -1;
}

//TEST
int getCoupledItemIndex(int in_item_number)
{
	
	int itemIndex = findWarehouseItem(in_item_number);
	
	if (warehouse_table[itemIndex].coupled_item_number == -1)
		return -1;
	
	if (itemIndex == -1)
	{
		Plog.logError("getCoupledItem", "Failed to find item at warehouse");
		return -1;
	}

	for (int i = 0; i < warehouse_table.size(); i++)
	{
		if (warehouse_table[i].coupled_item_number == in_item_number)
		{
			return i;
		}
	}

	return -1;
}

//TEST
bool coupleItems(int item_one, int item_two)
{
	int itemOneIndex = findWarehouseItem(item_one);
	int itemTwoIndex = findWarehouseItem(item_two);
	int isCoupled;

	if (itemOneIndex == -1 || itemTwoIndex == -1)
	{
		Plog.logError("coupleItems", "Failed to find item at warehouse");
		return false;
	}

	isCoupled = checkCoupled(itemOneIndex, itemTwoIndex); // check if items are coupled

	if (isCoupled != -1) // if items are already coupled together
	{
		Plog.logWarn("coupleItems", "One or both items are already coupled"); 
		return false;
	}
	else if (isCoupled == -1) // if items are not coupled together
	{
		warehouse_table[itemOneIndex].coupled_item_number = warehouse_table[itemTwoIndex].item_number;
		warehouse_table[itemTwoIndex].coupled_item_number = warehouse_table[itemOneIndex].item_number;
		Plog.logInfo("coupleItems", "Item have been coupled");
	}
	return true;
}

//TEST
bool uncoupleItems(int item_one, int item_two)
{
	int itemOneIndex = findWarehouseItem(item_one);
	int itemTwoIndex = findWarehouseItem(item_two);
	int isCoupled;

	if (itemOneIndex == -1 == itemTwoIndex == 1)
	{
		Plog.logError("coupleItems", "Failed to find at warehouse");
		return false;
	}

	isCoupled = checkCoupled(itemOneIndex, itemTwoIndex); // check if items are coupled

	if (isCoupled == -1) // if items are not already coupled together
	{
		Plog.logWarn("coupleItems", "Items are not coupled together"); 
	}
	// if items are coupled together
	else if (warehouse_table[itemOneIndex].coupled_item_number == warehouse_table[itemTwoIndex].item_number &&
		     warehouse_table[itemTwoIndex].coupled_item_number == warehouse_table[itemOneIndex].item_number)		
	{
		warehouse_table[itemOneIndex].coupled_item_number = -1; // set back to default
		warehouse_table[itemTwoIndex].coupled_item_number = -1; // set back to default
		Plog.logInfo("coupledItems", "Item have been uncoupled");
	}
	return true;
}

// TEST
void assignItemsToAllStores()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}

	long long setReorderLevel = temp.displayDialogGetEntryLongLong("Please enter the reorder level to assign to the items (10 digits): ", 10);

	if (setReorderLevel == -1)
		return;

	long long setReorderQuantity = temp.displayDialogGetEntryLongLong("Please enter the reorder quantity to assign to the items (10 digits): ", 10);

	if (setReorderQuantity == -1)
		return;

	// For each item in list
	// If item already assigned to store but active, skip
	// If item already assigned to store but inactive, overwrite
	// If item not assigned to store, add to store
	for (int i = 0; i < currentItemList.size(); i++)
	{
		for (int j = 0; j < store_data_table.size(); j++)
		{
			int findStoreItemResult = findStoreItem(warehouse_table[currentItemList[i]].item_number, store_data_table[i].store_number);
			if (findStoreItemResult == -1)
			{
				StoreInventory storeInventoryInstance;
				storeInventoryInstance.item_status = 'A';
				storeInventoryInstance.item_number = warehouse_table[currentItemList[i]].item_number;
				storeInventoryInstance.quantity = 0;
				storeInventoryInstance.store_number = store_data_table[i].store_number;
				storeInventoryInstance.reorder_level = setReorderLevel;
				storeInventoryInstance.reorder_quantity = setReorderQuantity;
				storeInventoryInstance.high_threshold = 1.15f * (float)setReorderLevel;
				storeInventoryInstance.low_threshold = 0.85f * (float)setReorderLevel;
				store_inventory_table.push_back(storeInventoryInstance);

				Plog.logInfo("assignItemsToStore", "Item <ITEM> assigned to store <STORE>");
			}
			else if (store_inventory_table[findStoreItemResult].item_status = 'A')
			{
				Plog.logInfo("assignItemsToStore", "Item <ITEM> already assigned to store <STORE> and active, skipping");
				continue;
			}
			else if (store_inventory_table[findStoreItemResult].item_status = 'D')
			{
				// Directly in store_inventory_table
				store_inventory_table[findStoreItemResult].item_status = 'A';
				store_inventory_table[findStoreItemResult].item_number = warehouse_table[currentItemList[i]].item_number;
				store_inventory_table[findStoreItemResult].quantity = 0;
				store_inventory_table[findStoreItemResult].store_number = store_data_table[i].store_number;
				store_inventory_table[findStoreItemResult].reorder_level = setReorderLevel;
				store_inventory_table[findStoreItemResult].reorder_quantity = setReorderQuantity;
				store_inventory_table[findStoreItemResult].high_threshold = 1.15f * (float)setReorderLevel;
				store_inventory_table[findStoreItemResult].low_threshold = 0.85f * (float)setReorderLevel;
			}
		}
	}
}

// Test
// Assign/Remove from store
void assignItemsToStore()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}	

	int assignStoreNumber = temp.displayDialogGetEntryInt("Please enter the store number to assign the items to (5 digits): ", 5);

		if (assignStoreNumber == -1)
			return;

	int findResult = findStore(assignStoreNumber);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Error - store not found");
		return;
	}

	long long setReorderLevel = temp.displayDialogGetEntryLongLong("Please enter the reorder level to assign to the items (10 digits): ", 10);

	if (setReorderLevel == -1)
		return;

	long long setReorderQuantity = temp.displayDialogGetEntryLongLong("Please enter the reorder quantity to assign to the items (10 digits): ", 10);

	if (setReorderQuantity == -1)
		return;

	// For each item in list
	// If item already assigned to store but active, skip
	// If item already assigned to store but inactive, overwrite
	// If item not assigned to store, add to store
	for (int i = 0; i < currentItemList.size(); i++)
	{
		int findStoreItemResult = findStoreItem(warehouse_table[currentItemList[i]].item_number, assignStoreNumber);
		if (findStoreItemResult == -1)
		{
			StoreInventory storeInventoryInstance;
			storeInventoryInstance.item_status = 'A';
			storeInventoryInstance.item_number = warehouse_table[currentItemList[i]].item_number;
			storeInventoryInstance.quantity = 0;
			storeInventoryInstance.store_number = assignStoreNumber;
			storeInventoryInstance.reorder_level = setReorderLevel;
			storeInventoryInstance.reorder_quantity = setReorderQuantity;
			storeInventoryInstance.high_threshold = 1.15f * (float)setReorderLevel;
			storeInventoryInstance.low_threshold = 0.85f * (float)setReorderLevel;
			store_inventory_table.push_back(storeInventoryInstance);

			Plog.logInfo("assignItemsToStore", "Item <ITEM> assigned to store <STORE>");
		}
		else if (store_inventory_table[findStoreItemResult].item_status = 'A')
		{
			Plog.logInfo("assignItemsToStore", "Item <ITEM> already assigned to store <STORE> and active, skipping");
			continue;
		}
		else if (store_inventory_table[findStoreItemResult].item_status = 'D')
		{
			// Directly in store_inventory_table
			store_inventory_table[findStoreItemResult].item_status = 'A';
			store_inventory_table[findStoreItemResult].item_number = warehouse_table[currentItemList[i]].item_number;
			store_inventory_table[findStoreItemResult].quantity = 0;
			store_inventory_table[findStoreItemResult].store_number = assignStoreNumber;
			store_inventory_table[findStoreItemResult].reorder_level = setReorderLevel;
			store_inventory_table[findStoreItemResult].reorder_quantity = setReorderQuantity;
			store_inventory_table[findStoreItemResult].high_threshold = 1.15f * (float)setReorderLevel;
			store_inventory_table[findStoreItemResult].low_threshold = 0.85f * (float)setReorderLevel;
		}
	}
}

// Test
void removeItemsFromStore()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}

	int removeStoreNumber = temp.displayDialogGetEntryInt("Please enter the store number to remove the items from (5 digits): ", 5);

	if (removeStoreNumber == -1)
		return;

	int findResult = findStore(removeStoreNumber);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Error - store not found");
		return;
	}

	// For each item in list
	// If item already assigned to store and active but no inventory, remove
	// If item already assigned to store and active but has inventory, skip
	// If item already assigned to store but inactive, skip
	// If item not assigned to store, skip

	for (int i = 0; i < currentItemList.size(); i++)
	{

		int findStoreItemResult = findStoreItem(warehouse_table[currentItemList[i]].item_number, removeStoreNumber);
		if (findStoreItemResult == -1)
		{
			Plog.logInfo("removeItemsFromStore", "Item <ITEM> not found at store <STORE>");
			continue;
		}
		else if (store_inventory_table[findStoreItemResult].item_status = 'A' && store_inventory_table[findStoreItemResult].quantity != 0)
		{
			Plog.logInfo("removeItemsFromStore", "Item <ITEM> assigned to store <STORE> but quantity is >0, skipping");
			continue;
		}
		else if (store_inventory_table[findStoreItemResult].item_status = 'A' && store_inventory_table[findStoreItemResult].quantity == 0)
		{
			store_inventory_table[findStoreItemResult].item_status = 'D';
			Plog.logInfo("removeItemsFromStore", "Item <ITEM> assigned to store <STORE> and quantity is 0, deactivating");
		}
		else if (store_inventory_table[findStoreItemResult].item_status = 'D')
		{
			Plog.logInfo("removeItemsFromStore", "Item <ITEM> exists for store <STORE> but is already deactivated, skipping");
			continue;
		}
	}
}

// TEST
void removeItemsFromAllStores()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}

	// For each item in list
	// If item already assigned to store and active but no inventory, remove
	// If item already assigned to store and active but has inventory, skip
	// If item already assigned to store but inactive, skip
	// If item not assigned to store, skip

	for (int i = 0; i < currentItemList.size(); i++)
	{
		for (int j = 0; j < store_data_table.size(); j++)
		{
			int findStoreItemResult = findStoreItem(warehouse_table[currentItemList[i]].item_number, store_data_table[i].store_number);
		
			if (findStoreItemResult == -1)
			{
				Plog.logInfo("removeItemsFromStore", "Item <ITEM> not found at store <STORE>");
				continue;
			}
			else if (store_inventory_table[findStoreItemResult].item_status = 'A' && store_inventory_table[findStoreItemResult].quantity != 0)
			{
				Plog.logInfo("removeItemsFromStore", "Item <ITEM> assigned to store <STORE> but quantity is >0, skipping");
				continue;
			}
			else if (store_inventory_table[findStoreItemResult].item_status = 'A' && store_inventory_table[findStoreItemResult].quantity == 0)
			{
				store_inventory_table[findStoreItemResult].item_status = 'D';
				Plog.logInfo("removeItemsFromStore", "Item <ITEM> assigned to store <STORE> and quantity is 0, deactivating");
			}
			else if (store_inventory_table[findStoreItemResult].item_status = 'D')
			{
				Plog.logInfo("removeItemsFromStore", "Item <ITEM> exists for store <STORE> but is already deactivated, skipping");
				continue;
			}
		}
	}
}

// Test
void changeItemStatus()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}


	char newItemStatus = temp.displayDialogGetEntryChar("Please enter the new status (A/D): ");

	if (newItemStatus == 0)
		return;

	if (newItemStatus != 'A' && newItemStatus != 'D' && newItemStatus != 'a' && newItemStatus != 'd')
	{
		temp.displayDialogNoReturn("Error - you did not enter a valid status");
		return;
	}

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].item_status = newItemStatus;
		Plog.logInfo("changeItemStatus", "Item status set to [" + std::to_string(newItemStatus) + "]");
	}
}

// Test
void changeVendorNumber()
{

	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}


	int newVendorNumber = temp.displayDialogGetEntryInt("Please enter the new vendor number (4 digits): ", 4);

	if (newVendorNumber == -1)
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].vendor_number = newVendorNumber;
		Plog.logInfo("changeVendorNumber", "Vendor number set to [" + std::to_string(newVendorNumber) + "]");
	}
}

// Test
void changeItemDosage()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}

	std::string newDosage = temp.displayDialogGetEntryString("Please enter the new dosage (20 chars): ", 20);

	if (newDosage == "")
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].item_dosage = newDosage;
		Plog.logInfo("changeItemDosage", "Item dosage set to [" + newDosage + "]");
	}
}

// Test
void changeItemName()
{

	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}
	
	std::string newName = temp.displayDialogGetEntryString("Please enter the new name (20 chars): ", 20);

	if (newName == "")
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].item_name = newName;
		Plog.logInfo("changeItemName", "Item name set to [" + newName + "]");
	}
}

// Test
void changeItemDescription()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}
	
	std::string newDescription = temp.displayDialogGetEntryString("Please enter the new description (100 chars): ", 100);

	if (newDescription == "")
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].item_description = newDescription;
		Plog.logInfo("changeItemDescription", "Item description set to [" + newDescription + "]");
	}
}

// Test
void changeWarehouseReorderQuantity()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}

	int newWarehouseReorderQuantity = temp.displayDialogGetEntryInt("Please enter the new quantity (10 digits): ", 10);

	if (newWarehouseReorderQuantity == -1)
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].reorder_quantity = newWarehouseReorderQuantity;
		Plog.logInfo("changeWarehouseReorderQuantity", "Item warehuse reorder quantity set to [" + std::to_string(newWarehouseReorderQuantity) + "]");
	}
}

// Test
void changeWarehouseReorderLevel()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}

	int newWarehouseReorderLevel = temp.displayDialogGetEntryInt("Please enter the new quantity level (10 digits): ", 10);

	if (newWarehouseReorderLevel == -1)
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].reorder_level = newWarehouseReorderLevel;
		Plog.logInfo("changeWarehouseReorderLevel", "Item warehouse reorder level set to [" + std::to_string(newWarehouseReorderLevel) + "]");
	}
}

// Test
void changeBasePrice()
{
	Menu temp;
	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no item selected");
		return;
	}

	double newBasePrice = temp.displayDialogGetEntryDouble("Please enter the new base price ($$$$$.$$): ", 8);

	if (newBasePrice == -1.0)
		return;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		warehouse_table[i].price = newBasePrice;
		Plog.logInfo("changeBasePrice", "Item base price level set to [" + std::to_string(newBasePrice) + "]");
	}
}

// Test
void displayItemInfo()
{
	Menu temp;

	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}

	ofstream itemInfo_File;
	bool createResult = createFile("iteminfo.txt", itemInfo_File);

	// For each item in currentItemList:
	itemInfo_File << "== WAREHOUSE ==" << endl << "Item#\t" << "Item Status\t" << "Item Name\t" << "Vendor#\t" << "Qty.\t"
		<< "Dosage\t" << "Coupled\t" << "Discount%\t" << "ReorderQty\t" << "RestockDelay" << endl;
	for (int i = 0; i < currentItemList.size(); i++)
	{

		itemInfo_File << warehouse_table[currentItemList[i]].item_number << "\t" << warehouse_table[currentItemList[i]].item_status << "\t" <<
			warehouse_table[currentItemList[i]].item_name << "\t" << warehouse_table[currentItemList[i]].vendor_number << "\t" <<
			warehouse_table[currentItemList[i]].quantity << "\t" << warehouse_table[currentItemList[i]].item_dosage << "\t" << warehouse_table[currentItemList[i]].item_discount_percent
			<< "\t" << warehouse_table[currentItemList[i]].reorder_quantity << "\t" << warehouse_table[currentItemList[i]].expected_delivery_time << std::endl;
	}

	itemInfo_File << std::endl;

	itemInfo_File << "== STORE ==" << endl << "Item#\t" << "Item Name\t" << "Store#\t" << "Stauts\t" << "Qty." << std::endl;

		/*
		For each store_data item <store> in store_data table
			For each store_inventory item <item> in <store>
				If findItem == item_number
					totalQuantity += <item>.quantity
					Output appropriate fields from <item>*/
	long long overallItemQuantity = 0;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		for (int j = 0; j < store_data_table.size(); j++)
		{
			for (int k = 0; k < store_inventory_table.size(); k++)
			{
				if (store_inventory_table[k].item_number == warehouse_table[currentItemList[i]].item_number &&
					store_inventory_table[k].store_number == store_data_table[j].store_number
					)
				{
					overallItemQuantity += store_inventory_table[k].quantity;
					itemInfo_File << store_inventory_table[k].item_number << "\t" << warehouse_table[currentItemList[i]].item_name << "\t" << store_inventory_table[k].store_number << "\t" <<
						store_inventory_table[currentItemList[i]].item_status << "\t" << store_inventory_table[currentItemList[i]].quantity << std::endl;				
				}				
			}
		}
	}

	itemInfo_File << "======= OVERALL ITEM QUANTITY ========" << std::endl;

	for (int i = 0; i < currentItemList.size(); i++)
	{
		for (int j = 0; j < store_data_table.size(); j++)
		{
			for (int k = 0; k < store_inventory_table.size(); k++)
			{
				if (store_inventory_table[k].item_number == warehouse_table[currentItemList[i]].item_number &&
					store_inventory_table[k].store_number == store_data_table[j].store_number
					)
				{
					overallItemQuantity += store_inventory_table[k].quantity;
				}
			}

		}
		itemInfo_File << warehouse_table[currentItemList[i]].item_number << "\t\t" << overallItemQuantity << std::endl;
		overallItemQuantity = 0;
	}

	itemInfo_File.close();
}

// Test
void displayCurrentList()
{
	Menu temp;

	if (currentItemListSize == 0)
	{
		temp.displayDialogNoReturn("Error - no items selected");
		return;
	}

	ofstream currentItemList_File;
	createFile("currentItemList.txt", currentItemList_File);

	currentItemList_File << "== Items ==" << endl << "Item#\t" << "Item Name\t" << "Item Description" << endl;
	for (int i = 0; i < currentItemList.size(); i++)
	{

		currentItemList_File << warehouse_table[currentItemList[i]].item_number << "\t" << warehouse_table[currentItemList[i]].item_name <<
			"\t" << warehouse_table[currentItemList[i]].item_description << std::endl;

	}
	currentItemList_File.close();
}

void updateItemDiscount()
{
	Menu temp;
	
	int itemNumber = temp.displayDialogGetEntryInt("Please enter the item number (9 digits): ", 9);

	if (itemNumber == -1)
		return;

	int findResult = findWarehouseItem(itemNumber);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Error - no such item exists at the warehouse");
		return;
	}

	int newDiscountPct = temp.displayDialogGetEntryInt("Please enter the new percentage (0-100): ", 3);
	if (newDiscountPct == -1)
		return;

	if (newDiscountPct > 100 || newDiscountPct < 0)
	{
		temp.displayDialogNoReturn("Error - invalid percentage entered");
		return;
	}

	warehouse_table[findResult].item_discount_percent = newDiscountPct;
}


//give user entered ID
//get index of account if exists, 
int accountExistsByNumber(int accNumber)
{
	//Find account
	for (int x = 0; x < customer_table.size(); x++)
	{
		if (customer_table[x].account_number == accNumber)
		{
			return x;       //return account index | true
		}
	}
	return -1; // not found
};

//TEST
//create account and return index. |-1 return to previous menu| 0 account not created/false
int createAccount()
{
	Menu temp;
	Customer newCust;
	string name;
	string address;
	int accID = generateAccountNumber();
	if (accID == -1)
	{
		return accID;
	}
	else if (accountExistsByNumber(accID) == -1)                     //accid is 0, no account found for that number -- make new
	{
		//assign account number
		newCust.account_number = accID;
		cout << "Enter customer information; 2 fields, or q to return to previous menu." << endl;
		//assign name
		cout << "Name: ";
		getline(cin, name);
		newCust.name = name;
		//assign address
		cout << "Address: ";
		getline(cin, address);
		newCust.address = address;
		//add to table
		customer_table.push_back(newCust);
		return (customer_table.size() - 1);
	}
	else                    //account already exists
	{
		cout << "Cannot create new account. Account for that number exists." << endl;
		return 0;
	}
};

//TEST
//returns true when item has been added
//bool addItemToOrderByName(string itemName)
//{
//	int itemNumber;
//	//find item at warehouse to get details
//	int ind = findWarehouseItemByItemName(itemName);
//	if (ind != -1 && warehouse_table[ind].item_status == 'A')       //found and active
//	{
//		itemNumber = warehouse_table[ind].item_number;              //get number
//	}
//	//look for item number at store
//	if (addItemToOrderByNumber(itemNumber))
//	{
//		return true;
//	}
//	return false;
//};

//TEST
//number must be validated before passing
bool addItemToOrderByNumber(int itemNumber)
{
	int storeIndex = findStoreItem(itemNumber, currentStoreNumber);
	if (storeIndex == -1 || store_inventory_table[storeIndex].item_status == 'D')           //item not found or inactive
	{
		cout << "Cannot add item. Does not exist within the store." << endl;
		return false;
	}
	else if (store_inventory_table[storeIndex].item_status == 'A')          //item found at store && active
	{
		int warehouseIndex = findWarehouseItem(itemNumber);
		string quantity;
		long long numQuantity;
		cout << "Quantity: ";
		cin.ignore();
		getline(cin, quantity);
		if (quantity.length() < g_storeupdate_txt_requested_quantity_len)        //correct length
		{
			if (validateAllNumbers)                                             //if all numbers
			{
				numQuantity = stoll(quantity);                                  //convert
			}
		}
		if (numQuantity <= store_inventory_table[storeIndex].quantity)           //sufficient stock| add to transaction
		{
			//add item number
			pendingTransaction.transaction_item_number.push_back(itemNumber);
			//add quantity
			store_inventory_table[storeIndex].quantity -= numQuantity;          //remove quantity from inventory
			pendingTransaction.transaction_item_quantity.push_back(numQuantity);
			//add price
			pendingTransaction.transaction_item_price.push_back(warehouse_table[warehouseIndex].price);
			return true;
		}
		else
		{
			cout << "Insufficient stock to add to order." << endl;
			return false;
		}
	}
};

//TEST
//bool deleteItemFromOrderbyName(string itemName)
//{
//	int itemNumber;
//	//search for item number
//	//find item at warehouse to get details
//	int ind = findWarehouseItemByItemName(itemName);
//	if (ind != -1 && warehouse_table[ind].item_status == 'A')           //found and active
//	{
//		itemNumber = warehouse_table[ind].item_number;              //get number
//	}
//	else
//	{
//		return false;
//	}
//	//look for item number at store
//	if (deleteItemFromOrderbyNumber(itemNumber))
//	{
//		return true;
//	}
//	return false;
//};

//TEST
//assumes number has been validated before passing inside
bool deleteItemFromOrderbyNumber(int itemNumber)
{
	for (int x = 0; x < pendingTransaction.transaction_item_number.size(); x++)
	{
		if (pendingTransaction.transaction_item_number[x] == itemNumber)
		{
			pendingTransaction.transaction_item_number.erase(pendingTransaction.transaction_item_number.begin() + (x));         //hopefully works
			pendingTransaction.transaction_item_price.erase(pendingTransaction.transaction_item_price.begin() + (x));           //hopefully works
			pendingTransaction.transaction_item_quantity.erase(pendingTransaction.transaction_item_quantity.begin() + (x));      //hopefully works
			return true;
		}
	}
	return false;
};

int generateAccountNumber()
{
	int accountBase = 10000000;

	int highestAccount = 0;

	for (int i = 0; i < customer_table.size(); i++)
	{
		if (customer_table[i].account_number > highestAccount)
			highestAccount = customer_table[i].account_number;
	}

	int newAccount = 0;
	// All accounts use 10000000 as a base (10000000, 10000001, 10000002, etc)
	
	// In case this is the first account
	if (highestAccount < 10000000)
		newAccount = 10000000;
	else
		newAccount = highestAccount + 1;

	return newAccount;
}
//
//void displayOrderEntry()
//{
//	Menu orderEntryMenu;
//	orderEntryMenu.
//		"Item# 123456789  "
//}