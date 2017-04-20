#ifndef PMACS_DATA_STRUCTURES_H
#define PMACS_DATA_STRUCTURES_H

// All values set to -1, "" or '' are to enable us to determine if the value is properly being set.
// Any value set otherwise is a default value

class WarehouseItemData
{   
    char item_status = 'A'; // 'D' or 'A'
	int item_number = -1; // Key
    int vendor_number = -1;
    std::string item_dosage = ""; // mg
    int coupled_item_number = -1;
    int item_discount_percent = 0;
    std::string item_name = "";
	std::string item_description = "";
    int reorder_quantity = -1;  // Default reorder amount
	int reorder_level = -1;  // When warehouse quantity gets below this, order reorder_quantity
    std::string expected_delivery_time = "";  // Number of days will take be back in stock
    int quantity = -1;
	double price = 5.0;
};

class StoreInventory
{	
    char item_status = 'A'; 'D' or 'A'
	int item_number = -1; // can pull item_data information using this field, Key 1
    int store_number = -1; // Key 2
    int quantity = -1; // Quantity on-hand
    int high_threshold = -1; // Low reorder level threshold
    int low_threshold = -1; // High reorder level threshold
    int accustock_pct_change = 0; // Change applied based on H/L
	bool accustock_direction = 0; T = H, F = L
    int accustock_frequency = 0; // # of days elapsed
    //int default_quantity = 0;
    int reorder_level = -1;
    int reorder_quantity = -1;
};

class StoreData
{
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
    int account_number = -1;
    std::string address = "";
    std::string name = "";   
    std::vector<int> cust_items;  // Same index as item_dates
    std::vector<std::string> item_dates; // Same index as cust_items	
};

class Coupon
{
    int coupon_number = -1;
    int discount_pct = 0;
}

class Transactions
{
    int order_number = -1;  // Key 1
    int originating_cashier_number = -1;
    int approving_cashier_number = -1;
    int store_number = -1;
    std::string transaction_date = "";
    int account_number = -1;
    int discount_pct = -1;  // Discount percent from coupon
    double grand_total = -1.0;  // Transaction total after all discounts applied, for easy generation of grand totals in reporting
    std::vector<int> transaction_item;
    std::vector<int> transaction_item_quantity;
    std::vector<double> transaction_item_price;  // Item price after individual item discount 
}

class Add_Delete_Store_Event
{
    //Date date;  // Per Steiner:  Date not used
    char action_type; 'A' 'D' 'I' 'C'
    int store_id;
    std::string street_address
    std::string city_name
    std::string state_name
    int zip_code;
    int store_priority_level;
    int item_number;
    int store_default_quantity;
    int store_reorder_level;
    int store_reorder_quantity;
    int store_overall_item_count;   
}

class Update_Item_Data_Event
{
    char action_type; 'A' 'C' 'D' 'N'
    int item_number;
    std::string item_name;
    std::string item_description;
    std::string item_dosage;
    int warehouse_reorder_level;
    int vendor_number;
    int warehouse_reorder_quantity;
    std::string expected_delivery_time;
    char specific action_designation; // {A, D, C} immediately following 'N'
    int update_item_action_count; // Number of rows for each 'A' 'C' or 'D'
}

class Change_Data_Event
{
    std::string action_type; 'A' 'C' 'D' 'N'
    std::string item_number;
    std::string item_name;
    std::string item_description;
    std::string item_dosage;
    std::string warehouse_reorder_level;
    std::string vendor_number;
    std::string warehouse_reorder_quantity;
    std::string expected_delivery_time;
    std::string specific action_designation; // {A, D, C} immediately following 'N'
    std::string update_item_action_count; // Number of rows for each 'A' 'C' or 'D'
}

class Merge_Vendor_Return_Event
{
    int vendor_number;
    int item_number;
    int incoming_quantity;
}

class Merge_Add_Online_Batch_Event
{
    char source_code;
    int store_number;
    int store_priority;
    int item_number;
    int requested_quantity; 
}

// Vendor for vector of vendors with item sublist as vector
class vendor_report_vendor
{
    int vendor_number;
    std::vector<warehouse_item_level> vendor_report_items
}

#endif