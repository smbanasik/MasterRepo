#ifndef BANK_ACCOUNTS_CLASS_CPP
#define BANK_ACCOUNTS_CLASS_CPP

#include <iostream>
#include <string>

#include "BankAccountsClass.h"

using namespace std;

void BankAccountsClass::display() {
    cout << endl <<
        "Bank Account   : " << accountIdStr     << endl <<
        "Account Owner  : " << accountOwnerStr  << endl <<
        "Account Balance: " << accountBalanceFl << endl;
}

#endif