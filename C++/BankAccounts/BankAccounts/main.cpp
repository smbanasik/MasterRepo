/*
    Program Name: Bank Accounts
    Date:		  2021-07-23
    Author:		  Spencer Banasik

    Program Purpose
    This program reads in a series of bank accounts and transactions to be performed on those bank accounts,
    then calculates the outcoems of those transactions based off of the bank configurations.

    Module Design Description
    The program stores the transactions and bank accounts in two dynamic arrays.
    The program outputs the updated arrays into a file.
    The program makes use of multiple classes.

    Inputs:
    InfoBankAccounts.txt - Information containing the bank accounts to be inputted
    InfoBankAccountsTransactions.txt - Information containing instructions for performing the transactions
    InfoBankConfig.txt - A file containing the values that set values such as interest rates, minimum balances, and charges per check.

    Outputs:
    InfoBankAccounts.txt - Updated information about the bank accounts after all transactions have been performed.
    Additionally the program displays the transactions and processes to the console.

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "BankAccountsClass.h"
#include "CheckingAccountsClass.h"
#include "InterestCheckingAccountsClass.h"
#include "SavingsAccountsClass.h"
#include "TransactionsClass.h"

using namespace std;

const string BANK_CONFIGURATION_FILE_NAME_STR         = "InfoBankConfig.txt";
const string BANK_ACCOUNTS_FILE_NAME_STR              = "InfoBankAccounts.txt";
const string BANK_ACCOUNTS_TRANSACTIONS_FILE_NAME_STR = "InfoBankAccountsTransactions.txt";

void CheckFileStreamOpen(string fileNameStr, ifstream& inFile);
void CheckFileStreamOpen(string fileNameStr, ofstream& outFile);
void ReadConfigurationFile(string bankConfigurationFileNameStr);
void ReadInFromBankAccountsFile
(string bankAccountsFileNameStr,
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCount);
void ReadInFromTransactionsFile
(string transactionsFileNameStr,
 TransactionsClass*  &transactionsAry, unsigned& transactionsCountUns);
void ProcessTransactions
(TransactionsClass*   transactionsAry, unsigned& transactionsCountUns,
 BankAccountsClass**& bankAccountsAry, unsigned& accountsCountUns);
bool getMatchingBankAccountIndexUns(
  BankAccountsClass**& bankAccountsAry, unsigned  accountsCountUns,
  string accountIdStr, unsigned& bankAccountIndex);
void UpdateBankAccountsFile
(string   bankAccountsFileNameStr,
 BankAccountsClass**& bankAccountsAry, unsigned totalNoBankAccountsUns);

int main() {
  BankAccountsClass** bankAccountsAry      = nullptr;
  TransactionsClass*  transactionsAry      = nullptr;
  unsigned            accountsCountUns     = 0;
  unsigned            transactionsCountUns = 0;

  cout << setprecision(2) << fixed << showpoint;           //  set up output for dollar amounts

  ReadConfigurationFile     (BANK_CONFIGURATION_FILE_NAME_STR);
  ReadInFromBankAccountsFile(BANK_ACCOUNTS_FILE_NAME_STR, 
                             bankAccountsAry, accountsCountUns);
  ReadInFromTransactionsFile(BANK_ACCOUNTS_TRANSACTIONS_FILE_NAME_STR,
                             transactionsAry, transactionsCountUns);
  ProcessTransactions       (transactionsAry, transactionsCountUns,
                             bankAccountsAry, accountsCountUns);
  UpdateBankAccountsFile    (BANK_ACCOUNTS_FILE_NAME_STR,
                             bankAccountsAry, accountsCountUns);

} // int main()

// This function checks to make sure the file was opened successfully and exit the program if it was unable to.

void CheckFileStreamOpen(string fileNameStr, ifstream& inFile) {
    if (inFile.fail()) {
        cout << "File " << fileNameStr << " could not be opened!" << endl;
        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();
        exit(1);
    }
}

// This function checks to make sure the file was opened successfully and exit the program if it was unable to.

void CheckFileStreamOpen(string fileNameStr, ofstream& outFile) {
    if (outFile.fail()) {
        cout << "File " << fileNameStr << " could not be opened!" << endl;
        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();
        exit(1);
  }
}

/* This function reads input from the configuration file and assings the relevant values to the values in the file
*/
void ReadConfigurationFile(string bankConfigurationFileNameStr) {
    ifstream inputFile(bankConfigurationFileNameStr);
    CheckFileStreamOpen(bankConfigurationFileNameStr, inputFile);

    cout << "Configureation Information : " << endl <<
            "============================ " << endl << endl;

    float valueFloat;
    
    // Read in the savings interest rate and display it

    inputFile >> valueFloat;
    SavingsAccountsClass::setSavingsInterestRate(valueFloat);
    cout << "Savings Interest Rate                : " << SavingsAccountsClass::getSavingsInterestRate() << endl;

    // Read in the minimum balance amount display it

    inputFile >> valueFloat;
    CheckingAccountsClass::setCheckingMinimumFl(valueFloat);
    cout << "Checking Minimum Balance             : " << CheckingAccountsClass::getCheckingMinimumFl() << endl;

    // Read in the charge per check and display it

    inputFile >> valueFloat;
    CheckingAccountsClass::setChargePerCheckFl(valueFloat);
    cout << "Charge Per Check                     : " << CheckingAccountsClass::getChargePerCheckFl() << endl;

    // Read in the interest checking rate and display it

    inputFile >> valueFloat;
    InterestCheckingAccountsClass::setInterestCheckingRate(valueFloat);
    cout << "Interest Checking Rate               : " << InterestCheckingAccountsClass::getInterestCheckingRate() << endl;

    // Read in the interest checking minimum balance and display it

    inputFile >> valueFloat;
    InterestCheckingAccountsClass::setMinimmunBlanceRequired(valueFloat);
    cout << "Interest Checking Minimum Balance    : " << InterestCheckingAccountsClass::getMinimmunBlanceRequired() << endl;

    // Read in the checking monthly fee charge and display it

    inputFile >> valueFloat;
    InterestCheckingAccountsClass::setMonthlyFeeChargeNoMinimumBalance(valueFloat);
    cout << "Interest Checking Monthly Fee Charge : " << InterestCheckingAccountsClass::getMonthlyFeeChargeNoMinimumBalance() << endl;

    cout << "\n\n";

    inputFile.close();
}

/* This function reads in the information from the bank accounts file and assigns it to a dynamic array
*/
void ReadInFromBankAccountsFile
(string bankAccountsFileNameStr, 
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCountUns) {
  
    ifstream accountsFile(bankAccountsFileNameStr);
    CheckFileStreamOpen(bankAccountsFileNameStr, accountsFile);

    string inputBufferStr;

    // Get the amount of accounts in the file

    accountsCountUns = 0;
    while (getline(accountsFile, inputBufferStr))
        ++accountsCountUns;
    
    // Create an array with a size based off of the accounts

    bankAccountsAry = new BankAccountsClass *[accountsCountUns];

    // Return to beginning of the file

    accountsFile.clear();
    accountsFile.seekg(0, ios::beg);
    constexpr char COMMA_CHAR = ',';

    string accountIdStr;
    string accountOwnerStr;
    string accountBalanceStr;
    float accountBalanceFl;

    cout << "Accounts:" << endl
         << "=========" << endl << endl;

    // Loop through the amount of accounts and assign the values inot hte array

    for (unsigned int lines = 0; lines < accountsCountUns; ++lines) {

        // Get the entire line and store it in a buffer

        getline(accountsFile, inputBufferStr);
        istringstream isStringStream(inputBufferStr);

        // Store the content up to the comma character to a specific string
        // Convert the last string into a float

        getline(isStringStream, accountIdStr,      COMMA_CHAR);
        getline(isStringStream, accountOwnerStr,   COMMA_CHAR);
        getline(isStringStream, accountBalanceStr, COMMA_CHAR);
        accountBalanceFl = stof(accountBalanceStr);

        // Create new classes based off of the first letter in the id string

        switch (accountIdStr.at(0)) {

        case 'S':
        case's':
            bankAccountsAry[lines] = new SavingsAccountsClass(accountIdStr, accountOwnerStr, accountBalanceFl);
            bankAccountsAry[lines]->display();
            break;

        case 'C':
        case 'c':
            bankAccountsAry[lines] = new CheckingAccountsClass(accountIdStr, accountOwnerStr, accountBalanceFl);
            bankAccountsAry[lines]->display();
            break;

        case 'I':
        case 'i':
            bankAccountsAry[lines] = new InterestCheckingAccountsClass(accountIdStr, accountOwnerStr, accountBalanceFl);
            bankAccountsAry[lines]->display();
            break;

        default:
            cout << "*** illegal account identification ***" << endl;
        }//switch

    }//for

    accountsFile.close();

}//ReadInFromBankAccountsFile()

/* This function reads in the information from the transactions file and assigns it to a dynamic array
*/
void ReadInFromTransactionsFile
(string transactionsFileNameStr,
 TransactionsClass* &transactionsAry,  unsigned& transactionsCountUns) {
  
    ifstream transactionsFile(transactionsFileNameStr);
    CheckFileStreamOpen(transactionsFileNameStr, transactionsFile);

    string inputBufferStr;

    // Get the total amount of transactions in the file

    transactionsCountUns = 0;
    while (getline(transactionsFile, inputBufferStr))
        ++transactionsCountUns;

    // Create the dynamic array with the size of the amount of transactions

    transactionsAry = new TransactionsClass [transactionsCountUns];

    transactionsFile.clear();
    transactionsFile.seekg(0, ios::beg);
    constexpr char COMMA_CHAR = ',';

    string accountIdStr;
    string accoundTransactionIdStr;
    string accountTransactionAmountStr;
    float accountTransactionAmountFl;

    cout << "Transactions:" << endl
        << "-------------" << endl << endl;

    // Loop through the amount of transactions and assign the values into the array

        for (unsigned int lines = 0; lines < transactionsCountUns; ++lines) {

            // Get whole line and store in buffer

            getline(transactionsFile, inputBufferStr);
            istringstream isStringStream(inputBufferStr);

            // Read buffer line up to the comma and assign it to the ID string

            getline(isStringStream, accountIdStr, COMMA_CHAR);
            transactionsAry[lines].setIdentifcationStr(accountIdStr);
            
            // Read buffer line up to the comma and assign it to the transaction ID

            getline(isStringStream, accoundTransactionIdStr, COMMA_CHAR);
            transactionsAry[lines].setTransactionIdStr(accoundTransactionIdStr);

            // Check if the transaction is not instructing the program to calculate interest

            if (accoundTransactionIdStr != "interest") {

                // Read buffer line up to the comma and assign it to the amount specified

                getline(isStringStream, accountTransactionAmountStr, COMMA_CHAR);
                accountTransactionAmountFl = stof(accountTransactionAmountStr);
                transactionsAry[lines].setTransactionArgumentFl(accountTransactionAmountFl);
            }
            
            transactionsAry[lines].displayTransaction();

    }//for

        cout << endl;
        transactionsFile.close();

}//ReadInFromTransactionsFile

/* This function loops through the transaction array and performs the actions indicated by the array arguments.
*/

void ProcessTransactions
(TransactionsClass   *transactionsAry, unsigned& transactionsCountUns,
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCountUns) {
  
    string accountIdStr;
    string accountTransactionIdStr;
    string accountTransactionAmountStr;
    float  accountTransactionAmountFl;

    unsigned bankAccountIndex;

    cout << "Process Transactions" << endl
        << "--------------------" << endl << endl;

    // Loop through every transaction in array

    for (unsigned int transactionCount = 0; transactionCount < transactionsCountUns; ++transactionCount) {

        // Check that the account id string matches an account 

        accountIdStr = transactionsAry[transactionCount].getIdentifcationStr();
        if (!getMatchingBankAccountIndexUns(bankAccountsAry, accountsCountUns, accountIdStr, bankAccountIndex)) {

            cout <<
                "***account identification not found " << endl <<
                "Acount Id : " << accountIdStr << endl << endl;
            return;
        }

        // Get the transaction ID to be performed

        accountTransactionIdStr = transactionsAry[transactionCount].getTransactionIdStr();

        // The switch will check for the transaction ID which is then followed by a series of if statements to determine
        // which actions need to be taken for the account.

        switch (accountIdStr.at(0)) {

        case 'S':
        case 's':
            cout << "Account Before Transaction" << endl
                << "--------------------------" << endl;

            static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            transactionsAry[transactionCount].displayTransaction();

            // Depositing into a savings account

            if (accountTransactionIdStr == "deposit") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                bankAccountsAry[bankAccountIndex]->deposit(accountTransactionAmountFl);
            }

            // Withdrawing from a savings account

            else if (accountTransactionIdStr == "withdraw") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->savingsWithdraw(accountTransactionAmountFl);
            }

            // Performing interest on a savings account

            else if (accountTransactionIdStr == "interest") {

                static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->calculateInterest();
            }

            else {

                cout << "Invalid Transaction Id : " << accountTransactionIdStr << endl << endl;

            }

            cout << "Account After Transaction" << endl
                << "-------------------------" << endl;
            static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            break;

        case 'C':
        case 'c':
            cout << "Account Before Transaction" << endl
                << "--------------------------" << endl;
            static_cast<CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            transactionsAry[transactionCount].displayTransaction();

            // Deposit into checkings account

            if (accountTransactionIdStr == "deposit") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                accountTransactionAmountFl = bankAccountsAry[bankAccountIndex]->getAccountBalanceFl() + accountTransactionAmountFl;
                bankAccountsAry[bankAccountIndex]->setAccountBalanceFl(accountTransactionAmountFl);
            }

            // Cash check with checkings account

            else if (accountTransactionIdStr == "check") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                static_cast<CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->cashCheck(accountTransactionAmountFl);
            }

            cout << "Account After Transaction" << endl
                << "-------------------------" << endl;
            static_cast<CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();
            break;

        case 'I':
        case 'i':

            cout << "Account Before Transaction" << endl
                << "--------------------------" << endl;

            static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            transactionsAry[transactionCount].displayTransaction();

            // Deposit money into interest bearing checkings account

            if (accountTransactionIdStr == "deposit") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                accountTransactionAmountFl = bankAccountsAry[bankAccountIndex]->getAccountBalanceFl() + accountTransactionAmountFl;
                bankAccountsAry[bankAccountIndex]->setAccountBalanceFl(accountTransactionAmountFl);
            }

            // Cash check with interest bearing checkings account

            else if (accountTransactionIdStr == "check") {

                accountTransactionAmountFl = transactionsAry[transactionCount].getTransactionArgumentFl();
                static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->cashCheck(accountTransactionAmountFl);
            }

            // Calculate interest in interest bearing checkings account

            else if (accountTransactionIdStr == "interest") {

                static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->calculateInterest();
            }

            cout << "Account After Transaction" << endl
                << "-------------------------" << endl;
            static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();
            break;


        default:
            cout << "*** illegal account identification in transaction ***" <<
                "\n Account Id     : " << accountIdStr << endl << endl;
        }//switch

    }//for

    cout << endl;


}//ProcessTransactions

bool getMatchingBankAccountIndexUns(
BankAccountsClass** &bankAccountsAry, unsigned  accountsCountUns, 
string              accountIdStr,     unsigned& bankAccountIndex) {
  bankAccountIndex = 0;
  for (; bankAccountIndex < accountsCountUns; ++bankAccountIndex)
    if (bankAccountsAry[bankAccountIndex]->getAcountIdStr() == accountIdStr) {
      return true;
    }
  return false;
}

void UpdateBankAccountsFile
(string bankAccountsFileNameStr,
 BankAccountsClass**& bankAccountsAry, unsigned accountsCountUns) {

  ofstream outFile(bankAccountsFileNameStr);
  CheckFileStreamOpen(bankAccountsFileNameStr, outFile);

  cout << "Updating " << bankAccountsFileNameStr << endl <<
          "-----------------------------" << endl;

  for (unsigned writeIndex = 0; writeIndex < accountsCountUns; ++writeIndex)
    outFile <<
    bankAccountsAry[writeIndex]->getAcountIdStr()      << "," <<
    bankAccountsAry[writeIndex]->getAccountOwnerStr()  << "," <<
    bankAccountsAry[writeIndex]->getAccountBalanceFl() << endl;

  outFile.close();
};

