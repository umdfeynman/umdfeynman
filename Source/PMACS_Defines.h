#ifndef PMACS_DEFINES_H
#define PMACS_DEFINES_H

// Positions are 0-based

// adddeletestore.txt
// 'A' records
#define adddeletestore_txt_a_store_number_pos 1
#define adddeletestore_txt_a_store_number_len 5
#define adddeletestore_txt_a_store_address_pos 6
#define adddeletestore_txt_a_store_address_len 20
#define adddeletestore_txt_a_store_city_name_pos 26
#define adddeletestore_txt_a_store_city_name_len 20
#define adddeletestore_txt_a_store_state_pos 46
#define adddeletestore_txt_a_store_state_len 2
#define adddeletestore_txt_a_store_zip_pos 48
#define adddeletestore_txt_a_store_zip_len 9
#define adddeletestore_txt_a_store_priority_pos 57
#define adddeletestore_txt_a_store_priority_len 2
// 'D' records
#define adddeletestore_txt_d_store_number_pos 1
#define adddeletestore_txt_d_store_number_len 5
#define adddeletestore_txt_d_store_address_pos 6
#define adddeletestore_txt_d_store_address_len 20
#define adddeletestore_txt_d_store_city_name_pos 26
#define adddeletestore_txt_d_store_city_name_len 20
#define adddeletestore_txt_d_store_state_pos 46
#define adddeletestore_txt_d_store_state_len 2
#define adddeletestore_txt_d_store_zip_pos 48
#define adddeletestore_txt_d_store_zip_len 9
#define adddeletestore_txt_d_store_priority_pos 57
#define adddeletestore_txt_d_store_priority_len 2
// 'I' records
#define adddeletestore_txt_i_item_number_pos 1
#define adddeletestore_txt_i_item_number_len 9
#define adddeletestore_txt_i_store_default_quantity_pos 10
#define adddeletestore_txt_i_store_default_quantity_len 10
#define adddeletestore_txt_i_store_reorder_level_pos 20
#define adddeletestore_txt_i_store_reorder_level_len 10
#define adddeletestore_txt_i_store_reorder_quantity_pos 30
#define adddeletestore_txt_i_store_reorder_quantity_len 10
// 'C' records
#define adddeletestore_txt_c_store_overall_item_count_pos 1
#define adddeletestore_txt_c_store_overall_item_count_len 4

// storeupdate.txt
#define storeupdate_txt_source_code_pos 1     
#define storeupdate_txt_source_code_len 1
#define storeupdate_txt_store_number_pos 2       
#define storeupdate_txt_store_number_len 5
#define storeupdate_txt_store_priority_pos 7
#define storeupdate_txt_store_priority_len 2
#define storeupdate_txt_item_number_pos 9   
#define storeupdate_txt_item_number_len 9
#define storeupdate_txt_requested_quantity_pos 18
#define storeupdate_txt_requested_quantity_len 10

// itemreceived.txt
#define itemreceived_txt_vendor_number_pos 1
#define itemreceived_txt_vendor_number_len 4
#define itemreceived_txt_item_number_pos 5
#define itemreceived_txt_item_number_len 9
#define itemreceived_txt_quantity_received_pos 14
#define itemreceived_txt_quantity_received_len 10
// Note:  There is also a 10-digit expiration date but this is 
// not necessary for our project.

// vendororder.txt
#define	vendororder_txt_vendor_number_pos 1
#define	vendororder_txt_vendor_number_len 4
#define	vendororder_txt_item_number_pos 5
#define	vendororder_txt_item_number_len 9
#define	vendororder_txt_incoming_quantity_pos 14
#define	vendororder_txt_incoming_quantity_len 10

// items.txt
#define	items_txt_d_item_number_pos 1
#define	items_txt_d_item_number_len 9
#define	items_txt_a_item_number_pos 1
#define	items_txt_a_item_number_len 9
#define	items_txt_a_item_name_pos 10
#define	items_txt_a_item_name_len 20
#define	items_txt_a_item_description_pos 30
#define	items_txt_a_item_description_len 100
#define	items_txt_a_item_dosage_pos 130
#define	items_txt_a_item_dosage_len 20
#define	items_txt_a_warehouse_reorder_level_pos 150
#define	items_txt_a_warehouse_reorder_level_len 10
#define	items_txt_a_vendor_number_pos 160
#define	items_txt_a_vendor_number_len 4
#define	items_txt_a_warehouse_reorder_quantity_pos 164
#define	items_txt_a_warehouse_reorder_quantity_len 10
#define	items_txt_a_expected_delivery_time_pos 174
#define	items_txt_a_expected_delivery_time_len 20
#define	items_txt_c_item_number_pos 1
#define	items_txt_c_item_number_len 9
#define	items_txt_c_item_name_pos 10
#define	items_txt_c_item_name_len 20
#define	items_txt_c_item_description_pos 30
#define	items_txt_c_item_description_len 100
#define	items_txt_c_item_dosage_pos 130
#define	items_txt_c_item_dosage_len 20
#define	items_txt_c_warehouse_reorder_level_pos 150
#define	items_txt_c_warehouse_reorder_level_len 10
#define	items_txt_c_vendor_number_pos 160
#define	items_txt_c_vendor_number_len 4
#define	items_txt_c_warehouse_reorder_quantity_pos 164
#define	items_txt_c_warehouse_reorder_quantity_len 10
#define	items_txt_c_expected_delivery_time_pos 174
#define	items_txt_c_expected_delivery_time_len 20

// reports.txt
#define reports_txt_item_number_pos 1
#define reports_txt_item_number_len 9

// returnitems.txt			
#define	returnitems_txt_vendor_number_pos 1
#define	returnitems_txt_vendor_number_len 4
#define	returnitems_txt_item_number_pos 5
#define	returnitems_txt_item_number_len 9
#define	returnitems_txt_incoming_quantity_pos 14
#define	returnitems_txt_incoming_quantity_len 10

// addstoreitems.txt			
#define addstoreitems_txt_store_number_pos 1
#define addstoreitems_txt_store_number_len 5
#define addstoreitems_txt_store_priority_pos 6
#define addstoreitems_txt_store_priority_len 2
#define addstoreitems_txt_item_number_pos 8
#define addstoreitems_txt_item_number_len 9
#define addstoreitems_txt_requested_quantity_pos 17
#define addstoreitems_txt_requested_quantity_len 10

// batchreplenish.txt
#define batchreplenish_txt_store_number_pos 1
#define batchreplenish_txt_store_number_len 5
#define batchreplenish_txt_store_priority_pos 6
#define batchreplenish_txt_store_priority_len 2
#define batchreplenish_txt_item_number_pos 8    
#define batchreplenish_txt_item_number_len 9
#define batchreplenish_txt_requested_quantity_pos 17
#define batchreplenish_txt_requested_quantity_len 10

// onlineinvrequest.txt
#define onlineinvrequest_txt_store_number_pos 1
#define onlineinvrequest_txt_store_number_len 5
#define onlineinvrequest_txt_store_priority_pos 6    
#define onlineinvrequest_txt_store_priority_len 2
#define onlineinvrequest_txt_item_number_pos 8 
#define onlineinvrequest_txt_item_number_len 9
#define onlineinvrequest_txt_requested_quantity_pos 17
#define onlineinvrequest_txt_requested_quantity_len 10

#endif