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
#definestoreupdate_txt_source_code_pos       
#define storeupdate_txt_source_code_len
#define storeupdate_txt_store_number_pos        
#define storeupdate_store_number_code_len
#define storeupdate_txt_store_priority_pos      
#define storeupdate_txt_store_priority_len
#define storeupdate_txt_item_code_pos          
#define storeupdate_txt_item_code_len
#define storeupdate_txt_requested_quantity_pos       
#define storeupdate_txt_requested_quantity_len

// itemreceived.txt

// vendororder.txt

// items.txt

/*			
					
					
					
			returnitems_txt_vendor_code_pos
			returnitems_txt_vendor_code_len
			returnitems_txt_item_code_pos
			returnitems_txt_item_code_len
			returnitems_txt_incoming_quantity_pos
			returnitems_txt_incoming_quantity_len
			vendororder_txt_vendor_code_pos
			vendororder_txt_vendor_code_len
			vendororder_txt_item_code_pos
			vendororder_txt_item_code_len
			vendororder_txt_incoming_quantity_pos
			vendororder_txt_incoming_quantity_len
			returnitems_txt_vendor_code_pos
			returnitems_txt_vendor_code_len
			returnitems_txt_item_code_pos
			returnitems_txt_item_code_len
			returnitems_txt_incoming_quantity_pos
			returnitems_txt_incoming_quantity_len
			items_txt_d_item_number_pos
			items_txt_d_item_number_len
			items_txt_a_item_number_pos
			items_txt_a_item_number_len
			items_txt_a_item_name_pos
			items_txt_a_item_name_len
			items_txt_a_item_description_pos
			items_txt_a_item_description_len
			items_txt_a_item_dosage_pos
			items_txt_a_item_dosage_len
			items_txt_a_warehouse_reorder_level_pos
			items_txt_a_warehouse_reorder_level_len
			items_txt_a_vendor_code_pos
			items_txt_a_vendor_code_len
			items_txt_a_warehouse_reorder_quantity_pos
			items_txt_a_warehouse_reorder_quantity_len
			items_txt_a_expected_delivery_time_pos
			items_txt_a_expected_delivery_time_len
			items_txt_c_item_number_pos
			items_txt_c_item_number_len
			items_txt_c_item_name_pos
			items_txt_c_item_name_len
			items_txt_c_item_description_pos
			items_txt_c_item_description_len
			items_txt_c_item_dosage_pos
			items_txt_c_item_dosage_len
			items_txt_c_warehouse_reorder_level_pos
			items_txt_c_warehouse_reorder_level_len
			items_txt_c_vendor_code_pos
			items_txt_c_vendor_code_len
			items_txt_c_warehouse_reorder_quantity_pos
			items_txt_c_warehouse_reorder_quantity_len
			items_txt_c_expected_delivery_time_pos
			items_txt_c_expected_delivery_time_len
			addstoreitems_txt_store_number_pos
			addstoreitems_txt_store_number_len
			addstoreitems_txt_store_priority_pos
			addstoreitems_txt_store_priority_len
			addstoreitems_txt_item_number_pos 
			addstoreitems_txt_item_number_len
			addstoreitems_txt_requested_quantity_pos 
			addstoreitems_txt_requested_quantity_len
			batchreplenish_txt_store_number_pos      
			batchreplenish_txt_store_number_len
			batchreplenish_txt_store_priority_pos        
			batchreplenish_txt_store_priority_len
			batchreplenish_txt_item_number_pos         
			batchreplenish_txt_item_number_len
			batchreplenish_txt_requested_quantity_pos   
			batchreplenish_txt_requested_quantity_len
			onlineinvrequest_txt_store_number_pos      
			onlineinvrequest_txt_store_number_len
			onlineinvrequest_txt_store_priority_pos    
			onlineinvrequest_txt_store_priority_len
			onlineinvrequest_txt_item_number_pos      
			onlineinvrequest_txt_item_number_len
			onlineinvrequest_txt_requested_quantity_pos  
            onlineinvrequest_txt_requested_quantity_len
			

*/

#endif