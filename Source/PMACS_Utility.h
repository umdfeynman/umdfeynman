#ifndef PMACS_UTILITY_H
#define PMACS_UTLITY_H

int getSequenceNumber(int seq_index);
int getRecordLength(int rec_index);
int findStore(int store_number);
int findWarehouseItem(int item_number);
int findStoreItem(int item_number, int store_number);
int findCustomer(int account_number);
bool setCurrentCustomerNumber(int account_number);
bool setCurrentCashier(int cashier_number);
bool setCurrentStore(int store_number);
bool setCurrentItemByNumber(int item_number);
bool setCurrentItemByName(std::string item_name);
std::vector<int> getStoreItemList(int item_number);
void setSystemDate(std::string in_string);
int findCustomerByNameAddress(std::string name, std::string address);
int findWarehouseItemByItemName(std::string item_name);
int checkCoupled(int item_one_index, int item_two_index);
bool uncoupleItems(int item_one, int item_two);
bool coupleItems(int item_one, int item_two);
void addItemToOrder();
void closeAllStores();
int CouponCheck(int couponID);
bool deleteCoupon(int couponID);
void closeStore();
bool addCoupon(int couponID, int couponDiscount);
void clearItemSelections();
void assignItemsToStore();
void removeItemsFromStore();
void changeItemStatus();
void changeVendorNumber();
void changeItemDosage();
void changeItemName();
void changeItemDescription();
void changeWarehouseReorderQuantity();
void changeWarehouseReorderLevel();
void changeBasePrice();
int findWarehouseItemByItemName(std::string item_name);
void displayItemInfo();
void displayCurrentList();
void updateItemDiscount();
int generateAccountNumber();
void createAccount();
void lookupAccountByNameAddress();
void deleteItemFromOrder();
#endif