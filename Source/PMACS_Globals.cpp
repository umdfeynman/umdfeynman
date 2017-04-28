#include <vector>
#include "PMACS_Logger.h"
#include "PMACS_Defines.h"
#include "PMACS_String.h"
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"
#include "PMACS_File.h"
#include "PMACS_Date.h"
#include "PMACS_Data_Structures.h"
#include "PMACS_Utility.h"
#include "PMACS_Database.h"
#include "PMACS_Input.h"
std::vector<WarehouseItemData> warehouse_table;
std::vector<StoreInventory> store_inventory_table;
std::vector<StoreData> store_data_table;
std::vector<Customer> customer_table;
std::vector<Coupon> coupon_table;
std::vector<Transaction> transaction_table;
Logger Plog("PMACS_Log.txt");
int sequenceNumber[12];
int recordLength[12] = { 59, 27, 33, 23, 194, 9, 23, 27, 27, 27, 23, 27 };
// AddDeleteStore = 1 + 5 + 20 + 20 + 2 + 9 + 2 = 59
// StoreUpdate = 1 + 5 + 2 + 9 + 10 = 27
// ItemReceived = 4 + 9 + 10 + 10 = 33
// VendorOrder = 4 + 9 + 10 = 23
// Items = 1 + 9 + 20 + 100 + 20 + 10 + 4 + 10 + 20 = 194
// Reports = 9
// ReturnItems = Same as VendorOrder = 23
// AddStoreItems = Same as StoreUpdate = 27
// BatchReplenish = Same as StoreUpdate = 27
// OnlineInvRequest = Same as StoreUpdate = 27
// VendorRequest = Same as VendorOrder = 23
// LeftOvers = Same as StoreUpdate = 27
string fileName[12] = { "adddeletestore.txt", "storeupdate.txt", "itemreceived.txt", "vendororder.txt", "items.txt", "reports.txt",
"returnitems.txt",	"addstoreitems.txt", "batchreplenish.txt", "onlineinvrequest.txt", "vendorrequest.txt", "leftovers.txt" };
int currentCustomerNumber = -1;
int currentStoreNumber = -1;
int currentCashierNumber = -1;
int currentCustomerIndex = -1;
int currentStoreIndex = -1;
int currentItemNumber = -1;
int currentItemIndex = -1;
Date systemDate;
std::vector<int> currentItemList; // Item indices in warehouse_table
int currentItemListSize = 0; // Size of currentItemList
Transaction pendingTransaction;