#include "Player.h"
#include "Monster.h"
#include<iostream>
#include<iomanip>
#include<vector>

// -- Class Assigner Functions --

// ## redo all classes with new stats.

// Attack based class
void Player_Class::setPlayerBarbarian() {
    setStatDescription("A human with high attack and moderate defense. He chooses to defend instead of dodge. His intelligence and resourcefullness are low.");
    setStatEndurance(20);
    setStatAffinity(10);
    setStatHitPoints(100);
    setStatMana(10);
    setStatAttack(10);
    setStatDefense(5);
    setStatEvasion(0);
    setStatSpeed(10);
    setStatWillpower(5);
    setStatIntelligence(3);
    setStatResourcefullness(2);
    setStatLuck(5);
    setStatusIsDefense(1);
    initializeSecondStats();
}

// Defense based class
void Player_Class::setPlayerKnight() {
    setStatDescription("A human with high defense and moderate willpower. She chooses to defend instaed of dodge. Her intelligence and resourcefullnes are low.");
    setStatHitPoints(150);
    setStatAttack(10);
    setStatDefense(20);
    setStatEvasion(0);
    setStatSpeed(10);
    setStatWillpower(15);
    setStatIntelligence(6);
    setStatResourcefullness(6);
    setStatLuck(10);
    setStatusIsDefense(1);
}

// Evasion based class
void Player_Class::setPlayerThief() {
    setStatDescription("An elf with high evasion and moderate speed. She chooses to dodge instead of defend. Her intelligence and willpower are low.");
    setStatHitPoints(75);
    setStatAttack(10);
    setStatDefense(0);
    setStatEvasion(20);
    setStatSpeed(15);
    setStatWillpower(6);
    setStatIntelligence(6);
    setStatResourcefullness(10);
    setStatLuck(10);
    setStatusIsDefense(0);
}

// Resourcefullness/luck based class
void Player_Class::setPlayerScavenger() {
    setStatDescription("A hobbit with high resourcefullness and moderate luck. He chooses to dodge instead of defend. His speed and willpower are low. ");
    setStatHitPoints(100);
    setStatAttack(10);
    setStatDefense(0);
    setStatEvasion(10);
    setStatSpeed(6);
    setStatWillpower(6);
    setStatIntelligence(10);
    setStatResourcefullness(20);
    setStatLuck(15);
    setStatusIsDefense(0);
}

// Intelligence based class
void Player_Class::setPlayerMage() {
    setStatDescription("An elf who has high intelligence and willpower. He chooses to defend instead of dodge. His speed and attack are low.");
    setStatHitPoints(75);
    setStatAttack(6);
    setStatDefense(10);
    setStatEvasion(0);
    setStatSpeed(6);
    setStatWillpower(15);
    setStatIntelligence(20);
    setStatResourcefullness(10);
    setStatLuck(10);
    setStatusIsDefense(1);
}

// Custom
void Player_Class::setPlayerCustom() {
    int statPool = 40;
    int input;
    bool isDefenseInput;
    setStatDescription("An individual who's stats have yet to be determined. Perhaps you can appraise them?");
    std::cout << "Set HP" << std::endl;
    std::cin >> input;
    setStatHitPoints(input);
    std::cout << "Set Attack" << std::endl;
    std::cin >> input;
    setStatAttack(input);
    std::cout << "Set Defense" << std::endl;
    std::cin >> input;
    setStatDefense(input);
    std::cout << "Set Evasion" << std::endl;
    std::cin >> input;
    setStatEvasion(input);
    std::cout << "Set Speed" << std::endl;
    std::cin >> input;
    setStatSpeed(input);
    std::cout << "Set Willpower" << std::endl;
    std::cin >> input;
    setStatWillpower(input);
    std::cout << "Set Intelligence" << std::endl;
    std::cin >> input;
    setStatIntelligence(input);
    std::cout << "Set Resourcefullness" << std::endl;
    std::cin >> input;
    setStatResourcefullness(input);
    std::cout << "Set Luck" << std::endl;
    std::cin >> input;
    setStatLuck(input);
    std::cout << "Set if your character uses defense or evasion. 1 - defense, 0 - evasion" << std::endl;
    std::cin >> isDefenseInput;
    setStatusIsDefense(isDefenseInput);


}

// -- Player Menus --


/* This function handles the selection of targets for the player. The player should be able to freely observe
*  the stats of their opponents, and select who they want to attack. The function returns an int which is used
*  in the battle loop function found in main.
*/
int Player_Class::playerMenuSelector(std::vector<Monster_Class> enemyEncounter) {

    int userInputTarget;
    bool isIfFound = false;
    bool isUserInputValid = false;
    std::vector<Monster_Class>liveEnemyEncounter;

    std::cout << "Select your target to interact with this turn: " << std::endl;

    // Display enemies
    while (isUserInputValid == false) {

        // For loop runs through and displays enemy vector
        // ## make it to where dead enemies are no longer shown
        // ## have a for loop before that crease an alive enemy encounter vector and use that
        // ## this does mean we'll have to redo the input. 
        // ## compare entity ID from alive vector to total vector and return the target of the total if that makes sense.

        // Removes any elements in the vector to prevent repeated misinputs from flooding the vector (the same 2 mobs apearing multiple times)

        while (!liveEnemyEncounter.empty()) {

            liveEnemyEncounter.pop_back();

        }

        // Creates vector with live enemies

        for (int i = 0; i < enemyEncounter.size(); i++) {

            if (enemyEncounter[i].getStatusIsAlive() == 1) {

                liveEnemyEncounter.push_back(enemyEncounter[i]);

            }

        }

        // Lists out live enemies

        for (int i = 0; i < liveEnemyEncounter.size(); i++) {

            std::cout << i + 1 << " - " << liveEnemyEncounter[i].getStatName() << std::endl;

        }// for

        // User selects target
        std::cin >> userInputTarget;
        std::cin.ignore();
        std::cout << std::endl;

        // If selection is greater than the size or less than 1, the input is invalid
        // Else, the loop can be exited

        if (userInputTarget > liveEnemyEncounter.size() || userInputTarget < 1 || std::cin.fail()) {

            std::cout << "Your input was invalid, please try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');

        } else {

            isUserInputValid = true;

        }

    }

    // Drop userInputTarget down by one to go from user friendly number to index
    userInputTarget -= 1;

    // Translate live enemy vector into total enemy vector. set isIfFound just in case it isn't

    isIfFound = false;
    for(int i = 0; i < enemyEncounter.size(); i++) {
        
        // If the entity ID's match, we set the live index to that of the total index
        
        if(isIfFound != true && liveEnemyEncounter[userInputTarget].getValEntID() == enemyEncounter[i].getValEntID()) {
                   
            userInputTarget = i;
            isIfFound = true;
        }  
    }

    std::cout << std::endl;

    return userInputTarget;

}// playerSelectorMenu

// This function should give the player options to attack, show stats, or use items in combat.
// ## todo, make this function a lot better. Add more functionality, add in checking for ranged/mana abilities, hide functions that aren't unlocked, etc.
// ## Maybe use arrays to dynamically throw up choices. The player has an ability array?
void Player_Class::playerMenuBattle(Player_Class& playerCharacter, Stats_Class& target) {

    // Set turn to 1, initialize some variables

    playerCharacter.setStatusIsCurrentTurn(1);
    char playerInput;
    bool isReselect = 0;

    // Show player and enemy HP
    std::cout << "--------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Player HP: " << playerCharacter.getStatHitPoints() << std::endl;
    std::cout << std::fixed << std::setprecision(2) << target.getStatName() << " HP: " << target.getStatHitPoints() << std::endl;
    std::cout << "--------------" << std::endl;

    // -- Run any passives here --

    // -- Run any statuses here --

    playerCharacter.runStatuses();

    // Mana regen passive
    playerCharacter.passiveMagicRegnerateMana();

    while (playerCharacter.getStatusIsCurrentTurn() == 1 && isReselect == 0) {

        // First menu switch, choose which submenu to access

        std::cout << "Select a menu to continue!" << std::endl <<
            "A - Attacks" << std::endl <<
            "B - Abilities" << std::endl <<
            "C - Utility" << std::endl <<
            "D - Select New Target" << std::endl <<
            "E - Do nothing" << std::endl;
            
        std::cin >> playerInput;
        std::cin.ignore();
        std::cout << std::endl;

        switch (playerInput) {

        case 'A':
        case 'a':

            // Attack Submenu

            playerMenuBattleSubMenuAttacks(playerCharacter, target);
            break;

        case 'B':
        case 'b':

            // Ability Submenu

            playerMenuBattleSubMenuAbilities(playerCharacter, target);
            break;

        case 'C':
        case 'c':

            // Utility Submenu

            playerMenuBattleSubMenuUtilities(playerCharacter, target);
            break;
            
        case 'D':
        case 'd':
            isReselect = 1;
            break;
        case 'E':
        case 'e':
            playerCharacter.setStatusIsCurrentTurn(0);
            break;
        default:
            break;
        }// switch

        

    }// while loop

    // If the players turn has ended (they aren't reselecting targets), then increment turn tick by one.
    if (playerCharacter.getStatusIsCurrentTurn() == 0) {

        playerCharacter.setValTurnTick(playerCharacter.getValTurnTick() + 1);
    }

}// PlayerBattleMenu

// -- BattleMenu Submenus -- 

// Select Attacks
void Player_Class::playerMenuBattleSubMenuAttacks(Player_Class& playerCharacter, Stats_Class& target) {
    
    char playerInput;

    std::cout << "Select which attack to use!" << std::endl <<
        "A - Basic Melee Attack" << std::endl <<
        "B - Basic Magic Attack" << std::endl <<
        "C - ## Basic Ranged Attack" << std::endl <<
        "D - Go back!" << std::endl;

    std::cin >> playerInput;
    std::cin.ignore();
    std::cout << std::endl;

    switch (playerInput) {

    case 'A':
    case 'a':
        playerCharacter.actionAttackBasicMelee(playerCharacter, target);
        break;
    case 'B':
    case 'b':
        playerCharacter.actionAttackBasicMagic(playerCharacter, target);
        break;
    case 'C':
    case 'c':
    case 'D':
    case 'd':
        break;

    }// switch

}// playerBattleSubMenuAttacks

// Select Abilities
void Player_Class::playerMenuBattleSubMenuAbilities(Player_Class& playerCharacter, Stats_Class& target) {
    
    char playerInput;

    std::cout << "Select which ability to use!" << std::endl <<
        "A - Charged Strike" << std::endl <<
        "B - Stun Hit" << std::endl <<
        "C - Magic Missile" << std::endl <<
        "D - Poison Shot" << std::endl <<
        "E - Go back!" << std::endl;

    std::cin >> playerInput;
    std::cin.ignore();
    std::cout << std::endl;

    switch (playerInput) {

    case 'A':
    case 'a':
        playerCharacter.actionAbilityPhysicChargedHit(playerCharacter, target);
        break;
    case 'B':
    case 'b':
        playerCharacter.actionAbilityPhysicStunHit(playerCharacter, target);
        break;
    case 'C':
    case 'c':
        playerCharacter.actionAbilityMagicMissile(playerCharacter, target);
        break;
    case 'D':
    case 'd':
        playerCharacter.actionAbilityMagicPoisonSplash(playerCharacter, target);
        break;
    case 'E':
    case 'e':
        break;

    }// switch

}// playerBattleSubMenuAbilities

// Select Utilities
void Player_Class::playerMenuBattleSubMenuUtilities(Player_Class& playerCharacter, Stats_Class& target) {
    
    char playerInput;

    std::cout << "Select which utility to use!" << std::endl <<
        "A - Show Your Stats" << std::endl <<
        "B - Show Enemy Stats" << std::endl <<
        "C - Magic Heal!" << std::endl <<
        "D - Go back!" << std::endl;

    std::cin >> playerInput;
    std::cin.ignore();
    std::cout << std::endl;

    switch (playerInput) {

    case 'A':
    case 'a':
        playerCharacter.showStats();
        break;
    case 'B':
    case 'b':
        target.showStats();
        break;
    case 'C':
    case 'c':
        playerCharacter.actionUtilityMagicHeal(playerCharacter, target);
    case 'D':
    case 'd':
        break;

    }// switch


} // playerBattleSubMenuUtilities