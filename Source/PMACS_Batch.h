#ifndef PMACS_BATCH_H
#define PMACS_BATCH_H

bool runOfflineBatchProcess();
bool addDeleteStore();
bool storeInventoryGeneration();
bool massInventoryUpdates();
bool checkAllStoresClosed();
bool warehouseInventoryGeneration();
bool calculateAccuStock();

/////////////////////////////
void openAllStores();
bool mergeReturnsAndOrders();
bool vendorOrders();
bool mergeAddStoreBatchReplenishOnlineInvRequests();
bool batchReportGeneration();
#endif