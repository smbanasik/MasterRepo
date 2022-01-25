/* This program calculates the tip on a sale amount. The program prompts the user to enter
*  the amount of sale, then offers a menu for the user to input the tip amount they wish to add.
*  The program then outputs the sales amount, tip amount, and total due.
*/
#include<iostream>
#include<iomanip>
using namespace std;

// Function prototypes, each one found below main in order of appearance here

double calcTipAmt(double saleAmt, double tipPercent);
double calcTotalSale(double saleAmt, double tipAmt);
char getMenuItem(double saleAmt);
double getTipAmt(char menuChoice, double saleAmt, bool& errorDetect);

int main() 
{
	// Declaring the boolean errorDetect, character menuChoice, and numbers saleAmt, tiPAmt, tipPerc, and totalSale

	bool errorDetect = 0;
	char menuChoice;
	double saleAmt, tipAmt, tipPerc, totalSale;
	
	// Prompting the user to enter the sales amount and collects the input

	cout << "Enter the amount of the sale: " << endl;
	cin >> saleAmt;

	// Error check to make sure the sale amount is above zero

	if (saleAmt < 0) {

		// Error message if below 0

		cout << "Error, invalid sales amount entered." << endl;

	}
	else
	{
		// Runs the function getMenuItem with saleAmt as it's parameter and assignes the value to menuChoice

		menuChoice = getMenuItem(saleAmt);

		// Runs the function getTipAmt with menuChoice, saleAmt, and errorDetect as it's parameters.
		// It assigns the result to tipAmt

		tipAmt = getTipAmt(menuChoice, saleAmt, errorDetect);

		// Check to see if the menuChoice or custom amounts entered were valid.
		// If it is invald the program ends, if it's valid the following code runs.

		if (errorDetect == 0) {

			// Calculates the total sale using the function calcTotalSale.

			totalSale = calcTotalSale(saleAmt, tipAmt);

			// Outputs the sale amount entered by the user, the tip amount selected by the user, and the calculated total due.

			cout << "Sales Amount: $" << fixed << setprecision(2) << saleAmt << endl;
			cout << "Tip Amount: $" << fixed << setprecision(2) << tipAmt << endl;
			cout << "Total Due: $" << fixed << setprecision(2) << totalSale << endl;

		}
	}
}


/* This function calculates the tip amount by
*  multiplying the sale amount and a decimal 
*  percentage of tip percent.
* Parameters: saleAmt, tipPercent
* Outputs: tipAmt
*/

double calcTipAmt(double saleAmt, double tipPercent)
{
	double tipAmt = saleAmt * tipPercent/100.0;

	return tipAmt;
}

/* This function calculates the total sale
*  by adding the saleAmt and tipAmt.
* Parameters: saleAmt, tipAmt
* Outputs: totalSale
*/

double calcTotalSale(double saleAmt, double tipAmt)
{
	double totalSale = saleAmt + tipAmt;

	return totalSale;
}

/* This function uses the sale amount to display a menu
*  that contains letters the user can input, as well as what
*  each percentage of tip the price would be.
* Parameters: saleAmt
* Outputs: menuChoice
*/

char getMenuItem(double saleAmt)
{
	char menuChoice;

	cout << "\t\t\tTip Calculator" << endl << endl;
	cout << "\tT - 10 percent tip of $" << fixed << setprecision(2) << calcTipAmt(saleAmt, 10) << endl;
	cout << "\tF - 15 percent tip of $" << fixed << setprecision(2) << calcTipAmt(saleAmt, 15) << endl;
	cout << "\tW - 20 percent tip of $" << fixed << setprecision(2) << calcTipAmt(saleAmt, 20) << endl;
	cout << "\tP - Custom tip percentage " << endl;
	cout << "\tA - Custom tip amount " << endl;
	cout << "Enter your menu choice [T, F, W, P, A]: ";
	
	cin >> menuChoice;

	return menuChoice;
}

/* This functions uses the users menu choice to output the tip amount
*  they desire using a switch statement. If the function recieves an
*  invalid input it sets error detect to 1 which ends the program.
* Parameters: menuCHoice, saleAmt, errorDetect
* Outputs: tipAmt, errorDetect
*/

double getTipAmt(char menuChoice, double saleAmt, bool& errorDetect)
{
	double tipPerc, tipAmt = 0;

	switch (menuChoice)
	{

		// Ten Percent

	case 'T':
	case 't':

		tipAmt = calcTipAmt(saleAmt, 10);

		break;

		// Fifteen Percent

	case 'F':
	case 'f':

		tipAmt = calcTipAmt(saleAmt, 15);

		break;

		// Twenty Percent

	case 'W':
	case 'w':

		tipAmt = calcTipAmt(saleAmt, 20);

		break;

		// Custom Percent

	case 'P':
	case 'p':

		cout << "Enter the tip percentage." << endl;
		cin >> tipPerc;

		// Checks for valid percentage, sets errorDetect to 1 if needed

		if (tipPerc < 0) 
		{

			cout << "Error, invalid percentage entered." << endl
				<< "Valid percentages are non-negative." << endl;
			errorDetect = 1;
		}
		else
		{

			tipAmt = calcTipAmt(saleAmt, tipPerc);

		}
		break;

		// Custom Amount

	case 'A':
	case 'a':

		cout << "Enter the tip amount." << endl;
		cin >> tipAmt;

		// Checks for valid amount, sets errorDetect to 1 if needed

		if (tipAmt < 0) 
		{
			cout << "Error, invalid tip amount entered." << endl
				<< "Valid amounts are non-negative." << endl;
			errorDetect = 1;
		}

		break;

		// Error

	default:

		cout << "Error, invalid menu choice entered." << endl;
		errorDetect = 1;

		break;

	}

	return tipAmt;

}