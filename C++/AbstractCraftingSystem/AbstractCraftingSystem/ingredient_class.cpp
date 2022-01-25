#include "ingredient_class.h"
#include <iostream>

void ingredient_class::defineItem(unsigned ingredientQuality, tag_class primaryHarvestTool, tag_class harvestTier) {

    // Checks passed, define terms

    this->ingredientQuality = ingredientQuality;
    primaryHarvestTool.cloneTagInfo(this->primaryHarvestTool);
    harvestTier.cloneTagInfo(this->harvestTier);

}


void ingredient_class::displayItem() {

    std::cout << "----------" << std::endl
        << "Item name: " << itemName << std::endl
        << "Description: " << itemDescription << std::endl
        << "Amount: " << itemCount << "/" << itemMaxCount << std::endl
        << "----------" << std::endl;


}

void ingredient_class::inspectItem() {

    displayItem();
    std::cout << "----------" << std::endl
        << "Quality: " << ingredientQuality << std::endl
        << "Tool required: " << primaryHarvestTool.tagName << std::endl
        << "Tier required: " << harvestTier.tagName << std::endl
        << "Tags: ";
    for (int i = 0; i < itemTags.size() - 1; i++) {

        std::cout << itemTags[i].tagName << ", ";
    }
    std::cout << itemTags[itemTags.size() - 1].tagName << std::endl;

    std::cout << "---------" << std::endl;



}