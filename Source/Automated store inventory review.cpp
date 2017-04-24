////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ofstream outPut;
	//outPut.open("batchreplenish.txt");

	createFile("batchreplenish.txt", outPut);

	insertHeader(outPut, g_batchreplenish_seq);

	int counter = 0;
	for (int x = 0; x < store_inventory_table.size(); x++)
	{
		if (store_inventory_table[x].quantity <= store_inventory_table[x].reorder_level)			//store quantity at or below the reorder point
		{
			string outP = "B";
			outP += StringZeroFill(g_batchreplenish_txt_store_number_len, store_inventory_table[x].store_number);

			//get store priority from store table
			for (int y = 0; x < store_data_table.size(); y++)
			{
				if (store_inventory_table[x].store_number == store_data_table[y].store_number)
				{
					outP += StringZeroFill(g_batchreplenish_txt_store_priority_len, store_data_table[y].store_priority);
					break;
				}
			}
			outP += StringZeroFill(g_batchreplenish_txt_item_number_len, store_inventory_table[x].item_number);
			outP += StringZeroFill(g_batchreplenish_txt_requested_quantity_len, store_inventory_table[x].reorder_quantity);
			counter++;
		}
	}

	insertTrailer(outPut, counter);
	outPut.close();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


