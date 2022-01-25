#ifndef CHECKING_ACCOUNTS_CLASS_CPP
#define CHECKING_ACCOUNTS_CLASS_CPP

#include <iostream>
#include <iomanip>
#include <string>

#include "CheckingAccountsClass.h"

using namespace std;

void CheckingAccountsClass::cashCheck(float checkAmountFl) {
  if (checkAmountFl >= accountBalanceFl) {
    cout << endl <<
      "*** Insufficient Funds ***" << endl <<
      "Account         : " << accountIdStr << endl <<
      "Owner           : " << accountOwnerStr << endl <<
      "Account Balance : " << accountBalanceFl << endl <<
      "Check Amount    : $" << checkAmountFl << endl << endl;
      return;
  }

  //  cash check and deduct per check charge if necessary
  if (accountBalanceFl < checkingMinimumFl)
    accountBalanceFl -= (checkAmountFl + chargePerCheckFl);
  else
    accountBalanceFl -= checkAmountFl;
}

void CheckingAccountsClass::display() {
    cout <<
        "Checking Account: " << accountIdStr      << endl <<
        "Account Owner   : " << accountOwnerStr   << endl <<
        "Account Balance : " << accountBalanceFl  << endl <<
        "Minimum Amount  : " << checkingMinimumFl << endl <<
        "Charge Per Check: " << chargePerCheckFl  << endl <<
        endl;
}

//CheckingAccountsClass statics
float CheckingAccountsClass::checkingMinimumFl = 0;
float CheckingAccountsClass::chargePerCheckFl  = 0;

#endif
