#ifndef INTEREST_CHECKING_ACCOUNTS_CLASS_CPP
#define INTERESTCHECKING_ACCOUNTS_CLASS_CPP

#include <iostream>
#include <iomanip>
#include <string>

#include "InterestCheckingAccountsClass.h"

using namespace std;

// InterestCheckingAccountsClass statics
float InterestCheckingAccountsClass::interestCheckingRate             = 0,
      InterestCheckingAccountsClass::minimmunBalanceRequired          = 0,
      InterestCheckingAccountsClass::monthlyFeeChargeNoMinimumBalance = 0;

void InterestCheckingAccountsClass::calculateInterest() {
  const int NO_OF_MONTHS = 12;
  const int CONVERT_TO_PERCENTAGE = 100;

  if (accountBalanceFl >= minimmunBalanceRequired) {
    float interestAmmount = accountBalanceFl * interestCheckingRate / (NO_OF_MONTHS * CONVERT_TO_PERCENTAGE);
    accountBalanceFl += interestAmmount;
  }
  else
    accountBalanceFl -= monthlyFeeChargeNoMinimumBalance;
}

void InterestCheckingAccountsClass::display() {
    cout << endl <<
        "Interest Checking Account: " << accountIdStr                     << endl <<
        "Account Owner            : " << accountOwnerStr                  << endl <<
        "Account Balance          : " << accountBalanceFl                 << endl <<
        "Minimum Balance          : " << minimmunBalanceRequired          << endl <<
        "Interest Rate            : " << interestCheckingRate      << "%" << endl <<
        "Monthly Fee              : " << monthlyFeeChargeNoMinimumBalance << endl <<
        endl;
}

#endif