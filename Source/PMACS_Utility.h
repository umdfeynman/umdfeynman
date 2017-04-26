#ifndef PMACS_UTILITY_H
#define PMACS_UTLITY_H

int getSequenceNumber(int seq_index);
int getRecordLength(int rec_index);
int findStore(int store_number);
int findWarehouseItem(int item_number);
int findStoreItem(int item_number);
<<<<<<< HEAD
int findCustomer(int account_number);
bool setCurrentCustomer(int account_number);
=======
int findStoreItem(int item_number, int storeNumber);
vector<int> getStoreItemList(int item_number);

>>>>>>> af0aa398b0bf1bbe56cf615a8e1c37c016751a63
#endif