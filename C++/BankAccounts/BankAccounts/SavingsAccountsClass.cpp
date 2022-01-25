#ifndef SAVINGS_ACCOUNTS_CLASS_CPP
#define SAVINGS_ACCOUNTS_CLASS_CPP

#include <iostream>
#include <iomanip>
#include <string>

#include "BankAccountsClass.h"
#include "SavingsAccountsClass.h"

using namespace std;

// SavingsAccountsClass statics
float SavingsAccountsClass::savingsInterestRate = 0;

bool SavingsAccountsClass::savingsWithdraw(float withdrawAmountFl) {
  if (accountBalanceFl < withdrawAmountFl) {
    cout << endl <<
      "*** Insufficient Funds ***" <<
      "Account :             " << accountIdStr      << endl <<
      "Owner :               " << accountOwnerStr   << endl <<
      "Account Balance:      " << accountBalanceFl << endl <<
      "Withdraw Amount :    $" << withdrawAmountFl << endl <<
      "Press enter once or twice to continue." << endl; cin.ignore(); cin.get();
    return EXIT_FAILURE;
  }

  accountBalanceFl -= withdrawAmountFl;

  return EXIT_SUCCESS;
}

void SavingsAccountsClass::calculateInterest()
{
  const unsigned NO_OF_MONTHS          =  12;
  const unsigned CONVERT_TO_PERCENTAGE = 100;

  float savingsInterestAmount = accountBalanceFl * savingsInterestRate / (NO_OF_MONTHS * CONVERT_TO_PERCENTAGE);
  accountBalanceFl += savingsInterestAmount;
}

void SavingsAccountsClass::display() {

    cout << endl <<
        "Savings Account  : " << accountIdStr               << endl <<
        "Account Owner    : " << accountOwnerStr            << endl <<
        "Account Balance  : " << accountBalanceFl           << endl <<
        "Savings Interest : " << savingsInterestRate << "%" << endl <<
        endl;

}

#endif