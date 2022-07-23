#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// 7/23/2022 I need a program that can write basically the same json file with many variations.
// We're going to read in a json file, then change what we need to.
// Any words needing to be replaced should be repleaced with the keyword constant

std::vector<std::string> readInputArr(std::string filename);
std::vector<std::string> readJSONFormat(std::string jsonName);
void printFiles(std::vector<std::string> jsonFormat, std::vector<std::string> inputArr);

// Change to a format appropriate for what is needed. In my case, no words are going to be capitalized in this manner.
const std::string KEYWORD = "CHANGEME";
const std::string INVALID_NAME_CHARS = "*.\":/\\[];|,";

int main() {

    std::vector<std::string> jsonFormat, inputArr;
    std::string jsonName, inputArrName;

    std::cout << "Input the name of the input array, be sure to include the file extension" << std::endl;
    std::cin >> inputArrName;

    inputArr = readInputArr(inputArrName);

    std::cout << "Input the name of the json file to read, be sure to include the file extension" << std::endl;
    std::cin >> jsonName;

    jsonFormat = readJSONFormat(jsonName);

    printFiles(jsonFormat, inputArr);

    std::cout << "Files have been created." << std::endl;

    return 0;
}

// Gathers up the array that will be inputted into the json format
std::vector<std::string> readInputArr(std::string fileName) {

    std::vector<std::string> inputArr;
    std::ifstream inputArrFile;

    inputArrFile.open(fileName);
    if (inputArrFile.is_open()) {

        std::string buffer;

        // Format should be value \n
        while (std::getline(inputArrFile, buffer)) {

            inputArr.push_back(buffer);

        }

        std::cout << "Input array created!" << std::endl;
        inputArrFile.close();
    }
    else {

        std::cout << "File unable to be opened!" << std::endl;
    }

    return inputArr;
}

// Read in a file to gain the json format.
std::vector<std::string> readJSONFormat(std::string fileName) {

    std::vector<std::string> jsonFormat;
    std::ifstream inputJSONFile;

    inputJSONFile.open(fileName);
    if (inputJSONFile.is_open()) {

        std::string buffer;

        // Format should be value \n
        while (std::getline(inputJSONFile, buffer)) {

            jsonFormat.push_back(buffer);

        }

        std::cout << "JSON format has been read!" << std::endl;
        inputJSONFile.close();
    }
    else {

        std::cout << "File unable to be opened!" << std::endl;
    }

    return jsonFormat;
}


// Loop through input array and json format, scan json format for keyword and replace, output file.
void printFiles(std::vector<std::string> jsonFormat, std::vector<std::string> inputArr) {

    std::string buffer;
    std::size_t stringPos;
    std::string fileName;

    for (int i = 0; i < inputArr.size(); i++) {

        // Make sure that the inputted data is acceptable as a file name
        fileName = inputArr.at(i);
        for (int k = 0; k < INVALID_NAME_CHARS.size(); k++) {

            stringPos = fileName.find(INVALID_NAME_CHARS[k]);
            if (stringPos != std::string::npos) {

                fileName.replace(stringPos, 1, "_");
            }

        }

        std::ofstream outputFile(fileName + ".json");
        if (outputFile.is_open()) {

            // Go through and create the format
            for (int j = 0; j < jsonFormat.size(); j++) {

                // Put the json format into a buffer
                buffer = jsonFormat.at(j);

                // Scan for the keyword, if keyword is found, put in the input arr instead
                stringPos = buffer.find(KEYWORD, 0);
                if (stringPos != std::string::npos) {

                    buffer.replace(stringPos, KEYWORD.length(), inputArr.at(i));

                }

                // Output buffer
                outputFile << buffer + "\n";

            }

            std::cout << "File " + inputArr.at(i) + ".json created!" << std::endl;
            outputFile.close();
        }
        else {

            std::cout << "File " + inputArr.at(i) + ".json unable to be created!" << std::endl;

        }

    }


}