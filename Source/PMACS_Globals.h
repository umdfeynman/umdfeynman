#ifndef PMACS_GLOBALS_H
#define PMACS_GLOBALS_H
#include <vector>
#include "PMACS_Data_Structures.h"
#include "PMACS_Logger.h"
#include "PMACS_Date.h"
extern std::vector<WarehouseItemData> warehouse_table;
extern std::vector<StoreInventory> store_inventory_table;
extern std::vector<StoreData> store_data_table;
extern std::vector<Customer> customer_table;
extern std::vector<Coupon> coupon_table;
extern std::vector<Transaction> transaction_table;
extern Logger Plog;
extern int sequenceNumber[12];
extern int recordLength[12];
extern string fileName[12];
extern Date systemDate;
extern int currentCustomerNumber;
extern int currentCustomerIndex;
extern int currentStoreNumber;
extern int currentStoreIndex;
extern int currentCashierNumber;

#endif