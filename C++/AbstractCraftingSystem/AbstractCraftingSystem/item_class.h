/* This is the base item class that contains very basic functionality that every item should have.
*  This class and it's children will henceforth be known as item types.
*  The process of creating an item type requires the following:
*  1. The item type and it's properties.
*  2. Defining it's targetType enum. Modify the original enum in item_class to add more.
*  3. Ensuring it has an unordered map that associates it's properties to integers.
*  4. Creating a tag implementation function that carries out modifying the properties.
*/
#ifndef ITEM_CLASS_H
#define ITEM_CLASS_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "tag_class.h"

class item_class {

public:

    // STATIC

    static enum class targetType { any, ingredient, part, productUsable, productUnusable };

    // CONSTRUCTORS

    inline item_class() {

        targetType = targetType::any;

    }

    inline item_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount) {

        targetType = targetType::any;
        defineItem(itemName, itemDescription, itemCount, itemMaxCount);

    }

    void setDescription(std::string itemDescription) {

        this->itemDescription = itemDescription;

    }

    // DECLARING VARS

    std::string itemName = "";
    std::string itemDescription = "";
    unsigned itemCount = 0;
    unsigned itemMaxCount = 0;
    std::vector<tag_class> itemTags;
    targetType targetType = targetType::any;

    // Just need single element, no order needed.
    std::unordered_map<std::string, int> propertyKey = {

        {"itemName", 0},
        {"itemDescription", 1},
        {"itemMaxCount", 2},

    };

    // FUNCTIONS

    // Add tags

    void addTag(tag_class tagName);

    void addTag(std::vector<tag_class> tagArr);
    
    // Input values into item
    void defineItem(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount);

    // Show name and amount
    void displayItem();

    // Show detailed stats
    void inspectItem();



};
#endif ITEM_CLASS_H