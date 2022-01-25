/*
    Program Name: Sorty By Pointers
    Date:		  2021-06-11
    Author:		  Spencer Banasik

    Program Purpose
    This program reads in arrays from a file and sorts their contents.

    Module Design Description
    The program uses a pointer array to point towards the values of the original array.
    This pointer array is then sorted using a bubble sort.
    Both arrays have their contents displayed.

    Inputs:
    arrayData.txt - a file containing the arrays to be read.

    Outputs:
    A display of the sorted pointer array and the original array to the console.

*/
#include<iostream>;
#include<iomanip>;
#include<fstream>;
#include<string>;
#include<stdio.h>;

using namespace std;

const int MAX_SIZE = 10;
const int TEXT_WIDTH = 6;

bool readIntoDataArray(ifstream& inputFile, int arrayData[MAX_SIZE], int* arrptrArray[MAX_SIZE], int& listSize);
void displayOriginalArray(int arrayData[MAX_SIZE], int size);
void swapIntPtr(int*& numOne, int*& numTwo);
void matrixSort(int* arrptrArray[MAX_SIZE], int size);
void displayPointerArray(int* arrptrArray[MAX_SIZE], int size);

int main() {

    bool loopIsStop = 0;
    int listSize;
    int arrayData[MAX_SIZE];
    int* arrptrArray[MAX_SIZE];

    string inputFileName = "arrayData.txt";

    ifstream inputFile;

    inputFile.open(inputFileName);
    if (inputFile.good()) {
        do {

            // When the readIntoDataArray function hits the end of the file it will set loopIsStop to 1 and end the loop

            loopIsStop = readIntoDataArray(inputFile, arrayData, arrptrArray, listSize);
            if (loopIsStop == 1)
                break;

            // These functions handle sorting the pointer array and displaying the two arrays

            matrixSort(arrptrArray, listSize);
            displayPointerArray(arrptrArray, listSize);
            displayOriginalArray(arrayData, listSize);

            // The program will pause here until the user presses enter twice. Then it will mvoe on to the next array.

            cout << "\nPress the enter key once or twice to continue..." << endl;
            cin.ignore();
            cin.get();
        } while (true);

        // Close inputFile object when done.

        inputFile.close();
    }
    else {

        // Error message if file is unable to be accessed

        cout << "File " << inputFileName << " could not be opened!" << endl;
        cout << "\nPress the enter key once or twice to continue..." << endl;

    }
    return 0;

}

/* This function reads input from a file. The first value that it reads is the size of the list, and based
*  off of the number an array is built using the next numbers that are read in. If the the function finds
*  that the end of the file has been reached, it doesn't set the loopIsStop to zero which halts the loop.
*/

bool readIntoDataArray(ifstream& inputFile, int arrayData[MAX_SIZE], int* arrptrArray[MAX_SIZE], int& listSize) {

    bool loopIsStop = 1;

    // If we've reached the end of the file then the all the function does is signal for the loop to end

    if (!inputFile.eof()) {

        // The first value inputted will determine the size of the array

        inputFile >> listSize;

        // Fill in the array with the remaining numbers according to listSize

        for (int i = 0; i < listSize; i++) {

                inputFile >> arrayData[i];
                arrptrArray[i] = &arrayData[i];
        }

        // If we haven't reached the end of the file then we must continue the loop

        loopIsStop = 0;
    }
    return loopIsStop;
}

/* This function cycles through the given array and displays the contents.
*/

void displayOriginalArray(int arrayData[MAX_SIZE], int size) {

    cout << "\nNow displaying data in the original order" << endl;

    // Displays the numbers with a width according to TEXT_WIDTH.

    for (int i = 0; i < size; i++) {

            cout << setw(TEXT_WIDTH) << arrayData[i];
    }

    cout << endl;

}

/* This function takes two inputted pointers  
*  by reference and swaps their positions
*/

void swapIntPtr(int*& numOne, int*& numTwo) {

    int* tempptr;

    tempptr = numOne;
    numOne = numTwo;
    numTwo = tempptr;

}

/* This function sorts through the array's contents and organizes it from least to greatest.
*  It uses the bubble sort method called from swapIntPtr.
*/

void matrixSort(int* arrptrArray[MAX_SIZE], int size) {

    bool loopIsStop = 0;

    // Loops through the specified row as many times as necessary to carry out the bubble sort

    do {

        // By default the loop will stop, but if there's at least one sort made there's the potential for another sort to be made
        // Only when the if statement does not run can the loop end

        loopIsStop = 1;

        for (int i = 0; i < size - 1; i++) {

            // If the value we're pointing to at the right of our selected element is less than our original element's value,
            // we call swapIntPtr to swap the two pointer values. This performs a sort without modifying the original array's data.

            if (*arrptrArray[i] > *arrptrArray[i + 1]) {

                swapIntPtr(arrptrArray[i], arrptrArray[i + 1]);

                loopIsStop = 0;
            }

        }
    } while (loopIsStop == 0);
}

/* This function cycles through the given pointer array and displays the contents.
*/

void displayPointerArray(int* arrptrArray[MAX_SIZE], int size) {

    cout << "\nNow displaying data in sorted order" << endl;

    // Displays the numbers with a width according to TEXT_WIDTH.

    for (int i = 0; i < size; i++) {

        cout << setw(TEXT_WIDTH) << *arrptrArray[i];
    }

    cout << endl;

}