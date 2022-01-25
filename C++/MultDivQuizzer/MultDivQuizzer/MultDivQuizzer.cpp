/* This function prompts the user to select either a multiplication quiz or a division quiz. After selecting one,
*  the user will be prompted with 10 different problems one at a time with numbers ranging from 1 through 9.
*  After answering all 10 questions the user will then be shown their score and be given the chance to to another
*  quiz or exit the program.
*/

#include<iostream>
using namespace std;

// Function prototypes, full ones found below main in order

int getMenuChoice();
void multiplicationQuiz();
void divisionQuiz();

int main()
{
	// Seed randomization, zybooks will input the seed

	unsigned seed;

	cin >> seed;
	srand(seed);

	// Declaring variable menuChoice

	int menuChoice = 0;
		
	// The loop will continue so long as menuChoice is not 3 (exit program)

	while (menuChoice != 3) {

		// Setting menu choice to whatever value getMenuChoice outputs

		menuChoice = getMenuChoice();

		// If menuChoice is 1, call the function multiplicationQuiz,
		// If menuChoice is 2, call the function divisionQuiz,
		// If menuChocie is anything else do nothing and loop back.

		switch (menuChoice) {

		case 1:
			multiplicationQuiz();
			break;

		case 2:
			divisionQuiz();
			break;

		default:
			break;

		}
	}

	return 0;
}

/* This function prompts the with a menu to choose what quiz they'd like 
*  to take or if they'd like to leave the program. If they enter an 
*  invalid entry then the program will prompt them again.
* Parameters: None
* Returns: choice
*/

int getMenuChoice()
{
	// Declaring variables loopPass and choice.

	bool loopPass = 0;
	int choice;

	// While loopPass is set to zero, repeat everything inside

	while (loopPass == 0) {

		// The menu below prompts the user to input a value between 1 and 3 inclusive.
		// 1 for a multiplication quiz, 2 for a division quiz, and 3 to end the program

		cout << "\t\t\tMATH QUIZ" << "\n\n";

		cout << "\t1 - Multiplication Quiz" << endl;
		cout << "\t2 - Division Quiz" << endl;
		cout << "\t3 - End Program" << "\n\n";
		cout << "Enter the number of your choice: ";

		cin >> choice;
		
		// If the choice is less than 1 or greater than 3,
		// display an error message and keep looping

		if (choice < 1 || choice > 3) {

			cout << "Invalid entry.\n\n";

		}
		else
		{
			// If the choice is valid stop looping

			loopPass = 1;
		}

	}

	// Send back the valaue that the user chose

	return choice;
}

/* This function will prompt the user with 10 randomly generated multiplication
*  questions that range from numbers 1 through 9. If the user inputs a correct
*  answer it congratulates them. If the answer is incorrect it shows them the
*  correct answer. At the end it shows how many questions the user got correct.
* Parameters: None
* Returns: None
*/

void multiplicationQuiz()
{
	// Declaring 5 integers. num1 and num2 for the inputs of the problem, answer as the output, 
	// userAns as what the user enters, and amtCorrect to track how many were correct

	int num1, num2, answer, userAns;
	int amtCorrect = 0;

	// Loop through the code 10 times

	for (int i = 0; i < 10; i++)
	{
		// Set num1 and num2 to a random number between 1 and 9

		num1 = rand() % 9 + 1, num2 = rand() % 9 + 1;

		// Answer is num1 multiplied by num2

		answer = num1 * num2;

		// Prompt the user for what num1 multiplied by num2 is

		cout << "\nQuestion " << (i + 1) << ": What is " << num1 << " x " << num2 << "? ";
		cin >> userAns;

		// Check to see if the answer matches the calculated one

		if (userAns == answer) {

			// If correct, congradulate and increment correct tracker by one

			cout << "\nYou are correct!" << endl;
			amtCorrect++;
		}
		else
		{
			// If incorrect, show correct answer to problem

			cout << "\nYou are incorrect! " << num1 << " x " << num2 << " = " << answer << endl;

		}
	}

	// Display to the user how many questions they got correct out of 10

	cout << "\nYou got " << amtCorrect << " out of 10 answers correct.\n\n";

}

/* This function will prompt the user with 10 randomly generated division
*  questions that range from numbers 1 through 9. If the user inputs a correct
*  answer it congratulates them. If the answer is incorrect it shows them the
*  correct answer. At the end it shows how many questions the user got correct.
* Parameters: None
* Returns: None
*/

void divisionQuiz()
{

	// Declaring 5 integers. num1 and num2 for the inputs of the problem, answer as the output, 
	// userAns as what the user enters, and amtCorrect to track how many were correct

	int num1, num2, answer, userAns;
	int amtCorrect = 0;

	// Loop through the code 10 times

	for (int i = 0; i < 10; i++)
	{
		// Set num1 and num2 to a random number between 1 and 9

		num1 = rand() % 9 + 1, num2 = rand() % 9 + 1;

		// answer is num1 multiplied by num2

		answer = num1 * num2;

		// Prompt the user for what answer divided by num1 is

		cout << "\nQuestion " << (i + 1) << ": What is " << answer << " / " << num1 << "? ";
		cin >> userAns;

		// Check to see if the answer matches the randomly generated one

		if (userAns == num2) {

			// If correct, congradulate and increment correct tracker by one

			cout << "\nYou are correct!" << endl;
			amtCorrect++;
		}
		else
		{
			// If incorrect, show correct answer to problem

			cout << "\nYou are incorrect! " << answer << " / " << num1 << " = " << num2 << endl;

		}
	}

	// Display to the user how many questions they got correct out of 10

	cout << "\nYou got " << amtCorrect << " out of 10 answers correct.\n\n";

}