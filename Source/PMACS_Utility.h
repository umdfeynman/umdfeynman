#ifndef PMACS_UTILITY_H
#define PMACS_UTLITY_H

int getSequenceNumber(int seq_index);
int getRecordLength(int rec_index);
int findStore(int store_number);
int findWarehouseItem(int item_number);
int findStoreItem(int item_number, int store_number);
int findCustomer(int account_number);
bool setCurrentCustomer(int account_number);
std::vector<int> getStoreItemList(int item_number);
#endif