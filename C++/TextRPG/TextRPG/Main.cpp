#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>

#include "Stats.h"
#include "Player.h"
#include "Monster.h"


// -- TODO -- 
//


void IntroFunc(char& userChoice);
void GameStart(char userInput, Player_Class& player);
void GameNew(Player_Class& player);
void GameLoad(); // ## Not done
void GameHelp(); // ## Not done
void GameFunc(Player_Class& playerCharacter);
void GameBattleEncounter(Player_Class& playerCharacter);
void GameBattleLoop(Player_Class& playerCharacter, std::vector<Monster_Class>& monsterEncounter);

int main() {
    char userInput;
    Player_Class playerCharacter;

    srand(time(NULL));

    // Welcome user, determine if new or old char, help menu, quit.

    IntroFunc(userInput);

    // Run character setup or import

    GameStart(userInput, playerCharacter);

    // Run game

    GameFunc(playerCharacter);

    return 0;
}// main


/* Function that starts menu and welcomes player
*/
void IntroFunc(char&userChoice) {
    
    bool isValidChoice = 0;

    // Game title, introduce game
    // ## Find name for thing

    std::cout << "Welcome to..." << std::endl;
    std::cout << "GAMETITLE" << std::endl;
    std::cout << std::endl << std::endl;

    while (isValidChoice == 0) {

        // Prompt user for choice

        std::cout << "\nSelect your option: " << std::endl <<
            "A - Start New Game!" << std::endl <<
            "B - Load Previous Game!" << std::endl <<
            "C - Help!" << std::endl <<
            "D - Quit!" << std::endl;

        std::cin >> userChoice;
        std::cin.ignore();

        std::cout << std::endl;

        // Switch for handling choices

        switch (userChoice) {

        // Send cases to next area for player creation/import

        case 'A':
        case 'a':
        case 'B':
        case 'b':
            isValidChoice = 1;
            break;

        // Help menu for players

        case 'C':
        case 'c':
            isValidChoice = 0;
            GameHelp();
            break;

        // Exit game

        case 'D':
        case 'd':
            isValidChoice = 1;
            exit(0);
            break;

        default:
            std::cout << "That choice is invalid, please try again" << std::endl;
            isValidChoice = 0;
            break;

        }//switch
    
    }//while

}//introFunc

/* This function shows up a help menu explaining stats.
*/
// ## Rework this later to be more accurate with stats.
void GameHelp() {

    std::cout << "HELP MESSAGE" << std::endl;
    std::cout << "Stats:" << std::endl <<
        "HiP - The amount of hitpoints you have. A point here would give 15 HP" << std::endl <<
        "Atk - The amount of damage you deal. A point here would give +3 attack" << std::endl <<
        "Def - Logarithmically reduces incoming damage." << std::endl <<
        "Eva - Logarithmically gives chance to negate a precentage damage." << std::endl <<
        "Spe - Frequency of attacks relative to enemy, higher speed goes first, if you have double their speed you're going 2 turns per 1 of theirs, if you have 4/3's their speed you get an extra turn for every three of theirs." << std::endl <<
        "Wil - Willpower, Hp regen out of combat and mana regen at all times" << std::endl <<
        "Int - Intelligence, capability of doing ability based attacks" << std::endl <<
        "Res - Resourcefulness, determines quantity of loot scaveneged" << std::endl <<
        "Luc - Luck, Boosts quality of loot and chances of specific things. In cases that loot cannot have its quality increased, luck increases the chance of it being dropped or found";
    std::cout << std::endl << std::endl;
} // Help func
    
/* This function determines if the player should go throguh the creation process or import process
*/
// ## Probably obselete, just move these functions into other IntroFunc
void GameStart(char userInput, Player_Class& player) {

    // Select which option the character will be doing to assign stats 
    if (userInput == 'A' || userInput == 'a') {

        // Create new character and show stats

        GameNew(player);
        player.showStats();


    }// if
    if (userInput == 'B' || userInput == 'b') {

        // Import character and show stats
        
        GameLoad();
        player.showStats();

    }// if


}// Game start

/* This function handles creating a new character. It is intended to offer templates and custom character creation.
*  In addition the character should be able to press D to display the stats of the template, and S to select the choice.
*/
// ## Add in character selection functionality. Create a manniquen object to model stats for show stats.
// ## Maybe load player classes into an array somehow?
// ## At worst cry and make a bunch of nested switch statements
void GameNew(Player_Class& player) {
    char input;
    bool loopPass = 0;

    while (loopPass == 0) {
        std::string nameInput;

        // Have the player create a new character and assign stats/abilities
        
        // ## not done
        std::cout << "Name your character!" << std::endl;
        getline(std::cin, nameInput);
        player.setStatName(nameInput);
        std::cout << std::endl;
        std::cout << "Choose your class. Press a number, and then press D to display or S to select." << std::endl;
        player.setPlayerBarbarian();

        std::cout << "Are you satisfied with your choice? Y/N" << std::endl;
        std::cin >> input;
        std::cout << std::endl;
        std::cin.ignore();

        if (input == 'Y' || input == 'y') {
            loopPass = 1;
        } // if
    }// while


}// Game new

/* This functions purpose is to handle reading files and assigning character values into the text file.
*  The player should be able to select the name of their file that they are 
*/
// ## have a game save function that writes a file that the user names.
void GameLoad() {

    //Have it read in a save file to assign stats
    std::cout << "I DO NOTHING RIGHT NOW";


}// Game load

/* This is the main function that runs the game. It should handle all out of combat areas
*  Any combat encounters should be handled in a function like GameEncounter, which will handle
*  construction and deconstruction of all mobs
*/
// ## Create the encounter function. Once random battles are established do out of battle things
void GameFunc(Player_Class& playerCharacter) {

    // Two encounters, refills characters stats in between

    GameBattleEncounter(playerCharacter);
    playerCharacter.setStatHitPoints(100);
    playerCharacter.setStatMana(10);
    playerCharacter.setStatusIsAlive(1);
    GameBattleEncounter(playerCharacter);

    std::cout << "\n\n\n Thank you for completing the test. Feel free to try and break the game as much as possible and tell me what happens." <<
        "\n I plan on adding more soon! Stay tuned.\n\n";

}

/* This function is the encounter function, used to handle spawning and despawning enemies, as well as running the battleloop function
*  It should be used once per battle, and a new encounter should be run for a new set of enemies.
*/
void GameBattleEncounter(Player_Class& playerCharacter) {

    char userInput;

    // Temporary code. Most code should be followed by:
    // Monster creation, prompt for user, proceed to battle

    Monster_Class Goblin1;
    Monster_Class Goblin2;
    Monster_Class Goblin3;

    // Initializing three goblin stats

    Goblin1.monsterSetStats(1, "Angry Goblin", "A small angry goblin who wants to beat you up", 11, 11, 5, 2, 11);
    Goblin2.monsterSetStats(2, "Sad Goblin", "A small sad goblin who wants to beat you up", 10, 10, 4, 0, 4);
    Goblin3.monsterSetStats(3, "Timid Goblin", "A small timid goblin who doesn't really want to beat you up", 9, 9, 3, 1, 8);
    
    // Add to vector

    std::vector<Monster_Class> GoblinGang;
    GoblinGang.push_back(Goblin1);
    GoblinGang.push_back(Goblin2);
    GoblinGang.push_back(Goblin3);

    std::cout << "Oh no! An Angry goblin wishes to attack you!" << std::endl;
    std::cout << "A - Show stats" << std::endl <<
        "B - Proceed" << std::endl;

    std::cin >> userInput;
    std::cin.ignore();
    std::cout << std::endl;

    // Run the battle function

    GameBattleLoop(playerCharacter, GoblinGang);

    // ## Run a loot function or something like that
    // Set turn tick back to zero.
    playerCharacter.setValTurnTick(0);
    
}

/* This function handles the actual combat loop and turns.
*  It runs the speed checks, handles turn orders, and runs battle menu functions.
*  The function takes vectors as the input for the monsters rather than dynamic arrays.
*  This allows for an easier time finding the size of the array, and easier initialization.
*/
void GameBattleLoop(Player_Class& playerCharacter, std::vector<Monster_Class>& monsterEncounter) {
    
    unsigned int turn = 0;
    bool isWholeEnemyDead = false;
    int monsterTarget;
    int monsTurn = 0;
    std::vector<int> monstTurnVect;
    

    // Create vector and load player + monsters into it, player always goes in index 0

    std::vector<Stats_Class>turnOrder;
    turnOrder.push_back(playerCharacter);

    for (unsigned int i = 0; i < monsterEncounter.size(); i++) {

        turnOrder.push_back(monsterEncounter[i]);

    }

    // Run a bubble sort by the speed to organize turn order.

    for (unsigned int i = 1; i < turnOrder.size(); i++) {
        for (unsigned int j = 0; j < turnOrder.size() - 1; j++) {

            if (turnOrder[j+1].getStatSpeed() > turnOrder[j].getStatSpeed()) {

                Stats_Class temp = turnOrder[j];
                turnOrder[j] = turnOrder[j+1];
                turnOrder[j+1] = temp;

            }

        }
    }

    // Translate turnOrder[turn] into monsterEncounter[monsTurn]
    /* At this point turnOrder has already been sorted.
    *  Run through all of turn order, compare it to every id in monster encounter.
    *  If there is a match, push it into the stack, add in monster encounter [i]
    *  If there was not a match, add in a -1 so the size will be the same and the
    *  monstTurnVect can still be accessed  by using [turn] later
    */

    for (int j = 0; j < turnOrder.size(); j++) {

        bool didStack = 0;

        for (int i = 0; i < monsterEncounter.size(); i++) {

            // Compare every monsterEncounter element to turnOrder element

            if (turnOrder[j].getValEntID() == monsterEncounter[i].getValEntID()) {

                // Add to monstTurn vector

                monstTurnVect.push_back(i);
                didStack = 1;
            }

        }

        // If there was no match, add a -1, this should intentionally crash the program if anything goes wrong with accessing the order.

        if (didStack == 0) {

            monstTurnVect.push_back(-1);

        }

    }

    // Actual battle loop

    while (playerCharacter.getStatusIsAlive() == true && isWholeEnemyDead == false) {

        // Loops the turn counter around when reached end of vector

        if (turn > turnOrder.size() - 1) {

            turn = 0;

        }

        // Set the global random val to a random number.
        Stats_Class::globalRandVal = rand() % 100;

        // Rather than checking if everything is dead, we just check if something is alive.
        // If not, then isWholeEnemyDead remains true.
        // ## might be a way to change for loop into while loop.
        isWholeEnemyDead = true;
        for (int i = 0; i < monsterEncounter.size(); i++) {

            // Second part of condition just skips resetting the value if it's already alive
            if (monsterEncounter[i].getStatusIsAlive() == true || isWholeEnemyDead == false) {
                
                isWholeEnemyDead = false;

            }

        }

        // Choose battle menu based off of entity ID
        // ## there's probably a better way to update turnOrder[turn]'s status of get current turn
        if (turnOrder[turn].getValEntID() == playerCharacter.getValEntID()) {

            // Select target and assign to monster target, then run player battle menu

            monsterTarget = playerCharacter.playerMenuSelector(monsterEncounter);
            playerCharacter.playerMenuBattle(playerCharacter, monsterEncounter[monsterTarget]);
  
            // Updates the turnOrder stat
            turnOrder[turn].setStatusIsCurrentTurn(playerCharacter.getStatusIsCurrentTurn());

        } else {

            // Match up the turn with the monster in encounter

            monsTurn = monstTurnVect[turn];

            // Check and make sure monster is alive

            if (monsterEncounter[monsTurn].getStatusIsAlive() == 1) {
                
                // Run monster encounter and update turnOrder stats

                monsterEncounter[monsTurn].monsterBattleMenu(monsterEncounter[monsTurn], playerCharacter);
                turnOrder[turn].setStatusIsCurrentTurn(monsterEncounter[monsTurn].getStatusIsCurrentTurn());
            }
            else {

                /* It might seem redundent to do this, after all, every ability sets the turn to 0 and the BattleMenu is what sets the turn back to 1
                *  However, in the case that a monster is slain before it is able to use an ability, it never uses its turn which prevents the game from
                *  advancing unless this is done.
                */

                turnOrder[turn].setStatusIsCurrentTurn(0);

            }
        }
        
        // This makes it so if the battle menu has occured but the player hasnt ended their turn, it redoes the
        // Selection and execution process.

        if (turnOrder[turn].getStatusIsCurrentTurn() == 0) {

        turn++;

        }
    }

    // End text

    std::cout << std::endl <<
        "-------------------" << std::endl <<
        "The battle is over!" << std::endl <<
        "-------------------" << std::endl << std::endl;

    playerCharacter.addItemMoney(15);
    std::cout << "You got 15 gold! You now have " << playerCharacter.getItemMoney() << " gold!" << std::endl << std::endl;

}