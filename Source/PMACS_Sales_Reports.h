#ifndef PMACS_SALES_REPORTS_H
#define PMACS_SALES_REPORTS_H

bool RunOnlineSalesReport();
bool RunReportByStore(int storeNum);
bool RunReportByItem(int itemNum);
int RunReportByStoreCheck();
int RunReportByItemCheck();

long double getItemCost(int itemNumber, int transaction);
unsigned long long getItemQuantity(int itemNumber, int transaction);

#endif