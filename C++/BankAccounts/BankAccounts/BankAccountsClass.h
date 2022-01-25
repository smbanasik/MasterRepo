#ifndef BANK_ACCOUNTS_CLASS_H
#define BANK_ACCOUNTS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BankAccountsClass {

  protected:
    string   accountIdStr,
             accountOwnerStr;
    float    accountBalanceFl;

  public:
    BankAccountsClass() : accountIdStr(""), accountOwnerStr(""), accountBalanceFl(0) {}

    BankAccountsClass
    (string accountIdStr, string accountOwnerStr, float accountBalanceFl) :
     accountIdStr(accountIdStr), accountOwnerStr(accountOwnerStr), accountBalanceFl(accountBalanceFl) {};

    const string& getAcountIdStr()                     const { return accountIdStr; }
    void          setAccountIdStr(string accountIdStr) { this->accountIdStr = accountIdStr; }

    const string& getAccountOwnerStr()                 const { return accountOwnerStr; }
    void          setAccountOwnerStr(string accountOwnerStr) { this->accountOwnerStr = accountOwnerStr; }

    float         getAccountBalanceFl()                const { return accountBalanceFl; }
    void          setAccountBalanceFl(float accountBalanceFl) { this->accountBalanceFl = accountBalanceFl; }

    void          deposit(float depositAmountFl) { accountBalanceFl += depositAmountFl; };

    void          virtual display();

};//BankAccountsClass

#endif