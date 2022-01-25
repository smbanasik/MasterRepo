#include "item_class.h"

// Adding tags

void item_class::addTag(tag_class tagName) {

    itemTags.push_back(tagName);

}

void item_class::addTag(std::vector<tag_class> tagArr) {

    for (unsigned i = 0; i < tagArr.size(); i++) {

        itemTags.push_back(tagArr[i]);

    }

}

// Used in constructors and also to redefine a whole item at once

void item_class::defineItem(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount) {

    if (itemCount > itemMaxCount) itemCount = itemMaxCount;

    // Checks passed, define terms
    
    this->itemName = itemName;
    this->itemCount = itemCount;
    this->itemMaxCount = itemMaxCount;

    setDescription(itemDescription);

}

// Display basic stats

void item_class::displayItem() {

    std::cout << "----------" << std::endl
        << "Item name: " << itemName << std::endl
        << "Description: " << itemDescription << std::endl
        << "Amount: " << itemCount << "/" << itemMaxCount << std::endl
        << "----------" << std::endl;

}

// Display specific stats

void item_class::inspectItem() {




}