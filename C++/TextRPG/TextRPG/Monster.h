#pragma once
#ifndef MONSTER_H
#define MONSTER_H
#include "Stats.h"
class Player_Class;

class Monster_Class : public Stats_Class
{   

private:

    // ** Monster level will determine the difficulty of the monsters and influence their stats.
    // Replaced by levels for both parties.

    // ** Monster type will be used in the AI to limit the abilities that they can use in the menu.
    // ** This prevents a basic goblin from somehow using a level 100 super death insta kill spell.
    std::string monsterType;

public:

    // -- Monster Getters --

    // ## might be a better idea to have monster types in an enumerated array.
    std::string getMonsterType() const { return monsterType; }

    // -- Monster Setters --

    void setMonsterType(std::string monsterType)
    { this->monsterType = monsterType; }

    // Function that fills in stats of monster. Temporary, basic, gets job done
    void monsterSetStats(int entID, std::string name, std::string desc, double maxHP, double HP, int Atk, int Def, int Spe);

    // -- Monster Menus (AI) --

    void monsterBattleMenu(Monster_Class& monsterCharacter, Stats_Class& target);


    void lootGenerator();
    // Populates the monsters inventory with items

    void monsterDeath(Player_Class targetSlayer);
    // func should add gold to player that killed it and show a promt with the monsters inventory that
    // would let the player take it

};





#endif MONSTER_H