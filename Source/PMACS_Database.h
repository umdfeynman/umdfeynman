#ifndef PMACS_DATABASE_H
#define PMACS_DATABASE_H

bool loadDatabaseIntoMemory();
bool readWarehouseItemData();
bool readStoreInventory();
bool readStoreData();
bool readCustomer();
bool readCoupon();
bool readTransaction();
bool readSequenceNumbers();
bool readConfig();
bool saveDatabaseToDisk();
bool saveWarehouseItemData();
bool saveStoreInventory();
bool saveStoreData();
bool saveCustomer();
bool saveCoupon();
bool saveTransaction();
bool saveConfig();

#endif 