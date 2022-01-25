/*
    Program Name: Factorial
    Date:		  2021-07-30
    Author:		  Spencer Banasik

    Program Purpose
    This program calculates factorials using a loop method and a recursive method in three different data types until
    it reaches a stack overflow error for each data type. It then displays all of the calculations and the time taken
    in nanoseconds to perform those calculations using either method.

    Module Design Description
    The program makes use of templates and recursion.
    The program uses classes in the file.

    Inputs:
    None

    Outputs:
    The program displays all of the calculations and times elapsed into the console.

*/
#include <chrono>
#include <limits>
#include <locale>

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;
using namespace chrono;

template <class TypeMultiply>
bool isSafeMultiply (TypeMultiply mult01, TypeMultiply mult02, TypeMultiply &multResult) {

/*
add code to check if mult01 or mult02 = 0
if so, set multResult to 0 and leave with a true
*/

    if (mult01 == 0 || mult02 == 0) {

        multResult = 0;
        return true;
    }

/*
calculate the multResult from mult01 and mult02
check if mult01 is equal to the multResult divided by mult02
if mult01 is equal to the multResult divided by mult02 then leave with a true
if not equal then leave with a false
*/

    multResult = mult01 * mult02;
    if (mult01 == (multResult / mult02))
        return true;
    return false;

}
template <class TypeMultiply>
void calculateTimeFactorialLoopFunc(void) {

  //$set time start to clock now() 

  auto timeStart = steady_clock::now();

  TypeMultiply multiplier      = 1,
               factorialResult = 1;

  while ( isSafeMultiply <TypeMultiply> (multiplier, factorialResult, factorialResult)) {


    // display the multiplier and the factorialresult using field wdths of 3 and 27 respectively

      cout << setw(3) << multiplier << setw(27) << factorialResult << endl;

    // increment the multiplier

      ++multiplier;
  }

  // calculate timeElapsed as described in the assignment

  auto timeElapsed = duration_cast<nanoseconds> (steady_clock::now() - timeStart);
  
  cout << endl;

  /*
  Display "Unsigned overflow at : " using setw() to display multiplier
  Display "Time Elapsed (nano)  : " using setw() to display timeElapsed.count()
  */

  cout << "Unsigned overflow at : " << setw(15) << multiplier << endl;
  cout << "Time Elapsed (nano)  : " << setw(15) << timeElapsed.count() << endl;

}//calculateTimeFactorialLoopFunc

 //------------------------------------------
template <class TypeMultiply>
void factorialRecursiveFunc (TypeMultiply &multiplier, TypeMultiply factorialResult) {

  if (isSafeMultiply <TypeMultiply> (factorialResult, multiplier, factorialResult)) {

    cout << setw(3) << multiplier << setw(27) << factorialResult << endl;
    // invoke factorialRecursiveFunc with ++multiplier and factorialResult
    factorialRecursiveFunc(++multiplier, factorialResult);

  }
  return;

}//factorialRecursive

 //------------------------------------------  
template <class TypeMultiply>
void calculateTimeFactorialRecursiveFunc() {

  // set time start to clock now() 

  auto timeStart = steady_clock::now();

  TypeMultiply mult01 = 1;
  factorialRecursiveFunc <TypeMultiply> (mult01, 1);

  // calculate timeElapsed as described in the assignment

  auto timeElapsed = duration_cast<nanoseconds>(steady_clock::now() - timeStart);

  cout << endl;

  /*
  Display "Unsigned overflow at : " using setw() to display multiplier
  Display "Time Elapsed (nano)  : " using setw() to display timeElapsed.count()
  */

  cout << "Unsigned overflow at : " << setw(15) << mult01 << endl;
  cout << "Time Elapsed (nano)  : " << setw(15) << timeElapsed.count() << endl;

}//calculateTimeFactorialRecursiveFunc()

template <typename TYPESIZE> 
class FactorialCalculationClass {

private:
  unsigned typeSizeBits;

public:
  // Constructor
  FactorialCalculationClass(unsigned typeSize) {
      typeSizeBits = typeSize;
  }

  void executeFactorialForType() {

    cout <<
      typeSizeBits <<
      " bit unsigned Factorial Loop" << endl <<
      "------------------------------" << endl;
    calculateTimeFactorialLoopFunc <TYPESIZE>();
    cout << endl << endl;

    cout <<
      typeSizeBits <<
      " bit unsigned Factorial Recursion" << endl <<
      "-----------------------------------" << endl;
    calculateTimeFactorialRecursiveFunc <TYPESIZE>();
    cout << endl << endl;

  }

};// template <class TYPESIZE> class factorialCalculationClass

int main() {
  // condition cout set to local digit separation comas (USA)
  cout.imbue(locale(""));

  /*
  create an object of FactorialCalculationClass <uintnn_t> called factorialCalculateUintnnObj(nn)
  where nn is the size in bits for the tempalte type uintnn_t, the object name 
  factorialCalculateUintnnObj and the nn for the argument (nn) to the constructor
  nn must equal nn = 16, 32 and 64 to make the 3 objects
  */

  FactorialCalculationClass <uint16_t> factorialCalculateUnit16Obj(16);
  FactorialCalculationClass <uint32_t> factorialCalculateUnit32Obj(32);
  FactorialCalculationClass <uint64_t> factorialCalculateUnit64Obj(64);

  /*
  for each of the 3 nn objects factorialCalculateUintnnObj
  invoke the executeFactorialForType()
  */

  factorialCalculateUnit16Obj.executeFactorialForType();
  factorialCalculateUnit32Obj.executeFactorialForType();
  factorialCalculateUnit64Obj.executeFactorialForType();
  
  cout << "Press the enter key once or twice to end..." << endl; cin.ignore(); cin.get();


  return 0;
}
