#include <fstream>
#include <string>
#include <vector>
#include "PMACS_Data_Structures.h"
#include "PMACS_Defines.h"
#include "PMACS_Globals.h"

bool readTransaction()
{
    Plog.setContext("readTransaction");
    ifstream transactionFile;
    transactionFile.open(transaction_file);
    
    if (!transactionFile || !transactionFile.good())
    {
        Plog.LogError("Failed to read database file.  Bailing.");
        return false;
    }
    
    std::string readLine;
    std::getline(transactionFile, readLine);
    
    if (readLine.substr(0, 6) != "HTRANS")
    {
        Plog.LogError("Failed to find header in file.  Bailing.")
        return false;
    }
    
    if (transactionFile.eof())
    {
        Plog.LogWarn("Empty database file.  Continuing.")
        return true;
    }
    
    while(!transactionFile.eof() || !transactionFile)
    {
        
        std::string s_orderNumber;  
        std::string s_originatingCashierNumber;
        std::string s_approvingCashierNumber;
        std::string s_storeNumber;
        std::string s_transactionDate;
        std::string s_accountNumber;
        std::string s_discountPct;  
        std::string s_grandTotal;
        
        std::getline(transactionFile, readLine);
        s_orderNumber = readLine;
        std::getline(transactionFile, readLine);
        s_originatingCashierNumber = readLine;
        std::getline(transactionFile, readLine);
        s_approvingCashierNumber = readLine;
        std::getline(transactionFile, readLine);
        s_storeNumber = readLine;
        std::getline(transactionFile, readLine);
        s_transactionDate = readLine;
        std::getline(transactionFile, readLine);
        s_accountNumber = readLine;
        std::getline(transactionFile, readLine);
        s_discountPct = readLine;
        std::getline(transactionFile, readLine);
        s_grandTotal = readLine;
        
        std::getline(transactionFile, readLine);
        if (readLine[0] != 'S')
        {
            Plog.LogError("Expected S record.  Bailing.");
            return false;
        }
        
        std::vector<std::string> s_transactionItemNumber;
        
        while(readLine[0] != 'E')
        {
            std::getline(transactionFile, readLine);
            s_transactionItemNumber.push_back(readLine);
        }
        
        std::getline(transactionFile, readLine);
        if (readLine[0] != 'S')
        {
            Plog.LogError("Expected S record.  Bailing.");
            return false;
        }
        
        std::vector<std::string> s_transactionItemQuantity;
        while(readLine[0] != 'E')
        {
            std::getline(transactionFile, readLine);
            s_transactionItemQuantity.push_back(readLine);
        }
        
        std::getline(transactionFile, readLine);
        if (readLine[0] != 'S')
        {
            Plog.LogError("Expected S record.  Bailing.");
            return false;
        }
        
        std::vector<std::string> s_transactionItemQuantity;
        while(readLine[0] != 'E')
        {
            std::getline(transactionFile, readLine);
            s_transactionItemQuantity.push_back(readLine);
        }
    
        int orderNumber StringToInt(s_orderNumber);
        int originatingCashierNumber = StringToInt(s_originatingCashierNumber);
        int approvingCashierNumber = StringToInt(s_approvingCashierNumber);
        int storeNumber = StringToInt(s_storeNumber)
        std::string transactionDate = s_transactionDate;
        int accountNumber = StringToInt(s_accountNumber);
        int discountPct = StringToInt(s_discountPct);
        double grandTotal = StringToDouble(s_grandTotal);  // Transaction total after all discounts applied, for easy generation of grand totals in reporting
        
        std::vector<int> transactionItemNumber;
        for (int i = 0; i < s_transactionItemNumber.size(); i++)
        {
            transactionItemNumber.push_back(StringToInt(s_transactionItemNumber[i]));
        }
        
        std::vector<long long> transactionItemQuantity;
        for (int i = 0; i < s_transactionItemQuantity.size(); i++)
        {
            transactionItemQuantity.push_back(StringToInt(s_transactionItemQuantity[i]));
        }
        
        std::vector<double> transactionItemPrice;
        for (int i = 0; i < s_transactionItemPrice.size(); i++)
        {
            transactionItemPrice.push_back(StringToInt(s_transactionItemPrice[i]));
        }
        
        transactionFile.flush();
        transactionFile.close();
}

// Note:  Skipping record length check due to file structure, assuming files are immaculate
// Record checks
    // Check record length
    // Header check
    
    
// For each line
    // Create an instance of of a single table item
    // Using defines, store each field in its own string
    // Convert string to proper type for table and store in instance
    // Push instance to empty table


/*
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
    std::vector<int> transaction_item;
    std::vector<long long> transaction_item_quantity;
    std::vector<double> transaction_item_price;  // Item price after individual item discount 
};*/

//HTRANS
//-1
//-1
//-1
//-1
//
//-1
//-1
//-1.0
//S
//
//
//
//
//E
//S
//
//
//
//
//E
//S - START ARRAY
// - FIELD
// - FIELD
// - FIELD
//E - END ARRAY




