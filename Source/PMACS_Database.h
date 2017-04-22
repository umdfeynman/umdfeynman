#include<string>
#include<vector>
#ifndef PMACS_DATABASE_H
#define PMACS_DATABASE_H

bool readWarehouseItemData();
bool readStoreInventory();
bool readStoreData();
bool readCustomer();
bool readCoupon();
bool readTransaction();
bool saveWarehouseItemData();
bool saveStoreInventory();
bool saveStoreData();
bool saveCustomer();
bool saveCoupon();
bool saveTransaction();

#endif 