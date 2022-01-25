#include "Stats.h"
#include<iostream>
#include<iomanip>
#include<cmath>

// Initialize static variables

int Stats_Class::globalRandVal = 0;

// -- Utility Functions --

// ## gonna need to redo this

// This function displays all of the stats
void Stats_Class::showStats() {

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Name: " << statName << std::endl;
    std::cout << "Desc: " << statDescription << std::endl;
    std::cout << "HP - " << statHitPoints << std::endl;
    std::cout << "MP - " << statMana << std::endl;
    std::cout << "Atk - " << statAttack << std::endl;
    std::cout << "Def - " << statDefense << std::endl;
    std::cout << "Eva - " << statEvasion << std::endl;
    std::cout << "Spe - " << statSpeed << std::endl;
    std::cout << "Wil - " << statWillpower << std::endl;
    std::cout << "Int - " << statIntelligence << std::endl;
    std::cout << "Res - " << statResourcefullness << std::endl;
    std::cout << "Luc - " << statLuck << std::endl;
    std::cout << std::endl;
}

/* This function initializes the damage and trudef variables.
*  It MUST be used, do so after any change in stats. 
*/
void Stats_Class::initializeSecondStats() {

    setStatHitPointsMax(static_cast<double>(statEndurance) * 5);
    setStatManaMax(statAffinity);
    setNumDamage(statAttack);
    setNumTrueDef(1 - (sqrt(statDefense) / 30));
    setNumTrueEva(3 * sqrt(statEvasion) + 5);
    setNumDefPen((static_cast<double>(statAttack) / 5) / 160 + (static_cast<double>(statSpeed) / 5) / 80);
    // ## balance this
    //setNumEvaPen((static_cast<double>(statAttack) / 5) / 20 + (static_cast<double>(statIntelligence) / 5) / 10);
    setNumPhysicModi(2 * (static_cast<double>(statEndurance) / 5));
    setNumMagicModi(2 * (static_cast<double>(statAffinity) / 5));
    setNumStatusModi(1 - (static_cast<double>(statWillpower) / 5 ) / 25);

    // ## include a check to make sure modifiers cannot set the damage below 0.
    
}

// Function sees if an entity is dead. Use after any damage is applied
void Stats_Class::updateCheckDeath() {

    if (statHitPoints <= 0) {

        statusIsAlive = 0;

    }

}

// ## Maybe we could turn this function into a full modify HP? Run the check death, bounds checking, and hp modify functions here?
void Stats_Class::updateInBoundsDeltaHP(double& deltaHP, bool isHeal) {
    
    
    if (isHeal == 0) {

        // Check if below 0 hp, then set to 0

        if ((statHitPoints - deltaHP) < 0) {

            deltaHP = statHitPoints;

        }

        statHitPoints -= deltaHP;
    }
    else {
        
        // Check if above max hp, then set to max hp

        if ((statHitPoints + deltaHP) > statHitPointsMax) {

            deltaHP = statHitPointsMax - statHitPoints;

        }

        statHitPoints += deltaHP;
    }

    updateCheckDeath();

}// updateInBoundsDeltaHP

// Not feelin the random values.
/*
void Stats_Class::updateApplyDeltaHPRando(double& deltaHP) {

    double randomModi;

    // We should get anywhere from 0.95 - 1.05
    if (globalRandVal >= 49) {

        // Add up to 5%
        randomModi = 1 + ((globalRandVal % 5) / 100.00);

    }
    else {

        // Remove up to 5%
        randomModi = 1 - ((globalRandVal % 5) / 100.00);

    }
    
    // Delta HP * 1.00 to * 1.05
    deltaHP *= randomModi;

}*/

// -- Combat Functions --

void Stats_Class::actionAttackBasicMelee(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;

    // Calculate damage multiplied by dmg reduction due to defense.

    deltaHP = (user.numDamage + user.numPhysicModi) * (target.numTrueDef + user.numDefPen);
    
    // Randomize number slightly
    //updateApplyDeltaHPRando(deltaHP);

    // Make sure change in HP is in bounds
    // And modify the targets hit points
    // And see if the change in HP kills the target

    target.updateInBoundsDeltaHP(deltaHP, 0);

    // Display damage message/kill messages
    // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

    if (target.statusIsAlive == 0) {

        std::cout << user.statName << " has killed " << target.statName << " for " << deltaHP << " damage!" << std::endl;

    }
    else {

        std::cout << user.statName << " has hit " << target.statName << " for " << deltaHP << " damage." << std::endl;

    }// if

    std::cout << std::endl;

    // End the users turn
    user.statusIsCurrentTurn = 0;

}// actionAttackBasicMelee


// Defense should be logarithmic
// Evasions should be logarithmic

void Stats_Class::actionAttackBasicMagic(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    double manaCost = 1;

    // Check if player has proper mana, if not, skip other stuff, else do it

    if (user.statMana - manaCost < 0) {

        std::cout << "You have not enough mana!" << std::endl;

    } else {

        // Calculate damage multiplied by dmg reduction due to defense.
        
        deltaHP = (user.numDamage + user.numMagicModi) * (target.numTrueDef + user.numDefPen);

        user.statMana -= manaCost;

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target

        target.updateInBoundsDeltaHP(deltaHP, 0);

        // Display damage message/kill messages
        // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

        if (target.statusIsAlive == 0) {

            std::cout << user.statName << " has withered " << target.statName << " for " << deltaHP << " damage!" << std::endl;

        }
        else {

            std::cout << user.statName << " has afflicted " << target.statName << " for " << deltaHP << " damage." << std::endl;

        }// if

        // End the users turn
        user.statusIsCurrentTurn = 0;

    }// if mana check

    std::cout << std::endl;

}// actionAttackBasicMagic

void Stats_Class::actionAbilityPhysicChargedHit(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    user.statusChargeLimit = 2;

    if (user.statusChargeLevel == user.statusChargeLimit) {

        // Calculate damage multiplied by dmg reduction due to defense.

        deltaHP = (user.numDamage + user.numPhysicModi + static_cast<double>(user.statIntelligence))
            * (target.numTrueDef + user.numDefPen);

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target

        target.updateInBoundsDeltaHP(deltaHP, 0);

        // Display damage message/kill messages
        // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

        if (target.statusIsAlive == 0) {

            std::cout << user.statName << " has slayed " << target.statName << " for " << deltaHP << " damage!" << std::endl;

        }
        else {

            std::cout << user.statName << " has striked " << target.statName << " for " << deltaHP << " damage." << std::endl;

        } // if

        // Set charge level and limit back to 0

        user.statusChargeLevel = 0;
        user.statusChargeLimit = 0;

        std::cout << std::endl;

    }
    else {

        // Begin charging attack, prompt user

        std::cout << "You begin to charge your attack! It will be ready in " << user.statusChargeLimit << " turn(s)!" << std::endl << std::endl;
        user.statusChargeLevel = 1;

    } // if

    // End the users turn
    user.statusIsCurrentTurn = 0;

}// actionAbilityPhysicChargedHit

void Stats_Class::actionAbilityMagicMissile(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    double manaCost = 2;

    // Check if player has proper mana, if not, skip other stuff, else do it

    if (user.statMana - manaCost < 0) {

        std::cout << "You have not enough mana!" << std::endl;

    }
    else {

        // Calculate damage multiplied by dmg reduction due to defense.

        deltaHP = ((user.numDamage + user.numMagicModi) / 2) + user.statIntelligence
            * (target.numTrueDef + user.numDefPen);
        user.statMana -= manaCost;

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target

        target.updateInBoundsDeltaHP(deltaHP, 0);

        // Display damage message/kill messages
        // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

        if (target.statusIsAlive == 0) {

            std::cout << user.statName << " has exploded " << target.statName << " for " << deltaHP << " damage!" << std::endl;

        }
        else {

            std::cout << user.statName << " has blasted " << target.statName << " for " << deltaHP << " damage." << std::endl;

        }// if

        // End the users turn
        user.statusIsCurrentTurn = 0;

    }// if mana check

    std::cout << std::endl;
}// actionAbilityMagicMissile

void Stats_Class::actionAbilityMagicPoisonSplash(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    double manaCost = 3;
    target.statusPoisonLevel = 5;

    // Check if player has proper mana, if not, skip other stuff, else do it

    if (user.statMana - manaCost < 0) {

        std::cout << "You have not enough mana!" << std::endl;

    }
    else {

        // Calculate damage multiplied by dmg reduction due to defense.

        deltaHP = ((user.statIntelligence + user.numMagicModi) / 2)
            * (target.numTrueDef + user.numDefPen);
        user.statMana -= manaCost;

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target

        target.updateInBoundsDeltaHP(deltaHP, 0);

        // Display damage message/kill messages
        // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

        if (target.statusIsAlive == 0) {

            std::cout << user.statName << " has defiled" << target.statName << " for " << deltaHP << " damage!" << std::endl;

        }
        else {

            std::cout << user.statName << " has poisoned " << target.statName << " for " << deltaHP << " damage." << std::endl;

        }// if

        // End the users turn
        user.statusIsCurrentTurn = 0;

    }// if mana check

    std::cout << std::endl;

}// actionAbilityMagicMissile

void Stats_Class::actionAbilityPhysicStunHit(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    target.statusStunLevel = 1;

    // Calculate damage multiplied by dmg reduction due to defense.

    deltaHP = user.numPhysicModi * (target.numTrueDef + user.numDefPen);

    // Make sure change in HP is in bounds
    // And modify the targets hit points
    // And see if the change in HP kills the target

    target.updateInBoundsDeltaHP(deltaHP, 0);

    // Display damage message/kill messages
    // ## add on to these to make them more appealing. Maybe add damage numbers to killed or left over HP, idk.

    if (target.statusIsAlive == 0) {

        std::cout << user.statName << " has *bonked* " << target.statName << " for " << deltaHP << " damage!" << std::endl;

    }
    else {

        std::cout << user.statName << " has stunned " << target.statName << " for " << deltaHP << " damage." << std::endl;

    }// if

    std::cout << std::endl;

    // End the users turn
    user.statusIsCurrentTurn = 0;

}// actionAbilityPhysicStunHit



void Stats_Class::actionUtilityMagicHeal(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    double manaCost = 2;

    // Check if player has proper mana, if not, skip other stuff, else do it

    if (user.statMana - manaCost < 0) {

        std::cout << "You have not enough mana!" << std::endl;

    } else {

        // Calculate healing

        deltaHP = user.statIntelligence + user.numMagicModi;
        user.statMana -= manaCost;

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target
        
        user.updateInBoundsDeltaHP(deltaHP, 1);

        std::cout << "Your hit points have been increased by " << deltaHP << std::endl;

        // End the users turn
        user.statusIsCurrentTurn = 0;

    }// if mana check

    std::cout << std::endl;

} // actionUtilityMagicHeal

void Stats_Class::actionUtilityMagicAntidote(Stats_Class& user, Stats_Class& target) {

    double deltaHP = 0;
    double manaCost = 2;
    user.statusPoisonLevel = 0;

    // Check if player has proper mana, if not, skip other stuff, else do it

    if (user.statMana - manaCost < 0) {

        std::cout << "You have not enough mana!" << std::endl;

    }
    else {

        // Calculate healing

        deltaHP = user.numMagicModi;
        user.statMana -= manaCost;

        // Make sure change in HP is in bounds
        // And modify the targets hit points
        // And see if the change in HP kills the target

        user.updateInBoundsDeltaHP(deltaHP, 1);

        std::cout << "You have been cured, and your hit points have been increased by " << deltaHP << std::endl;

        // End the users turn
        user.statusIsCurrentTurn = 0;

    }// if mana check

    std::cout << std::endl;

}// actionUtilityMagicAntidote

// -- PASSIVE FUNCTIONS -- 

void Stats_Class::passiveMagicRegnerateMana() {

    // Every other turn, regen mana by one
    if (valTurnTick % 2 == 0) {

        statMana += CONSTMANAREGEN;
    }
}

// -- STATUS UPDATE FUNCTIONS --

void Stats_Class::runStatuses() {

    // -- Run any statuses here --

    // Poison Status
    updateStatusPoisoned();

    // Stun Status
    updateStatusStunned();

    // Charge Status
    updateStatusCharging();

}

// This function serves to deal poison damage.
void Stats_Class::updateStatusPoisoned() {

    if (statusPoisonLevel > 0) {

        double deltaHP = CONSTPOISONDMG * numStatusModi;

        updateInBoundsDeltaHP(deltaHP, 0);

        statusPoisonLevel -= 1;
    }

}// updateStatusPoisoned

// This function serves to skip the players turn if stunned
void Stats_Class::updateStatusStunned() {

    // StunFail should be 1-100
    int stunSucceed = (globalRandVal + 1) * numStatusModi;

    if (statusStunLevel > 0) {

        if (stunSucceed > STUNCHANCEFAIL) {

            statusIsCurrentTurn = 0;

        }

        statusStunLevel -= 1;
    }
} // updateStatusStunned

// This function serves to update the charging status
void Stats_Class::updateStatusCharging() {

    // Check if player is charging attack (geater than 0) or if charge is incomplete (less than charge limit)
    if (statusChargeLevel > 0 &&
        statusChargeLevel < statusChargeLimit) {

        // Give the player information on charge length

        std::cout << "\nYou are currently charging your attack! It will be ready in " << statusChargeLimit -
            statusChargeLevel << " turns!" << std::endl << std::endl;

        // Charge their attack

        statusChargeLevel += 1;

        // Set their turn to 0

        statusIsCurrentTurn = 0;

        // ## Add in a skip input function. Makes it so player has to cin manually to continue.

    }// if



}// updateStatusCharging