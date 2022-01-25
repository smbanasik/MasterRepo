#include "Monster.h"

// -- Monster Setters --

// This function is an extremely basic constructor(?), it justs adds in values needed to make a very simple dummy mob
void Monster_Class::monsterSetStats(int entID, std::string name, std::string desc, double maxHP, double HP, int Atk, int Def, int Spe) {

    setValEntID(entID);

    setStatName(name);
    setStatDescription(desc);
    setStatHitPointsMax(maxHP);
    setStatHitPoints(HP);
    setStatAttack(Atk);
    setStatDefense(Def);
    setStatSpeed(Spe);


    initializeSecondStats();
}


// -- Monster Menus (AI) --
// ** This serves as the "AI" of the monster. It will use seeded random generation (the seed being time),
// ** and depending on the monsters stats biases, will be applied in it's decision making. This means high
// ** intelligence monsters, likely some sort of mage, will use magic attacks much more frequently.
// ## Add in AI and stuff lol
void Monster_Class::monsterBattleMenu(Monster_Class& monsterCharacter, Stats_Class& target) {

    monsterCharacter.setStatusIsCurrentTurn(1);
    //int monsterInput;

    // ## as monsters get more abilities, impliment a time based random generation that functions as monster input.

    // Run any statuses here

    monsterCharacter.runStatuses();

    while (monsterCharacter.getStatusIsCurrentTurn() == 1) {

        monsterCharacter.actionAttackBasicMelee(monsterCharacter, target);

    }
    
}