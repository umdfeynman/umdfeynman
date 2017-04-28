#ifndef PMACS_DEFINES_H
#define PMACS_DEFINES_H

// Sequence number / record length array indices
#define g_adddeletestore 0
#define g_storeupdate 1
#define g_itemreceived 2
#define g_vendororder 3 
#define g_items 4
#define g_reports 5
#define g_returnitems 6
#define g_addstoreitems 7
#define g_batchreplenish 8
#define g_onlineinvrequest 9
#define g_vendorrequest 10
#define g_leftovers 11

// Database filenames
#define g_transaction_file "transaction.db"
#define g_warehouse_file "warehouse.db"
#define g_storeinv_file "storeinv.db"
#define g_storedata_file "storedata.db"
#define g_customer_file "customer.db"
#define g_coupon_file "coupon.db"
#define g_sequence_file "sequence.db"
#define g_config_file "config.db"

// Expected types for input validation
#define g_type_int 1
#define g_type_longlong 2
#define g_type_char_any 3
#define g_type_char_letter 4
#define g_type_string_any 5
#define g_type_string_letter 6
#define g_type_double 7

// storeupdate.txt source codes wannabe enum
#define g_source_code_batch 3
#define g_source_code_online 2
#define g_source_code_add 1

// **FILE FIELD LENGTH AND POSITION**
// Positions are 0-based
// adddeletestore.txt
// 'A' records
#define g_adddeletestore_txt_a_store_number_pos 1
#define g_adddeletestore_txt_a_store_number_len 5
#define g_adddeletestore_txt_a_store_address_pos 6
#define g_adddeletestore_txt_a_store_address_len 20
#define g_adddeletestore_txt_a_store_city_name_pos 26
#define g_adddeletestore_txt_a_store_city_name_len 20
#define g_adddeletestore_txt_a_store_state_pos 46
#define g_adddeletestore_txt_a_store_state_len 2
#define g_adddeletestore_txt_a_store_zip_pos 48
#define g_adddeletestore_txt_a_store_zip_len 9
#define g_adddeletestore_txt_a_store_priority_pos 57
#define g_adddeletestore_txt_a_store_priority_len 2
// 'D' records
#define g_adddeletestore_txt_d_store_number_pos 1
#define g_adddeletestore_txt_d_store_number_len 5
#define g_adddeletestore_txt_d_store_address_pos 6
#define g_adddeletestore_txt_d_store_address_len 20
#define g_adddeletestore_txt_d_store_city_name_pos 26
#define g_adddeletestore_txt_d_store_city_name_len 20
#define g_adddeletestore_txt_d_store_state_pos 46
#define g_adddeletestore_txt_d_store_state_len 2
#define g_adddeletestore_txt_d_store_zip_pos 48
#define g_adddeletestore_txt_d_store_zip_len 9
#define g_adddeletestore_txt_d_store_priority_pos 57
#define g_adddeletestore_txt_d_store_priority_len 2
// 'I' records
#define g_adddeletestore_txt_i_item_number_pos 1
#define g_adddeletestore_txt_i_item_number_len 9
#define g_adddeletestore_txt_i_store_default_quantity_pos 10
#define g_adddeletestore_txt_i_store_default_quantity_len 10
#define g_adddeletestore_txt_i_store_reorder_level_pos 20
#define g_adddeletestore_txt_i_store_reorder_level_len 10
#define g_adddeletestore_txt_i_store_reorder_quantity_pos 30
#define g_adddeletestore_txt_i_store_reorder_quantity_len 10
// 'C' records
#define g_adddeletestore_txt_c_store_overall_item_count_pos 2
#define g_adddeletestore_txt_c_store_overall_item_count_len 4

// storeupdate.txt
#define g_storeupdate_txt_source_code_pos 1     
#define g_storeupdate_txt_source_code_len 1
#define g_storeupdate_txt_store_number_pos 2       
#define g_storeupdate_txt_store_number_len 5
#define g_storeupdate_txt_store_priority_pos 7
#define g_storeupdate_txt_store_priority_len 2
#define g_storeupdate_txt_item_number_pos 9   
#define g_storeupdate_txt_item_number_len 9
#define g_storeupdate_txt_requested_quantity_pos 18
#define g_storeupdate_txt_requested_quantity_len 10

// itemreceived.txt
#define g_itemreceived_txt_vendor_number_pos 1
#define g_itemreceived_txt_vendor_number_len 4
#define g_itemreceived_txt_item_number_pos 5
#define g_itemreceived_txt_item_number_len 9
#define g_itemreceived_txt_quantity_received_pos 14
#define g_itemreceived_txt_quantity_received_len 10
// Note:  There is also a 10-digit expiration date but this is 
// not necessary for our project.

// vendororder.txt
#define	g_vendororder_txt_vendor_number_pos 1
#define	g_vendororder_txt_vendor_number_len 4
#define	g_vendororder_txt_item_number_pos 5
#define	g_vendororder_txt_item_number_len 9
#define	g_vendororder_txt_incoming_quantity_pos 14
#define	g_vendororder_txt_incoming_quantity_len 10

// items.txt
#define	g_items_txt_d_item_number_pos 1
#define	g_items_txt_d_item_number_len 9
#define	g_items_txt_a_item_number_pos 1
#define	g_items_txt_a_item_number_len 9
#define	g_items_txt_a_item_name_pos 10
#define	g_items_txt_a_item_name_len 20
#define	g_items_txt_a_item_description_pos 30
#define	g_items_txt_a_item_description_len 100
#define	g_items_txt_a_item_dosage_pos 130
#define	g_items_txt_a_item_dosage_len 20
#define	g_items_txt_a_warehouse_reorder_level_pos 150
#define	g_items_txt_a_warehouse_reorder_level_len 10
#define	g_items_txt_a_vendor_number_pos 160
#define	g_items_txt_a_vendor_number_len 4
#define	g_items_txt_a_warehouse_reorder_quantity_pos 164
#define	g_items_txt_a_warehouse_reorder_quantity_len 10
#define	g_items_txt_a_expected_delivery_time_pos 174
#define	g_items_txt_a_expected_delivery_time_len 20
#define	g_items_txt_c_item_number_pos 1
#define	g_items_txt_c_item_number_len 9
#define	g_items_txt_c_item_name_pos 10
#define	g_items_txt_c_item_name_len 20
#define	g_items_txt_c_item_description_pos 30
#define	g_items_txt_c_item_description_len 100
#define	g_items_txt_c_item_dosage_pos 130
#define	g_items_txt_c_item_dosage_len 20
#define	g_items_txt_c_warehouse_reorder_level_pos 150
#define	g_items_txt_c_warehouse_reorder_level_len 10
#define	g_items_txt_c_vendor_number_pos 160
#define	g_items_txt_c_vendor_number_len 4
#define	g_items_txt_c_warehouse_reorder_quantity_pos 164
#define	g_items_txt_c_warehouse_reorder_quantity_len 10
#define	g_items_txt_c_expected_delivery_time_pos 174
#define	g_items_txt_c_expected_delivery_time_len 20
#define g_items_txt_n_item_action_count_pos 3
#define g_items_txt_n_item_action_count_len 4

// reports.txt
#define g_reports_txt_item_number_pos 1
#define g_reports_txt_item_number_len 9

// returnitems.txt			
#define	g_returnitems_txt_vendor_number_pos 0
#define	g_returnitems_txt_vendor_number_len 4
#define	g_returnitems_txt_item_number_pos 4
#define	g_returnitems_txt_item_number_len 9
#define	g_returnitems_txt_incoming_quantity_pos 13
#define	g_returnitems_txt_incoming_quantity_len 10

// addstoreitems.txt			
#define g_addstoreitems_txt_store_number_pos 1
#define g_addstoreitems_txt_store_number_len 5
#define g_addstoreitems_txt_store_priority_pos 6
#define g_addstoreitems_txt_store_priority_len 2
#define g_addstoreitems_txt_item_number_pos 8
#define g_addstoreitems_txt_item_number_len 9
#define g_addstoreitems_txt_requested_quantity_pos 17
#define g_addstoreitems_txt_requested_quantity_len 10

// batchreplenish.txt
#define g_batchreplenish_txt_store_number_pos 1
#define g_batchreplenish_txt_store_number_len 5
#define g_batchreplenish_txt_store_priority_pos 6
#define g_batchreplenish_txt_store_priority_len 2
#define g_batchreplenish_txt_item_number_pos 8    
#define g_batchreplenish_txt_item_number_len 9
#define g_batchreplenish_txt_requested_quantity_pos 17
#define g_batchreplenish_txt_requested_quantity_len 10

// onlineinvrequest.txt
#define g_onlineinvrequest_txt_store_number_pos 1
#define g_onlineinvrequest_txt_store_number_len 5
#define g_onlineinvrequest_txt_store_priority_pos 6    
#define g_onlineinvrequest_txt_store_priority_len 2
#define g_onlineinvrequest_txt_item_number_pos 8 
#define g_onlineinvrequest_txt_item_number_len 9
#define g_onlineinvrequest_txt_requested_quantity_pos 17
#define g_onlineinvrequest_txt_requested_quantity_len 10

// leftovers.txt
#define g_leftovers_txt_store_number_pos 1
#define g_leftovers_txt_store_number_len 5
#define g_leftovers_txt_store_priority_pos 6    
#define g_leftovers_txt_store_priority_len 2
#define g_leftovers_txt_item_number_pos 8 
#define g_leftovers_txt_item_number_len 9
#define g_leftovers_txt_requested_quantity_pos 17
#define g_leftovers_txt_requested_quantity_len 10

#endif