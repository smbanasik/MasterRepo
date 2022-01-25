#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "Stats.h"
class Monster_Class;


class Player_Class : public Stats_Class
{
private:

    // Place holder for player specific variables.
    double itemMoney = 0;
    double itemXP = 0;

public:

    // Reserve the ent ID -1 for the player

    Player_Class() {

        setValEntID(-1);

    }

    // -- Player Getters --

    double getItemMoney() const { return itemMoney; }

    double getItemXP() const { return itemXP; }

    // -- Player Setters --

    void addItemMoney(double itemMoney)
    { this->itemMoney += itemMoney;}

    void addItemXP(double itemXP)
    { this->itemXP += itemXP; }
    
    // -- Class Assigner Functions --

    // Make a better function for this
    void setPlayerBarbarian();
    void setPlayerKnight();
    void setPlayerThief();
    void setPlayerScavenger();
    void setPlayerMage();
    void setPlayerCustom();

    // -- Player Menus --
    

    int playerMenuSelector(std::vector<Monster_Class> enemyEncounter);
    void playerMenuBattle(Player_Class& playerCharacter, Stats_Class& target);

    // -- BattleMenu SubMenus --

    void playerMenuBattleSubMenuAttacks(Player_Class& playerCharacter, Stats_Class& target);
    void playerMenuBattleSubMenuAbilities(Player_Class& playerCharacter, Stats_Class& target);
    void playerMenuBattleSubMenuUtilities(Player_Class& playerCharacter, Stats_Class& target);

    // -- Player Inventory Actions --

    void takeItem();
    void equipItem();
    void unequipItem();
    void dropItem();
    // drop item would really delete the item, add a prompt asking if they're sure.
    void depositItem();
};




#endif PLAYER_H