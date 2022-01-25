/*
    Program Name: Satellite
    Date:		  2021-06-18
    Author:		  Spencer Banasik

    Program Purpose
    This program reads in data from an input file and stores it in an array.
    When the command to display the data is called the program checks its information type,
    displays the appropriate values, and then display a summary of all of the values.

    Module Design Description
    This program uses strucutres to organize the data and assigne information types used in sorting.
    The program uses enum classes for message types and information types.
    The message types provide readability and the information types allow elements in the array to be categorized.

    Inputs:
    inputDataAntenna.txt - a file containing a vertical list of numbers that consists of commands for the program and data values

    Outputs:
    A display of the individual readings as well as a summary of the information.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<stdint.h>

using namespace std;

#define GroundStationOutputChannel cout

// File name for input & Maximum size for arrays

const string TELEMETRY_RECIEVER_INPUT_CHANNEL = "inputDataAntenna.txt";
const uint8_t ARRAY_MAX_SIZE = 5;

struct StatusInformation {

     float_t temperature,
             voltage;
};

struct ExperimentInformation {

    // While uint8_t has a limit of 255 which is over the limits of 200 and 100 for the counts, 
    // attempting to use this causes the program to misread the radiation and latchup count.

    uint16_t radiationCount,
            latchUpEventsCount;

};

union MasterUnion {

    StatusInformation statusInformation;
    ExperimentInformation experimentInformation;

};

enum class InformationType {

    STATUS_INFORMATION,
    EXPERIMENT_INFORMATION,
    EMPTY

};

enum class MessageType {

    SI_MESSAGE = 1,
    EI_MESSAGE = 2,
    SEND_INFO = 3

};

struct MasterInformation {

    InformationType informationType;
    MasterUnion masterUnion;

};

void workStatusInformationMessage(ifstream& telemetryInputAntennaReceiverChannel, InformationType& informationType,
    MasterInformation& masterInformation, uint8_t& positionIndex, MasterInformation* informationStorageArray);

void workExperimentInformationMessage(ifstream& telemetryInputAntennaReceiverChannel, InformationType& informationType,
    MasterInformation& masterInformation, uint8_t& positionIndex, MasterInformation* informationStorageArray);

void workSendInformation(MasterInformation* informationStorageArray);

int main() {

    MasterInformation informationStorageArray[ARRAY_MAX_SIZE];
    MasterInformation masterInformation;
    uint8_t positionIndex = 0;
    uint16_t messageInput;
    MessageType messageType;

    ifstream telemetryInputAntennaReceiverChannel;

    telemetryInputAntennaReceiverChannel.open(TELEMETRY_RECIEVER_INPUT_CHANNEL);
    if (telemetryInputAntennaReceiverChannel.fail()) {

        // Error message if file is unable to be accessed

        cout << "File " << TELEMETRY_RECIEVER_INPUT_CHANNEL << " could not be opened!" << endl;
        cout << "\nPress the enter key once or twice to continue..." << endl;
        cin.ignore(); cin.get();
        exit(EXIT_FAILURE);

    }

    // Assign every value in the array as information type empty. In the case that the display  
    // command is called before all 5 values are filled, the program knows which elements to skip

    for (uint8_t i = 0; i < ARRAY_MAX_SIZE; i++) {

        informationStorageArray[i].informationType = InformationType::EMPTY;

    }

    // Main loop for satellite, runs as long as there is input in the file

    while (telemetryInputAntennaReceiverChannel >> messageInput) {

        // When a number between 1 and 3 (inclusive) is read, use it as the index for the MessageType enum class and assign messageType to it.

        messageType = MessageType(messageInput);

        switch (messageType) {

        // When a 1 is reached in the input file, run the function below to assign the next two values as a part of status information

        case MessageType::SI_MESSAGE:
            workStatusInformationMessage(telemetryInputAntennaReceiverChannel, masterInformation.informationType, masterInformation, positionIndex, informationStorageArray);
            break;

        // When a 2 is reached in the input file, run the following function to assign the next to values as a part of the experiment information

        case MessageType::EI_MESSAGE:
            workExperimentInformationMessage(telemetryInputAntennaReceiverChannel, masterInformation.informationType, masterInformation, positionIndex, informationStorageArray);
            break;
        
        // When a 3 is reached in the input file, run the function to display everything

        case MessageType::SEND_INFO:
            workSendInformation(informationStorageArray);
            
            break;

        }

    }
    
    // Close the input file when finished and exit the program.

    telemetryInputAntennaReceiverChannel.close();
    return 0;
}

/* This function sets the information type to STATUS_INFORMATION, reads in two values, and then
*  assigns all of this to an element in the storage array. It also manages the position index.
*/

void workStatusInformationMessage(ifstream& telemetryInputAntennaReceiverChannel, InformationType& informationType,
    MasterInformation& masterInformation, uint8_t& positionIndex, MasterInformation* informationStorageArray) {

    // Set the information type of the masterInformation variable to Status Info

    informationType = InformationType::STATUS_INFORMATION;

    // Read in the next two lines for temperature and voltage respectively

    telemetryInputAntennaReceiverChannel >> masterInformation.masterUnion.statusInformation.temperature
                                         >> masterInformation.masterUnion.statusInformation.voltage;

    // Assign the information type and the two values to the index in the array

    informationStorageArray[positionIndex] = masterInformation;

    // If the array is in the 5th position, loop back to 0 for the next element, if not increment.

    if (positionIndex == ARRAY_MAX_SIZE - 1) {

        positionIndex = 0;
    }
    else {

        ++positionIndex;

    }

}

/* This function sets the information type to EXPERIMENT_INFORMATION, reads in two values,
*  and then assigns all of this to an element in the storage array. It also manages the position index.
*/

void workExperimentInformationMessage(ifstream& telemetryInputAntennaReceiverChannel, InformationType& informationType,
    MasterInformation& masterInformation, uint8_t& positionIndex, MasterInformation* informationStorageArray) {

    // Set the information type of the masterInformation variable to Experiment Info

    informationType = InformationType::EXPERIMENT_INFORMATION;

    // Read in the next two lines for radiation count and latch up events count respectively

    telemetryInputAntennaReceiverChannel >> masterInformation.masterUnion.experimentInformation.radiationCount
        >> masterInformation.masterUnion.experimentInformation.latchUpEventsCount;

    // Assign the information type and the two values to the index in the array

    informationStorageArray[positionIndex] = masterInformation;

    // If the array is in the 5th position, loop back to 0 for the next element, if not increment.

    if (positionIndex == ARRAY_MAX_SIZE - 1) {

        positionIndex = 0;
    }
    else {

        ++positionIndex;

    }

}

/* This function displays the values of the individual readings and a summary of all of the values.
*  The function calculates the totals of values and the minimum and maximum values of temperature and voltage.
*/

void workSendInformation(MasterInformation* informationStorageArray) {

    float_t minTemp = 212, maxTemp = -50,
        minVolt = 100, maxVolt = 0;

    uint16_t totalRadCount = 0,
        totalLatchupEventCount = 0,
        totalSIMessageCount = 0,
        totalEIMessageCount = 0;

    // Formatting

    GroundStationOutputChannel << setprecision(1) << fixed << showpoint;

    for (uint8_t i = 0; i < ARRAY_MAX_SIZE; i++) {

        // Check to see what the information type attached to the index is

        switch (informationStorageArray[i].informationType) {

        // If the information type is experiment information, display the values, add to the message count, and set minimum and maximum values

        case InformationType::STATUS_INFORMATION:
                totalSIMessageCount++;
                GroundStationOutputChannel << "Temperature : " << informationStorageArray[i].masterUnion.statusInformation.temperature << endl;
                GroundStationOutputChannel << "Voltage     : " << informationStorageArray[i].masterUnion.statusInformation.voltage << endl << endl;
                
                if (maxTemp < informationStorageArray[i].masterUnion.statusInformation.temperature)
                    maxTemp = informationStorageArray[i].masterUnion.statusInformation.temperature;

                if (minTemp > informationStorageArray[i].masterUnion.statusInformation.temperature)
                    minTemp = informationStorageArray[i].masterUnion.statusInformation.temperature;

                if (maxVolt < informationStorageArray[i].masterUnion.statusInformation.voltage)
                    maxVolt = informationStorageArray[i].masterUnion.statusInformation.voltage;

                if (minVolt > informationStorageArray[i].masterUnion.statusInformation.voltage)
                    minVolt = informationStorageArray[i].masterUnion.statusInformation.voltage;
                    break;
                
        // If the information type is experiment information, display the counts and add to totals

        case InformationType::EXPERIMENT_INFORMATION:
                totalEIMessageCount++;
                GroundStationOutputChannel << "Radiation Count     : " << informationStorageArray[i].masterUnion.experimentInformation.radiationCount << endl;
                GroundStationOutputChannel << "Latchup Event Count : " << informationStorageArray[i].masterUnion.experimentInformation.latchUpEventsCount << endl << endl;

                totalRadCount += informationStorageArray[i].masterUnion.experimentInformation.radiationCount;
                totalLatchupEventCount += informationStorageArray[i].masterUnion.experimentInformation.latchUpEventsCount;
                break;
        
        // Skip empty information types

        case InformationType::EMPTY:
            break;
        }
    }
    
    // Printing out the summary information with the total count of readings, total counts of radiation and latchups,
    // And the temperature and voltage minimums and maximums

    GroundStationOutputChannel << "Summary Information" << endl
        << "-------------------" << endl
        << "Number of Satellite  Information Records: " << totalSIMessageCount << endl
        << "Number of Experiment Information Records: " << totalEIMessageCount << endl
        << "Total Radiation Count     : " << totalRadCount << endl
        << "Total Latchup Event Count : " << totalLatchupEventCount << endl
        << "Maximum Temperature       : " << maxTemp << endl
        << "Minimum Tmperature        : " << minTemp << endl
        << "Maximum Voltage           : " << maxVolt << endl
        << "Minimum Voltage           : " << minVolt << endl << endl;

    // Pause after this and then continue after input

    GroundStationOutputChannel << "Press the enter key once or twice to continue..." << endl;
    cin.ignore();
    cin.get();

}