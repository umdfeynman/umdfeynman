#ifndef PMACS_ACCUSTOCK_H
#define PMACS_ACCUSTOCK_H

#include "PMACS_Globals.h"

// TODO:  AccuStock tests
// Add items to store using default reorder quantity / level / etc
// Adjust quantity manually
// Perform accustock 7 times where quantity > high_thresh
// Perform accustock 7 times where quantity < high_thresh
// Perform accustock 7 times where quantity > low_thresh
// Perform accustock 7 times where quantity < low_thresh
// Perform accustock 7 times where quantity alternates between high & low thresh

bool calculateAccuStock()
{
    for (int i = 0; i < store_inventory_table.size(); i++)
    {
        // High threshold is set to 1.15 * reorder_level, low 0.85 * reorder level by default
        
        // Depending on if quantity is above or below threshold, 
        if (store_inventory_table[i].quantity > store_inventory_table[i].high_threshold)
            store_inventory_table[i].accustock_direction--;
        if (store_inventory_table[i].quantity < store_inventory_table[i].low_threshold)
            store_inventory_table[i].accustock_direction++;
        
        
        // If item quantity goes under the low threshold 7 times, increase reorder quantity
        if (store_inventory_table[i].accustock_direction == 7)
        {
            // Increase by 10%
            int increase_amount = 0.1f * (float)store_inventory_table[i].reorder_quantity;
            store_inventory_table[i].reorder_quantity += increase_amount;
            store_inventory_table[i].accustock_direction = 0;
            store_inventory_table[i].high_threshold += increase_amount;
            store_inventory_table[i].low_threshold += increase_amount;
        }
        
        // If item quantity goes above the high threshold 7 times, decrease reorder quantity
        if (store_inventory_table[i].accustock_direction == -7)
        {
            // Decrease by 10%
            int decrease_amount = 0.1f * (float)store_inventory_table[i].reorder_quantity;
            store_inventory_table[i].reorder_quantity -= decrease_amount;
            store_inventory_table[i].accustock_direction = 0;
            store_inventory_table[i].high_threshold -= decrease_amount;
            store_inventory_table[i].low_threshold -= decrease_amount;
        }
        
    }
}
    

#endif