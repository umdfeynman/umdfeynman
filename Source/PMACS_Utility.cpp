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

int findCoupon(int coupon_number)
{
	for (int i = 0; i < coupon_table.size(); i++)
	{
		if (coupon_table[i].coupon_number == coupon_number)
			return i;
	}
	return -1;
}

bool setCurrentCustomerNumber(int account_number)
{
	Menu temp;
	temp.setMenuName("setCurrentCustomerNumber");

	int findResult = findCustomer(account_number);
	if (findResult == -1)
	{
		return false;
	}

	currentCustomerNumber = account_number;
	currentCustomerIndex = findResult;

	return true;
}

bool setCurrentCoupon(int coupon_number)
{
	Menu temp;
	temp.setMenuName("setCurrentCoupon");

	int findResult = findCoupon(coupon_number);
	if (findResult == -1)
	{
		return false;
	}

	currentCouponIndex = findResult;

	return true;
}


bool setCurrentStore(int store_number)
{
	Menu temp;
	temp.setMenuName("setCurrentStore");

	int findResult = findStore(store_number);
	if (findResult == -1)
	{
		//temp.displayDialogNoReturn("Failed to select store, store not found");
		return false;
	}

	currentStoreNumber = store_number;
	currentStoreIndex = findResult;

	return true;
}

bool setCurrentItemByNumber(int item_number)
{
	Menu temp;
	temp.setMenuName("setCurrentItemByNumber");

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
	temp.setMenuName("setCurrentItemByName");

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
	temp.setMenuName("clearItemSelections");

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
	for (int i = 0; i < customer_table.size(); i++)
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
	if (itemIndex == -1)
	{
		Plog.logError("getCoupledItem", "Failed to find item at warehouse");
		return -1;
	}	
	
	if (warehouse_table[itemIndex].coupled_item_number == -1)
		return -1;	
	
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
	Menu temp;
	temp.setMenuName("coupleItems");
		
	int itemOneIndex = findWarehouseItem(item_one);
	int itemTwoIndex = findWarehouseItem(item_two);
	int isCoupled;

	if (itemOneIndex == -1 || itemTwoIndex == -1)
	{
		temp.displayDialogNoReturn("Failed to find item at warehouse");
		return false;
	}

	isCoupled = checkCoupled(itemOneIndex, itemTwoIndex); // check if items are coupled

	if (isCoupled != -1) // if items are already coupled together
	{
		temp.displayDialogNoReturn("One or both items are already coupled"); 
		return false;
	}
	else if (isCoupled == -1) // if items are not coupled together
	{
		warehouse_table[itemOneIndex].coupled_item_number = warehouse_table[itemTwoIndex].item_number;
		warehouse_table[itemTwoIndex].coupled_item_number = warehouse_table[itemOneIndex].item_number;
	}
	return true;
}

//TEST
bool uncoupleItems(int item_one, int item_two)
{
	Menu temp;
	temp.setMenuName("assignItemsToAllStores");

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
	temp.setMenuName("assignItemsToAllStores");

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
	temp.setMenuName("assignItemsToStore");
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
	temp.setMenuName("removeItemsFromStore");
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
	temp.setMenuName("removeItemsFromAllStores");
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
	temp.setMenuName("changeItemStatus");
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
	temp.setMenuName("changeVendorNumber");
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
	temp.setMenuName("changeItemDosage");
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
	temp.setMenuName("changeItemName");
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
	temp.setMenuName("changeItemDescription");
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
	temp.setMenuName("changeWarehouseReorderQuantity");
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
	temp.setMenuName("changeWarehouseReorderLevel");
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
	temp.setMenuName("changeBasePrice");
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
	temp.setMenuName("displayItemInfo");
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
	temp.setMenuName("displayCurrentList");

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
	temp.setMenuName("updateItemDiscount");
	
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
}

//TEST
//create account and return index. |-1 return to previous menu| 0 account not created/false
void createAccount()
{
	Menu temp;
	temp.setMenuName("createAccount");
	
	Customer newCust;

	int accID = generateAccountNumber();
	newCust.account_number = accID;
	newCust.name = temp.displayDialogGetEntryString("Please enter the customer name (30 chars):", 30);
	newCust.address = temp.displayDialogGetEntryString("Please enter the customer address (100 chars):", 100);
			
	//add to table
	customer_table.push_back(newCust);

	setCurrentCustomerNumber(accID);	
}

void lookupAccountByNameAddress()
{
	Menu temp;
	temp.setMenuName("lookupAccountByNameAddress");

	std::string name = temp.displayDialogGetEntryString("Please enter the customer name (30 chars):", 30);
	std::string address = temp.displayDialogGetEntryString("Please enter the customer address (100 chars):", 100);
	
	int findResult = findCustomerByNameAddress(name, address);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("No customer with that name and address was found");
		return;
	}

	setCurrentCustomerNumber(customer_table[findResult].account_number);
}

//int findCustomerByNameAddress(std::string name, std::string address)
//{
//	for (int i = 0; i < customer_table.size(); i++)
//	{
//		std::string trimmedName = trimTrailingLeadingSpaces(name);
//		std::string trimmedAddress = trimTrailingLeadingSpaces(address);
//		std::string sanitizedName = upperCase(trimmedName);
//		std::string sanitizedAddress = upperCase(trimmedAddress);
//
//		if (customer_table[i].name == name && customer_table[i].address == address)
//			return i;
//	}
//	return -1;
//}

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
void addItemToOrder()
{
	Menu temp;
	temp.setMenuName("addItemToOrder");

	int numOrderItems = 0;
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
		numOrderItems++;

	if (numOrderItems >= 5)
	{
		temp.displayDialogNoReturn("Error - order already has 5 items");
		return;
	}

	int itemNumber = temp.displayDialogGetEntryInt("Please enter the item number to add (9 digits):", 9);
	if (itemNumber == -1)
		return;

	int warehouseIndex = findWarehouseItem(itemNumber);
	if (warehouseIndex == -1)
	{
		temp.displayDialogNoReturn("Error - no item with number " + std::to_string(itemNumber) + " exists");
		return;
	}
			
	int storeIndex = findStoreItem(itemNumber, currentStoreNumber);
	if (storeIndex == -1 || store_inventory_table[storeIndex].item_status == 'D')           //item not found or inactive
	{
		temp.displayDialogNoReturn("Error - no item with number " + std::to_string(itemNumber) + " exists at store " + std::to_string(currentStoreNumber));
		return;
	}
	else if (store_inventory_table[storeIndex].item_status == 'A')          //item found at store && active
	{		
		long long desiredQuantity = 0;
		desiredQuantity = temp.displayDialogGetEntryLongLong("Please enter the quantity to add (10 digits):");
		if (desiredQuantity == -1)
			return;

		if (desiredQuantity <= store_inventory_table[storeIndex].quantity)           //sufficient stock| add to transaction
		{
			//add item number
			pendingTransaction.transaction_item_number.push_back(itemNumber);
			//add quantity
			store_inventory_table[storeIndex].quantity -= desiredQuantity;          //remove quantity from inventory
			pendingTransaction.transaction_item_quantity.push_back(desiredQuantity);
			//add price
			pendingTransaction.transaction_item_price.push_back(warehouse_table[warehouseIndex].price);
						
			addCoupledItem(itemNumber);

			return;
		}
		else
		{
			temp.displayDialogNoReturn("Error - insufficient stock of " + std::to_string(itemNumber) + " exists at store " + std::to_string(currentStoreNumber));
			return;
		}
	}
}

void addCoupledItem(int item_number)
{
	Menu temp;
	temp.setMenuName("addCoupledItem");

	// Check to see if coupled item exists
	int coupledResult = getCoupledItemIndex(item_number);
	if (coupledResult == -1)
		return;
		
	char addCoupledResponse = temp.displayDialogGetEntryChar("Coupled item [" + std::to_string(warehouse_table[coupledResult].item_number) + "] + NAME [" + warehouse_table[coupledResult].item_name + "] DOSAGE [" + warehouse_table[coupledResult].item_dosage + "] exists, add to order (Y/N)?");
	if (addCoupledResponse != 'Y' || addCoupledResponse != 'y')
		return;

	int numOrderItems = 0;
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
		numOrderItems++;

	if (numOrderItems >= 5)
	{
		temp.displayDialogNoReturn("Error - order already has 5 items");
		return;
	}

	int itemNumber = warehouse_table[coupledResult].item_number;
	if (itemNumber == -1)
		return;

	int warehouseIndex = findWarehouseItem(itemNumber);
	if (warehouseIndex == -1)
	{
		temp.displayDialogNoReturn("Error - no item with number " + std::to_string(itemNumber) + " exists");
		return;
	}

	int storeIndex = findStoreItem(itemNumber, currentStoreNumber);
	if (storeIndex == -1 || store_inventory_table[storeIndex].item_status == 'D')           //item not found or inactive
	{
		temp.displayDialogNoReturn("Error - no item with number " + std::to_string(itemNumber) + " exists at store " + std::to_string(currentStoreNumber));
		return;
	}
	else if (store_inventory_table[storeIndex].item_status == 'A')          //item found at store && active
	{
		long long desiredQuantity = 0;
		desiredQuantity = temp.displayDialogGetEntryLongLong("Please enter the quantity to add (10 digits):");
		if (desiredQuantity == -1)
			return;

		if (desiredQuantity <= store_inventory_table[storeIndex].quantity)           //sufficient stock| add to transaction
		{
			//add item number
			pendingTransaction.transaction_item_number.push_back(itemNumber);
			//add quantity
			store_inventory_table[storeIndex].quantity -= desiredQuantity;          //remove quantity from inventory
			pendingTransaction.transaction_item_quantity.push_back(desiredQuantity);
			//add price
			pendingTransaction.transaction_item_price.push_back(warehouse_table[warehouseIndex].price);

			return;
		}
		else
		{
			temp.displayDialogNoReturn("Error - insufficient stock of " + std::to_string(itemNumber) + " exists at store " + std::to_string(currentStoreNumber));
			return;
		}
	}
}

void checkRefills()
{
	Menu temp;
	temp.setMenuName("checkRefills");
	
	std::string refillItems;

	int refillCount = 0;

	for (int i = 0; i < customer_table[currentCustomerIndex].item_dates.size(); i++)
	{
		if (customer_table[currentCustomerIndex].item_dates[i] >= systemDate.DateCompareValue())
		{
			std::string temp_string = std::to_string(customer_table[currentCustomerIndex].cust_items[i]);
			temp_string += '\n';
			refillItems += temp_string;
			refillCount++;
		}		
	}

	if (refillCount > 0)
		temp.displayDialogNoReturn("The following items are eligible for refill:\n" + refillItems);	
}

bool submitOrder()
{

	Menu temp;
	temp.setMenuName("submitOrder");

	int numOrderItems = 0;
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
		numOrderItems++;

	if (numOrderItems < 1)
	{
		temp.displayDialogNoReturn("Error - no items on order to submit");
		return false;
	}

	int couponNumber = temp.displayDialogGetEntryInt("Please enter a coupon number (if customer has any, press Enter to skip) number to add (3 digits):", 3);
	if (couponNumber != -1)
	{
		int couponIndex = findCoupon(couponNumber);
		if (couponIndex == -1)
		{
			temp.displayDialogNoReturn("Error - no coupon with number " + std::to_string(couponNumber) + " exists");
			return false;
		}

		setCurrentCoupon(couponNumber);
	}

	// Display whole thing, ask if they want to proceed

	int verifyingCashier = temp.displayDialogGetEntryInt("Please have another cashier enter their cashier number to verify (4 digits):", 4);
	if (verifyingCashier == -1)
	{
		//Reset coupon in case it got changed
		currentCouponIndex = -1;
		return false;
	}


	if (verifyingCashier == currentCashierNumber)
	{
		temp.displayDialogNoReturn("Error - verifying cashier and originating cashier cannot be the same");
		return false;
	}

	printPrescriptionLabels();

	// Commit transactions
	
	// Check items exist at store
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
	{
		int storeIndex = findStoreItem(pendingTransaction.transaction_item_number[i], currentStoreNumber);
		if (storeIndex == -1)
		{
			temp.displayDialogNoReturn("Error - unable to find one of the items on the order at the store, bailing");
			return false;
		}
	}

	
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
	{
		int storeIndex = findStoreItem(pendingTransaction.transaction_item_number[i], currentStoreNumber);
	
		// subtract store inventory
		store_inventory_table[storeIndex].quantity -= pendingTransaction.transaction_item_quantity[i];

		// Add item to customer's history
		customer_table[currentCustomerIndex].cust_items.push_back(pendingTransaction.transaction_item_number[i]);  // store item number
		int storeDate = systemDate.ProjectDate(30);
		customer_table[currentCustomerIndex].item_dates.push_back(storeDate); // store today's date + 30 as int
	}

	pendingTransaction.originating_cashier_number = currentCashierNumber;
	pendingTransaction.approving_cashier_number = verifyingCashier;
	pendingTransaction.order_number = generateOrderNumber();
	pendingTransaction.store_number = currentStoreNumber;
	pendingTransaction.transaction_date = systemDate.GetDate();
	pendingTransaction.account_number = customer_table[currentCustomerIndex].account_number;	
	if (currentCouponIndex != -1)
		pendingTransaction.discount_pct = coupon_table[currentCouponIndex].discount_pct;
	pendingTransaction.grand_total = grandTotal;

	transaction_table.push_back(pendingTransaction);

	// Clear out pending transaction
	Transaction emptyTransaction;
	pendingTransaction = emptyTransaction;
		
	// Make sure all curr stuff cleared
	currentCashierNumber = -1;
	currentCouponIndex = -1;
	currentCustomerIndex = -1;
	currentCustomerNumber = -1;
	currentStoreIndex = -1;
	currentStoreNumber = -1;

	return true;
}

// Assumes at least 1 item in pendingTransaction
// Assumes all items added are valid
void printPrescriptionLabels()
{	
	Menu temp;
	temp.setMenuName("printPrescriptionLabels");	
	
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
	{
		int warehouseIndex = findWarehouseItem(pendingTransaction.transaction_item_number[i]);
			
		std::string temp_string = "Store#: " + std::to_string(currentStoreNumber) + "\n";
		temp_string += "Item#: " + std::to_string(pendingTransaction.transaction_item_number[i]) + "\n";
		temp_string += "Item Name: " + warehouse_table[warehouseIndex].item_name + "\n";
		temp_string += "Item Dosage: " + warehouse_table[warehouseIndex].item_name + "\n";
		temp_string += "Customer Account#: " + std::to_string(customer_table[currentCustomerIndex].account_number) + "\n";
		temp_string += "Customer Name: " + customer_table[currentCustomerIndex].name + "\n";
		temp_string += "Customer Address: " + customer_table[currentCustomerIndex].address + "\n";
		temp_string += "Quantity" + std::to_string(pendingTransaction.transaction_item_quantity[i]) + "\n";

		temp.displayDialogNoReturn("Prescription label:\n" + temp_string + "Press enter to continue\n");
	}
}


//TEST
void deleteItemFromOrder()
{
	Menu temp;
	temp.setMenuName("deleteItemFromOrder");

	int numItems = 0;
	for (int i = 0; i < pendingTransaction.transaction_item_number.size(); i++)
		numItems++;

	if (numItems == 0)
	{
		temp.displayDialogNoReturn("Error - no items on transaction to delete ");
		return;
	}

	int lineNumber = temp.displayDialogGetEntryInt("Please enter the corresponding line number to delete (1 digit):", 1);
	if (lineNumber == -1)
		return;
		
	if (lineNumber < 1 || lineNumber > numItems)
	{
		temp.displayDialogNoReturn("Error - no line number " + std::to_string(lineNumber) + " exists");
		return;
	}

	int adjustedLineNumber = lineNumber - 1; // for array index

	pendingTransaction.transaction_item_number.erase(pendingTransaction.transaction_item_number.begin() + adjustedLineNumber);         //hopefully works
	pendingTransaction.transaction_item_price.erase(pendingTransaction.transaction_item_price.begin() + adjustedLineNumber);           //hopefully works
	pendingTransaction.transaction_item_quantity.erase(pendingTransaction.transaction_item_quantity.begin() + adjustedLineNumber);      //hopefully works
	
	return;
}

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

int generateOrderNumber()
{
	int orderBase = 10000;

	int highestOrder = 0;

	for (int i = 0; i < transaction_table.size(); i++)
	{
		if (transaction_table[i].order_number > highestOrder)
			highestOrder = transaction_table[i].order_number;
	}

	int newOrder = 0;
	// All accounts use 10000000 as a base (10000000, 10000001, 10000002, etc)

	// In case this is the first account
	if (highestOrder < 10000)
		newOrder = 10000;
	else
		newOrder = highestOrder + 1;

	return newOrder;
}

void lookupAccountByNumber()
{
	Menu temp;
	temp.setMenuName("createAccount");

	int accountNumber = temp.displayDialogGetEntryInt("Please enter the customer account number (8 digits):", 8);
	
	int findResult = findCustomer(accountNumber);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("No customer with that name and address was found");
		return;
	}

	setCurrentCustomerNumber(customer_table[findResult].account_number);
}

void setSequenceNumber()
{
	Menu temp;
	temp.setMenuName("setSequenceNumber");


	std::string sequenceList = "g_adddeletestore 0\n";
	sequenceList += "g_storeupdate 1\n";
	sequenceList += "g_itemreceived 2\n";
	sequenceList += "g_vendororder 3\n";
	sequenceList += "g_items 4\n";
	sequenceList += "g_reports 5\n";
	sequenceList += "g_returnitems 6\n";
	sequenceList += "g_addstoreitems 7\n";
	sequenceList += "g_batchreplenish 8\n";
	sequenceList += "g_onlineinvrequest 9\n";
	sequenceList += "g_vendorrequest 10\n";
	sequenceList += "g_leftovers 11\n";

	int sequenceIndex = temp.displayDialogGetEntryInt("Please enter the sequence number index to alter\n" + sequenceList + ":", 1);

	if (sequenceIndex == -1)
		return;

	if (sequenceIndex > 11)
	{
		temp.displayDialogNoReturn("Invalid sequence number index");
		return;
	}
	
	int newSequenceNumber = temp.displayDialogGetEntryInt("Please enter the new sequence number " + sequenceList, 4);
	if (newSequenceNumber == -1)
		return;
	if (newSequenceNumber > 9999)
	{
		temp.displayDialogNoReturn("Invalid sequence number");
		return;
	}		
}

void coupleItem()
{
	Menu temp;
	temp.setMenuName("coupleItem");

	int coupleFirst = temp.displayDialogGetEntryInt("Please enter the first item number you wish to couple (8 digits):", 8);
	int coupleSecond = temp.displayDialogGetEntryInt("Please enter the second item number you wish to couple (8 digits):", 8);

	if (coupleFirst == -1 || coupleSecond == -1)
		return;

	bool coupleResult = coupleItems(coupleFirst, coupleSecond);

	if (coupleResult)
		temp.displayDialogNoReturn("Items coupled successfully");
	else
		temp.displayDialogNoReturn("Item couple failed");
}

void uncoupleItem()
{
	Menu temp;
	temp.setMenuName("uncoupleItem");

	int uncoupleFirst = temp.displayDialogGetEntryInt("Please enter the first item number you wish to couple (8 digits):", 8);
	int uncoupleSecond = temp.displayDialogGetEntryInt("Please enter the second item number you wish to couple (8 digits):", 8);

	if (uncoupleFirst == -1 || uncoupleSecond == -1)
		return;

	bool uncoupleResult = uncoupleItems(uncoupleFirst, uncoupleSecond);

	if (uncoupleResult)
		temp.displayDialogNoReturn("Items uncoupled successfully");
	else
		temp.displayDialogNoReturn("Item uncouple failed");
}

void addCoupon()
{
	Menu temp;
	temp.setMenuName("addCoupon");

	int couponNumber = temp.displayDialogGetEntryInt("Please enter the coupon number you wish to add (3 digits):", 3);
	
	if (couponNumber == -1)
		return;
	
	int findResult = findCoupon(couponNumber);
	if (findResult != -1)
	{
		temp.displayDialogNoReturn("That coupon number already exists, please try again");
		return;
	}

	int discountPercent = temp.displayDialogGetEntryInt("Please enter the discount percent you wish to use (3 digits):", 3);
	if (discountPercent == -1)
		return;

	if (discountPercent < 1 || discountPercent > 100)
	{
		temp.displayDialogNoReturn("Invalid discount percentage, please try again");
		return;
	}

	Coupon couponInstance;
	couponInstance.coupon_number = couponNumber;
	couponInstance.discount_pct = discountPercent;
	coupon_table.push_back(couponInstance);

	temp.displayDialogNoReturn("Coupon created successfully");
}
// TEST
void deleteCoupon()
{
	Menu temp;
	temp.setMenuName("deleteCoupon");

	int couponNumber = temp.displayDialogGetEntryInt("Please enter the coupon number you wish to delete (3 digits):", 3);

	if (couponNumber == -1)
		return;

	int findResult = findCoupon(couponNumber);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("That coupon number does not exist, please try again");
		return;
	}

	coupon_table.erase(coupon_table.begin(), coupon_table.begin() + findResult);

	temp.displayDialogNoReturn("Coupon deleted successfully");
}

//void updateItemDiscount()
//{
//	Menu temp;
//	temp.setMenuName("updateItemDiscount");
//
//	int itemNumber = temp.displayDialogGetEntryInt("Please enter the item number you wish to adjust discount on (8 digits):", 8);
//	if (itemNumber == -1)
//		return;
//
//	int findResult = findWarehouseItem(itemNumber);
//	if (findResult == -1)
//	{
//		temp.displayDialogNoReturn("That item number does not exist, please try again");
//		return;
//	}
//
//	int discountPercent = temp.displayDialogGetEntryInt("Please enter the discount percent you wish to use (3 digits):", 3);
//	if (discountPercent == -1)
//		return;
//
//	if (discountPercent < 1 || discountPercent > 100)
//	{
//		temp.displayDialogNoReturn("Invalid discount percentage, please try again");
//		return;
//	}
//	
//	warehouse_table[itemNumber].item_discount_percent = discountPercent;
//	temp.displayDialogNoReturn("Discount updated successfully");
//}

void finalizeStoreSales()
{
	store_data_table[currentStoreIndex].store_status = 'C';
}

void finalizeAllStoreSales()
{
	for (int i = 0; i < store_data_table.size(); i++)
	{
		if (store_data_table[i].store_status == 'O')
		{
			store_data_table[i].store_status = 'C';
		}
	}
}


void requestStoreInventory();

//
//void displayOrderEntry()
//{
//	Menu orderEntryMenu;
//	orderEntryMenu.
//		"Item# 123456789  "
//}