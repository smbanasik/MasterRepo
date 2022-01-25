// Random note:
// Make a multitool tag, then a multitool tag class, this class will have an additional property of having a number such as: 4004, which would act as 4th tier pick, and 4th tier shovel for example
// Or something like that. Figure it out. Also figure out harvestability.

#include "productUsable_class.h"
#include "tag_class.h"
#include "tagHandler_class.h"
#include <iostream>
#include <string>
#include <vector>

int main() {

    
    bool canHarvest = true;
    
    std::vector<tag_class> masterTagArr;
    std::vector<std::string> masterTagName = { "Wood", "Organic", "Hard", "Resource", "Ingredient", "Axe", "Iron", "Tool", "AnyTier", "Inorganic", "Rock", "Pickaxe", "WoodTier", "StoneTier" };
    std::vector<unsigned> masterTagType = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::vector<unsigned> masterTargetType = { 0, 0, 0, 1, 1, 3, 1, 3, 0, 0, 0, 3, 0, 0 };
    std::vector<unsigned> masterTagModiAmount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    tagHandler_class::tagArrayMaker(masterTagArr, masterTagName, masterTagType, masterTargetType, masterTagModiAmount);

    std::vector<std::string> woodTagNameArr = { "Wood", "Organic", "Hard", "Resource", "Ingredient" };
    std::vector<std::string> axeIronTagNameArr = { "Axe", "Iron", "Tool", "AnyTier"};
    std::vector<std::string> ironoreTagNameArr = { "Iron", "Inorganic", "Rock", "Hard", "Resource", "Ingredient" };
    std::vector<std::string> woodPickTagNameArr = { "Pickaxe", "Wood", "Tool", "WoodTier" };
    std::vector<std::string> ironPickTagNameArr = { "Pickaxe", "Iron", "Tool", "StoneTier" };
    
    std::vector<tag_class> woodTagArr;
    std::vector<tag_class> axeIronTagArr;
    std::vector<tag_class> ironoreTagArr;
    std::vector<tag_class> woodPickTagArr;
    std::vector<tag_class> ironPickTagArr;
    
    tagHandler_class::tagStringCopy(masterTagArr, woodTagArr, woodTagNameArr);
    tagHandler_class::tagStringCopy(masterTagArr, axeIronTagArr, axeIronTagNameArr);
    tagHandler_class::tagStringCopy(masterTagArr, ironoreTagArr, ironoreTagNameArr);
    tagHandler_class::tagStringCopy(masterTagArr, woodPickTagArr, woodPickTagNameArr);
    tagHandler_class::tagStringCopy(masterTagArr, ironPickTagArr, ironPickTagNameArr);

    tag_class qualAxe;
    tag_class qualAnyTier;
    tag_class qualPickaxe;
    tag_class qualStoneTier;

    tagHandler_class::tagArrayExtract(masterTagArr, qualAxe, "Axe");
    tagHandler_class::tagArrayExtract(masterTagArr, qualAnyTier, "AnyTier");
    tagHandler_class::tagArrayExtract(masterTagArr, qualPickaxe, "Pickaxe");
    tagHandler_class::tagArrayExtract(masterTagArr, qualStoneTier, "StoneTier");



    std::cout << "Making ingredient wood!" << std::endl;

    ingredient_class wood("Wood", "A rough piece of wood, harvested from a tree", 0, 100, 50, qualAxe, qualAnyTier, woodTagArr);

    wood.inspectItem();

    std::cout << "Creating your axe!" << std::endl;

    productUsable_class axeIron("Iron Axe", "A sharp cleaver of iron fixxed to the end of a stick.", 1, 1, 5, 100, 100, 1, axeIronTagArr);

    axeIron.inspectItem();

    std::cout << "Making ingredient iron!" << std::endl;

    ingredient_class ironOre("Iron Ore", "A red piece of rock broken from the ground, smelting it could be useful.", 0, 100, 50, qualPickaxe, qualStoneTier, ironoreTagArr);

    ironOre.inspectItem();

    std::cout << "Making your wood pick, and then iron pick!" << std::endl;

    productUsable_class pickaxeIron("Iron Pickaxe", "A sharp spear of iron fixxed horizontally to the end of a stick.", 1, 1, 5, 100, 100, 1, ironPickTagArr);
    productUsable_class pickaxeWood("Wood Pickaxe", "A sharp piece of wood placed on the end of a stick.", 1, 1, 5, 50, 50, 1, woodPickTagArr);

    pickaxeIron.inspectItem();
    pickaxeWood.inspectItem();

    std::cout << "Checking to see if the axe can mine iron!" << std::endl;

    canHarvest = axeIron.checkHarvestability(ironOre);

    std::cout << "Result: " << canHarvest << std::endl;

    std::cout << "Checking to see if the wood pick can mine iron!" << std::endl;

    canHarvest = pickaxeWood.checkHarvestability(ironOre);

    std::cout << "Result: " << canHarvest << std::endl;

    std::cout << "Checking to see if the iron pick can mine iron!" << std::endl;

    canHarvest = pickaxeIron.checkHarvestability(ironOre);

    std::cout << "Result: " << canHarvest << std::endl;

    std::cout << "Making sure template function works" << std::endl;

    tagHandler_class::tagVerifyChange<productUsable_class>(qualAxe, axeIron);
    tagHandler_class::tagVerifyChange<ingredient_class>(woodTagArr, wood);
    

    return 0;
}