// This class containts elements needed for ingredients, things that will be turned into parts or products.
// It's parent is item class
#ifndef INGREDIENT_CLASS_H
#define INGREDIENT_CLASS_H

#include "item_class.h"

class ingredient_class : public item_class {

public:
    
    // CONSTRUCTORS

    // Empty Constructor

    ingredient_class() {

        targetType = targetType::ingredient;

    }

    // Constructor no tag

    inline ingredient_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned itemQuality, tag_class primaryHarvestTool, tag_class harvestTier) {

        targetType = targetType::ingredient;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(itemQuality, primaryHarvestTool, harvestTier);

    }

    // Constructor one tag

    inline ingredient_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned itemQuality, tag_class primaryHarvestTool, tag_class harvestTier, tag_class tag) {

        targetType = targetType::ingredient;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(itemQuality, primaryHarvestTool, harvestTier);

        addTag(tag);

    }

    // Constructor multiple tags

    inline ingredient_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned itemQuality, tag_class primaryHarvestTool, tag_class harvestTier, std::vector<tag_class> tagArr) {

        targetType = targetType::ingredient;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(itemQuality, primaryHarvestTool, harvestTier);

        addTag(tagArr);

    }

    // DECLARING VARS

    unsigned ingredientQuality = 0;
    tag_class primaryHarvestTool;
    tag_class harvestTier;

    std::unordered_map<std::string, int> propertyKey = {

        {"ingredientQuality", 0},
        {"primaryHarvestTool", 1},
        {"harvestTier", 2},

    };

    // FUNCTIONS

    // Input values into item
    void defineItem(unsigned itemQuality, tag_class primaryHarvestTool, tag_class harvestTier);

    // Show name and amount
    void displayItem();

    // Show detailed stats
    void inspectItem();

};
#endif INGREDIENT_CLASS_H