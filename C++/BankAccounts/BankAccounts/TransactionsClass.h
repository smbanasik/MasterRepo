#ifndef TRANSACTIONS_CLASS_CLASS_H
#define TRANSACTIONS_CLASS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TransactionsClass {

private:
  string   accountIdentifcationStr;
  string   transactionIdStr;
  unsigned transactionArgumentFl;

public:
//Constructor (Default)
TransactionsClass()
  : accountIdentifcationStr(""), transactionIdStr(""), transactionArgumentFl(0)
{}

  const string& getIdentifcationStr() const { return accountIdentifcationStr; };
  void          setIdentifcationStr(const string& accountIdentifcationStr)
  {
      this->accountIdentifcationStr = accountIdentifcationStr;
  }

  const string& getTransactionIdStr() const { return transactionIdStr; };
  void          setTransactionIdStr(const string& transactionIdStr)
  {
      this->transactionIdStr = transactionIdStr;
  }

  unsigned getTransactionArgumentFl() const { return transactionArgumentFl; };
  void     setTransactionArgumentFl(float transactionArgumentFl)
  {
      this->transactionArgumentFl = transactionArgumentFl;
  }

  void displayTransaction() {
    cout << "Transaction:" << endl <<
            "------------" << endl;
    cout << "Account Id                  : " << accountIdentifcationStr << endl <<
            "Account Transaction Id      : " << transactionIdStr << endl;
    if (transactionIdStr != "interest")
       cout << "Account Transaction Amount  : " << transactionArgumentFl << endl;
    cout << endl;
  }

};//TransactionClass

#endif