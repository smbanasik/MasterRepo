#pragma once
#ifndef STATS_H
#define STATS_H
#include<string>
#include<cmath>

class Stats_Class {

private:

    // -- Stat Vars --

    // Used whenever we need to compare stats class objects
    // To monster or player class objects
    // ## could we make this a static array and see what things are using it?
    int valEntID = 0;

    // Will be used to handle things that happen consistently accross multiple turns.
    // Things should use modulus turn tick to calculate. Example: when TurnTick % 2 == 0, mana increase by one.
    // ## charge might be able to be fitted with this system. Unsure.
    int valTurnTick = 0;

    std::string statName = "";
    std::string statDescription = "";
    int statLevel = 0;
    double statHitPoints = 0;
    double statMana = 0;
    // Primary stats
    int statEndurance = 0;
    int statAffinity = 0;
    int statAttack = 0;
    int statDefense = 0;
    int statEvasion = 0;
    int statSpeed = 0;
    int statWillpower = 0;
    int statIntelligence = 0;
    int statResourcefullness = 0;
    int statLuck = 0;

    // Used to determine if a character uses defense or evasion as their stat, by default they do
    bool statusIsDefense = 1;
    // Everything should be alive at first
    bool statusIsAlive = 1;
    // 1 means its their turn, 0 means they are unable to do abilities.
    // Combat menus should set this to 1, combat functions should set tis to 0
    bool statusIsCurrentTurn = 1;
    // Used in combat, starts at 0 and will increment until an ability has charged enough. 
    // The limit is set by combat functions, the menu handles incrementing the charge level.
    // When the charge level reaches  the limit, the menu is usable again and the attack may be used.
    int statusChargeLevel = 0;
    int statusChargeLimit = 0;
    // Set number of turns to be poisoned
    int statusPoisonLevel = 0;
    // Set number of turns to be stunned
    int statusStunLevel = 0;

    // Secondary stats that are influenced by primary stats
    double statHitPointsMax = 0;
    double statManaMax = 0;
    double numDamage = 0;
    double numTrueDef = 0;
    double numTrueEva = 0;
    // Lowers chance of evasion & amount of defense
    double numDefPen = 0;
    double numEvaPen = 0;
    // Adds damage based off of nubmers
    double numPhysicModi = 0;
    double numMagicModi = 0;
    // Controlls how effective status effects are
    double numStatusModi = 0;

public:

    // Constants

    static const int CONSTPOISONDMG = 3;
    static const int CONSTMANAREGEN = 1;
    static const int STUNCHANCEFAIL = 40;

    // Variable that is to be used for handling all general random values.
    // Seed is initialized in main using time(NULL).
    // Variable is to be set between 0 - 99 (%100).
    // Everything should be built around it using 0 - 99.

    static int globalRandVal;

    // -- Stat Getters --

    int getValEntID() const { return valEntID; }
    int getValTurnTick() const { return valTurnTick; }

    std::string getStatName() const { return statName; }
    std::string getStatDescription() const { return statDescription; }
    int getStatLevel() const { return statLevel; }
    double getStatHitPoints() const { return statHitPoints; }
    double getStatMana() const { return statMana; }
    // Primary Stats
    int getStatEndurance() const { return statEndurance; }
    int getStatAffinity() const { return statAffinity; }
    int getStatAttack() const { return statAttack; }
    int getStatDefense() const { return statDefense; }
    int getStatEvasion() const { return statEvasion; }
    int getStatSpeed() const { return statSpeed; }
    int getStatWillpower() const { return statWillpower; }
    int getStatIntelligence() const { return statIntelligence; }
    int getStatResourcefullness() const { return statResourcefullness; }
    int getStatLuck() const { return statLuck; }

    bool getStatusIsDefense() const { return statusIsDefense; }
    bool getStatusIsAlive() const { return statusIsAlive; }
    bool getStatusIsCurrentTurn() const { return statusIsCurrentTurn; }
    int getStatusChargeLevel() const { return statusChargeLevel; }
    int getStatusChargeLimit() const { return statusChargeLimit; }
    int getStatusPoisonLevel() const { return statusPoisonLevel; }

    // Secondary Stats
    double getStatHitPointsMax() const { return statHitPointsMax; }
    double getStatManaMax() const { return statManaMax; }
    double getNumDamage() const { return numDamage; }
    double getNumTrueDef() const { return numTrueDef; }
    double getNumTrueEva() const { return numTrueEva; }
    double getNumDefPen() const { return numDefPen; }
    double getNumEvaPen() const { return numEvaPen; }
    double getNumPhysicModi() const { return numPhysicModi; }
    double getNumMagicModi() const { return numMagicModi; }
    double getNumStatusModi() const { return numStatusModi; }


    // -- Stat Setters --

    void setValEntID(int valEntID)
    { this->valEntID = valEntID; }

    void setValTurnTick(int valTurnTick)
    { this->valTurnTick = valTurnTick; }

    void setStatName(std::string statName)
    { this->statName = statName; }

    void setStatDescription(std::string statDescription)
    { this->statDescription = statDescription; }

    void setStatLevel(int statLevel)
    { this->statLevel = statLevel; }

    void setStatHitPoints(double statHitPoints)
    { this->statHitPoints = statHitPoints; }

    void setStatMana(double statMana)
    { this->statMana = statMana; }

    // Primary stats
    
    void setStatEndurance(double statEndurance)
    { this->statEndurance = statEndurance; }

    void setStatAffinity(double statAffinity)
    { this->statAffinity = statAffinity; }

    void setStatAttack(int statAttack)
    { this->statAttack = statAttack; }

    void setStatDefense(int statDefense)
    { this->statDefense = statDefense; }

    void setStatEvasion(int statEvasion)
    { this->statEvasion = statEvasion; }

    void setStatSpeed(int statSpeed)
    { this->statSpeed = statSpeed; }

    void setStatWillpower(int statWillpower)
    { this->statWillpower = statWillpower; }

    void setStatIntelligence(int statIntelligence)
    { this->statIntelligence = statIntelligence; }

    void setStatResourcefullness(int statResourcefullness)
    { this->statResourcefullness = statResourcefullness; }

    void setStatLuck(int statLuck)
    { this->statLuck = statLuck; }

    // Statuses

    void setStatusIsDefense(bool statusIsDefense)
    { this->statusIsDefense = statusIsDefense; }

    void setStatusIsAlive(bool statusIsAlive)
    { this->statusIsAlive = statusIsAlive; }

    void setStatusIsCurrentTurn(bool statusIsCurrentTurn)
    { this->statusIsCurrentTurn = statusIsCurrentTurn; }

    void setStatusChargeLevel(int statusChargeLevel)
    { this->statusChargeLevel = statusChargeLevel; }

    void setStatusChargeLimit(int statusChargeLimit)
    { this->statusChargeLimit = statusChargeLimit; }

    void setStatusPoisonLevel(int statusPoisonLevel)
    { this->statusPoisonLevel = statusPoisonLevel; }

    // Secondary stats

    void setStatHitPointsMax(double statHitPointsMax)
    { this->statHitPointsMax = statHitPointsMax; }

    void setStatManaMax(double statManaMax)
    { this->statManaMax = statManaMax; }

    void setNumDamage(double numDamage)
    { this->numDamage = numDamage; }

    // ** TrueDef is the number that damage gets multiplied by to be reduced.
    // ** It's a negative multiplier

    void setNumTrueDef(double numTrueDef)
    { this->numTrueDef = numTrueDef; }

    // ** True Eva is the chance that a % of damage is negated.

    void setNumTrueEva(double numTrueEva)
    { this->numTrueEva = numTrueEva; }

    // ** Defensse modifier that affects reduction. Positive addend (negative in effect)

    void setNumDefPen(double numDefPen)
    { this->numDefPen = numDefPen; }

    // ** Defense modifier that affects amount negated. Negative addend

    void setNumEvaPen(double numEvaPen)
    { this->numEvaPen = numEvaPen; }

    // ** Physical Modifiers that affect damage. Positive addend

    void setNumPhysicModi(double numPhysicModi)
    { this->numPhysicModi = numPhysicModi; }

    // ** Magical Modifiers that affect damage. Positive addend

    void setNumMagicModi(double numMagicModi)
    { this->numMagicModi = numMagicModi; }

    // ** Negative multiplier that affects damage of status effects.

    void setNumStatusModi(double numStatusModi)
    { this->numStatusModi = numStatusModi; }

    // -- Utility Functions --

    void showStats();
    void initializeSecondStats();
    void updateCheckDeath();
    void updateInBoundsDeltaHP(double& deltaHP, bool isHeal);
    //void updateApplyDeltaHPRando(double& deltaHP);

    // -- Combat functions --
    // ** Broken into action and passive
    // ** and into physical, magical, and basic.
    // These functions handle calculating damage and running the deltahp func
    
    // ** FORMULAS GO HERE
    void actionAttackBasicMelee(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionAttackBasicMagic(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionAbilityPhysicChargedHit(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionAbilityMagicMissile(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionAbilityMagicPoisonSplash(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionAbilityPhysicStunHit(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionUtilityMagicHeal(Stats_Class& user, Stats_Class& target);
    // ** FORMULAS GO HERE
    void actionUtilityMagicAntidote(Stats_Class& user, Stats_Class& target);

    void passiveMagicRegnerateMana();

    // -- Status functions --
    // Used in battle functions and such

    void runStatuses();

    void updateStatusPoisoned();
    void updateStatusStunned();
    void updateStatusCharging();


};
#endif STATS_H

// Comment Formatting

// -- Section Title --

// ** Information about conceptual game things

// ## Todo Notes

// Comment Explaining code