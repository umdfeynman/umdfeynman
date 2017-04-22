#include <vector>
#include "PMACS_Data_Structures.h"
#include "PMACS_Globals.h"
std::vector<WarehouseItemData> warehouse_table;
std::vector<StoreInventory> store_inventory_table;
std::vector<StoreData> store_data_table;
std::vector<Customer> customer_table;
std::vector<Coupon> coupon_table;
std::vector<Transaction> transaction_table;
Logger Plog("PMACS_Log.txt");
int sequenceNumber[12];


