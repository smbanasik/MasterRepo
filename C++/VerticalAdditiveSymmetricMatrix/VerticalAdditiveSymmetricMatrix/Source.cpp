/*
    Program Name: Vertical Additive Symmetric Matrix
    Date:		  2021-06-04
    Author:		  Spencer Banasik

    Program Purpose
    The purpose of thise program is to read in matricies, calculate the sum of their columns,
    check if they have vertical symmetry, and then sort the rows.

    Module Design Description
    The program uses a bubble sort to sort the rows.

    Inputs:
    matrixes.txt - a file containing the matricies to be read.

    Outputs:
    A display of the matrix, column sums, if it's vertically symmetrical,
    and the sorted matrix

*/

#include<iostream>;
#include<iomanip>;
#include<fstream>;
#include<string>;
#include <stdio.h>

using namespace std;

const int MAX_SIZE = 20;
const int TEXT_WIDTH = 8;

bool readMatrix(ifstream& inputFile, int matrixArray[][MAX_SIZE], string fileName, int& height, int& width);
void displayMatrix(int matrixArray[][MAX_SIZE], int height, int width);
void displaySums(int matrixArray[][MAX_SIZE], int height, int width);
void symmetryCheck(int matrixArray[][MAX_SIZE], int height, int width);
void matrixSort(int matrixArray[][MAX_SIZE], int height, int width);

int main() {

    bool loopIsStop = 0;
    int height, width;
    int matrixArray[MAX_SIZE][MAX_SIZE];
    string inputFileName = "matrixes.txt";

    ifstream readFile;

    readFile.open(inputFileName);
    if (readFile.good()) {
        do {

            // When the readMatrix function hits the end of the file it will set loopIsStop to 1 and end the loop

            loopIsStop = readMatrix(readFile, matrixArray, inputFileName, height, width);
            if (loopIsStop == 1)
                break;

            // These functions handle displaying values, calculating sums, checking for symmetry, and sorting the array.

            displayMatrix(matrixArray, height, width);
            displaySums(matrixArray, height, width);
            symmetryCheck(matrixArray, height, width);
            matrixSort(matrixArray, height, width);

            // The program will pause here until the user presses enter twice. Then it will mvoe on to the next array.

            cout << "\nPress the enter key once or twice to continue..." << endl;
            cin.ignore();
            cin.get();
        } 
        while (true);
    }
    else {

        // Error message if file is unable to be accessed

        cout << "File " << inputFileName << " could not be opened!" << endl;
        cout << "\nPress the enter key once or twice to continue..." << endl;

    }
    readFile.close();

    return 0;
    
}

/* This function reads input from a file. The first two values it reads are assigned to the width and height,
*  and based off of those contents an array is built using the next inputted numbers. If the the function finds
*  that the end of the file has been reached, it doesn't set the loopIsStop to zero which halts the loop.
*/

bool readMatrix(ifstream& inputFile, int matrixArray[][MAX_SIZE], string fileName, int& height, int& width) {

    bool loopIsStop = 1;

    // If we've reached the end of the file then the all the function does is signal for the loop to end

    if (!inputFile.eof()) {

        // The first two values inputted will determine the dimension of the matrix

        inputFile >> height;

        inputFile >> width;

        // Fill in the array with the remaining numbers according to the dimensions

        for (int row = 0; row < height; row++) {
            for (int column = 0; column < width; column++) {

                inputFile >> matrixArray[row][column];

            }
        }

        // If we haven't reached the end of the file then there we must continue the loop

        loopIsStop = 0;
    }
    return loopIsStop;
}

/* This function cycles through the given array and displays the contents.
*/

void displayMatrix(int matrixArray[][MAX_SIZE], int height, int width) {

    cout << "Input:" << endl;

    // Displays the numbers with a width according to TEXT_WIDTH, each row ends with a new line.

    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {

            cout << setw(TEXT_WIDTH) << matrixArray[row][column];
            
        }

        cout << endl;
    }
}

/* This function sums up the columns of an array and displays them.
*/

void displaySums(int matrixArray[][MAX_SIZE], int height, int width) {

    int colsum = 0;

    cout << "Sums :" << endl;

    // Cycles through rows in a column while adding up the elements to get a sum fo the column
    // Displays the sum and moves on to the next column

    for (int column = 0; column < width; column++) {

        colsum = 0;

        for (int row = 0; row < height; row++) {

            colsum += matrixArray[row][column];

        }

        cout << setw(TEXT_WIDTH) << colsum;
    }
        cout << endl;
}


/* This function checks if there's vertical symmetry in the given matrix. It does this by calculating the
*  middle of the matrix and summing up the outer left and right columns. It works inwards and continues to
*  sum columns until it reaches the middle. If at anypoint the two summed columns do not match, it sets symmetry
*  to zero.
*/

void symmetryCheck(int matrixArray[][MAX_SIZE], int height, int width) {

    bool symmetry = 1;
    int leftSum, rightSum, middle;


    middle = width / 2;

    // Starts at the outer edges and moves inwards getting the sum of each column

    for (int column = 0; column < middle; column++) {

        leftSum = 0;
        rightSum = 0;

        for (int row = 0; row < height; row++) {

            leftSum += matrixArray[row][column];
            rightSum += matrixArray[row][(width - 1) - column];

        }

        // If any of the columns through out the loop do not match then the matrix is asymmetric

        if (leftSum != rightSum)
            symmetry = 0;

    }

    // Display whether the matrix has vertical additive symmetry

    cout << "\nVertical additive symmetry : ";

    if (symmetry == 1) {

        cout << "Yes";
    }
    else {

        cout << "No";
    }

    cout << endl;
}

/* This function sorts through the array's rows and organizes it from least to greatest. It uses the bubble sort method.
*  The function then displays the sorted array.
*/
void matrixSort(int matrixArray[][MAX_SIZE], int height, int width) {

    bool loopIsStop = 0;
    int temp;

    // Uses a bubble sort ofr each row

    for (int row = 0; row < height; row++) {

        // Loops through the specified row as many times as necessary to carry out the bubble sort

        do {

            // By default the loop will stop, but if there's at least one sort made there's the potential for another sort to be made
            // Only when the if statement does not run can the loop end

            loopIsStop = 1;

            for (int column = 0; column < width - 1; column++) {
        
                temp = 0;

                // The actual code that performs the bubble sort.
                // If the space to the right of our selected element is lesser, then we stash the original value in a temporary
                // Variable, move the lesser element to the original spot, and put the temporary value into the slot to the right

                if (matrixArray[row][column] > matrixArray[row][column + 1]) {

                    temp = matrixArray[row][column];
                    matrixArray[row][column] = matrixArray[row][column + 1];
                    matrixArray[row][column + 1] = temp;

                    loopIsStop = 0;
                }
            
            }
        } while (loopIsStop == 0);
    }

    // Once the array has been sorted, display the array

    cout << "\nSorted: " << endl;
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {

            cout << setw(TEXT_WIDTH) << matrixArray[row][column];

        }

        cout << endl;
    }
}