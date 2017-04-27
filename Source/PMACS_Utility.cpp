#include "PMACS_Globals.h"
#include "PMACS_Menu.h"
#include "PMACS_String.h"

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
		temp.displayDialogNoReturn("Failed to select item, item not found");
		return false;
	}

	currentItemNumber = item_number;
	currentItemIndex = findResult;

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

bool setCurrentItemByName(std::string item_name)
{
	Menu temp;

	int findResult = findWarehouseItemByItemName(item_name);
	if (findResult == -1)
	{
		temp.displayDialogNoReturn("Failed to select item, item not found");
		return false;
	}

	currentItemNumber = warehouse_table[findResult].item_number;
	currentItemIndex = findResult;

	return true;
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
void closeStore()
{
	store_data_table[currentStoreIndex].store_status = 'C';
}

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
			else			//no match
			{
				return -1;
			}
		}
	}
}

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



