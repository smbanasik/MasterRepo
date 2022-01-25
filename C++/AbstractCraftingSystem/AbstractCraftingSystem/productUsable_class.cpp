#include "productUsable_class.h"


// Should check to see if a target is harvestable with the current usable item
bool productUsable_class::checkHarvestability(ingredient_class harvestTarget) {
    
    bool toolCheck = false;
    bool harvestCheck = false;
    bool harvestable = false;

    // Loop through item tags, check if it has the tags that the item is looking for.
    for (int i = 0; i < itemTags.size(); i++) {

        if (itemTags[i].tagName == harvestTarget.primaryHarvestTool.tagName) toolCheck = true;

        if (itemTags[i].tagName == harvestTarget.harvestTier.tagName) harvestCheck = true;

    }

    if (toolCheck == true && harvestCheck == true) {

        harvestable = true;
    }

    return harvestable;
}

void productUsable_class::defineItem(unsigned damage, unsigned durability, unsigned maxDurability, unsigned harvestAmount) {

    if (durability > maxDurability) durability = maxDurability;

    // Checks passed, define terms

    this->damage = damage;
    this->durability = durability;
    this->maxDurability = maxDurability;
    this->harvestAmount = harvestAmount;

}


void productUsable_class::displayItem() {

    std::cout << "----------" << std::endl
        << "Item name: " << itemName << std::endl
        << "Description: " << itemDescription << std::endl
        << "Amount: " << itemCount << "/" << itemMaxCount << std::endl
        << "----------" << std::endl;

}

void productUsable_class::inspectItem() {

    displayItem();
    std::cout << "----------" << std::endl
        << "Durability: " << durability << "/" << maxDurability << std::endl
        << "Damage: " << damage << std::endl
        << "Tags: ";
    for (int i = 0; i < itemTags.size() - 1; i++) {

        std::cout << itemTags[i].tagName << ", ";
    }
    std::cout << itemTags[itemTags.size() - 1].tagName << std::endl;

    std::cout << "---------" << std::endl;


}