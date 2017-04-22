#include <string>
#include <vector>
#ifndef PMACS_DATA_STRUCTURES_H
#define PMACS_DATA_STRUCTURES_H

// All values set to -1, "" or '' are to enable us to determine if the value is properly being set.
// Any value set otherwise is a default value

class WarehouseItemData
{   
public:
    char item_status = 'A'; // 'D' or 'A'
	int item_number = -1; // Key
    int vendor_number = -1;
    std::string item_dosage = ""; // mg
    int coupled_item_number = -1;
    int item_discount_percent = 0;
    std::string item_name = "";
	std::string item_description = "";
    long long reorder_quantity = -1;  // Default reorder amount
	long long reorder_level = -1;  // When warehouse quantity gets below this, order reorder_quantity
    std::string expected_delivery_time = "";  // Number of days will take be back in stock
    long long quantity = -1;
	double price = 5.0;
};

class StoreInventory
{	
public:
    char item_status = 'A'; //'D' or 'A'
	int item_number = -1; // can pull item_data information using this field, Key 1
    int store_number = -1; // Key 2
    long long quantity = -1; // Quantity on-hand
    long long high_threshold = -1; // Low reorder level threshold
    long long low_threshold = -1; // High reorder level threshold
    int accustock_pct_change = 0; // Change applied based on H/L
	bool accustock_direction = 0; //T = H, F = L
    int accustock_frequency = 0; // # of days elapsed
    //int default_quantity = 0;
    long long reorder_level = -1;
    long long reorder_quantity = -1;
};

class StoreData
{
public:
    char store_status = 'O'; // D, O, C - Deactivated, open, or closed
    int store_priority = -1;
    int store_number = -1; // Key 1
	std::string street_address = "";
	std::string city_name = "";
	std::string state_name = "";
	int zip_code = -1;
};

class Customer
{
public:
    int account_number = -1;
    std::string address = "";
    std::string name = "";   
    std::vector<int> cust_items;  // Same index as item_dates
    std::vector<int> item_dates; // Same index as cust_items	
};

class Coupon
{
public:
    int coupon_number = -1;
    int discount_pct = 0;
};

class Transaction
{
public:
    int order_number = -1;  // Key 1
    int originating_cashier_number = -1;
    int approving_cashier_number = -1;
    int store_number = -1;
    std::string transaction_date = "";
    int account_number = -1;
    int discount_pct = -1;  // Discount percent from coupon
    double grand_total = -1.0;  // Transaction total after all discounts applied, for easy generation of grand totals in reporting
    std::vector<int> transaction_item_number;
    std::vector<long long> transaction_item_quantity;
    std::vector<double> transaction_item_price;  // Item price after individual item discount 
};

class Add_Delete_Store_Event
{
public:
    //Date date;  // Per Steiner:  Date not used
    char action_type; // 'A' 'D' 'I' 'C'
    int store_id;
	std::string street_address;
	std::string city_name;
	std::string state_name;
    int zip_code;
    int store_priority_level;
    int item_number;
    long long store_default_quantity;
    long long store_reorder_level;
    long long store_reorder_quantity;
    int store_overall_item_count;   
};

class Update_Item_Data_Event
{
public:
    char action_type; //'A' 'C' 'D' 'N'
    int item_number;
    std::string item_name;
    std::string item_description;
    std::string item_dosage;
    long long warehouse_reorder_level;
    int vendor_number;
    long long warehouse_reorder_quantity;
    std::string expected_delivery_time;
    char specific_action_designation; // {A, D, C} immediately following 'N'
    int update_item_action_count; // Number of rows for each 'A' 'C' or 'D'
};

class Change_Data_Event
{
public:
    std::string action_type; //'A' 'C' 'D' 'N'
    std::string item_number;
    std::string item_name;
    std::string item_description;
    std::string item_dosage;
    std::string warehouse_reorder_level;
    std::string vendor_number;
    std::string warehouse_reorder_quantity;
    std::string expected_delivery_time;
    std::string specific_action_designation; // {A, D, C} immediately following 'N'
    std::string update_item_action_count; // Number of rows for each 'A' 'C' or 'D'
};

class Merge_Vendor_Return_Event
{
public:
    int vendor_number;
    int item_number;
    long long incoming_quantity;
};

class Merge_Add_Online_Batch_Event
{
public:
    int source_code;  // Uses #defines source_code_add, source_code_online, source_code_batch
    //char source_code;
    int store_number;
    int store_priority;
    int item_number;
    long long requested_quantity; 
};

// Vendor for vector of vendors with item sublist as vector
class vendor_report_vendor
{
public:
    int vendor_number;
	std::vector<WarehouseItemData> vendor_report_items;
};

#endif