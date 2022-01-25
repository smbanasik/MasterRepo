#ifndef SAVINGS_ACCOUNTS_CLASS_H
#define SAVINGS_ACCOUNTS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>

#include "BankAccountsClass.h"

using namespace std;

class SavingsAccountsClass : public BankAccountsClass {
protected:
  static float savingsInterestRate;

public:
  SavingsAccountsClass(string accountIdStr, string accountOwnerStr, float accountBalanceFl)
  : BankAccountsClass(accountIdStr, accountOwnerStr, accountBalanceFl) { }

  static void  setSavingsInterestRate(float savingsInterestRate)
  {
      SavingsAccountsClass::savingsInterestRate = savingsInterestRate;
  }

  static float getSavingsInterestRate()
  {
      return SavingsAccountsClass::savingsInterestRate;
  }

  void        calculateInterest();
  bool        savingsWithdraw(float);
  void        display();

};

#endif
