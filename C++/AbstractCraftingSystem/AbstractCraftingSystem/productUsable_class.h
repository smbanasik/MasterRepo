// This class containts elements needed for usable products, such as weapons and tools..
// It's parent is item class, but ingredient (later parts class) is included since an array of ingredients (later parts) will make up recipes.
#ifndef PRODUCTUSABLE_CLASS_H
#define PRODUCTUSABLE_CLASS_H

#include "ingredient_class.h"

class productUsable_class : public item_class {

public:

    // CONSTRUCTORS

    // Empty Constructor

    inline productUsable_class() {

        targetType = targetType::productUsable;

    }

    // Constructor no tag

    inline productUsable_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned damage, unsigned durability, unsigned maxDurability, unsigned harvestAmount) {

        targetType = targetType::productUsable;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(damage, durability, maxDurability, harvestAmount);

    }

    // Constructor one tag

    inline productUsable_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned damage, unsigned durability, unsigned maxDurability, unsigned harvestAmount, tag_class tag) {

        targetType = targetType::productUsable;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(damage, durability, maxDurability, harvestAmount);;

        addTag(tag);

    }

    // Constructor multiple tags

    inline productUsable_class(std::string itemName, std::string itemDescription, unsigned itemCount, unsigned itemMaxCount,
        unsigned damage, unsigned durability, unsigned maxDurability, unsigned harvestAmount, std::vector<tag_class> tagArr) {

        targetType = targetType::productUsable;
        item_class::defineItem(itemName, itemDescription, itemCount, itemMaxCount);
        defineItem(damage, durability, maxDurability, harvestAmount);;

        addTag(tagArr);

    }

    // DECLARING VARS

    // Implement Max durability
    unsigned damage = 0;
    unsigned durability = 0;
    unsigned maxDurability = 0;
    unsigned harvestAmount = 0;
    std::vector<tag_class> enchantments;
    std::vector<tag_class> modifiers;

    std::unordered_map<std::string, int> propertyKey = {

        {"damage", 0},
        {"maxDurability", 1},
        {"harvestAmount", 2},

    };

    // FUNCTIONS

    bool checkHarvestability(ingredient_class harvestTarget);

    // Add enchantments

    void addEnchantment(tag_class enchName);

    void addEnchantment(std::vector<tag_class> enchArr);

    // Add modifiers

    void addModifier(tag_class modiName);

    void addModifier(std::vector<tag_class> modiArr);

    // Input values into item
    void defineItem(unsigned damage, unsigned durability, unsigned harvestAmount, unsigned maxDurability);

    // Show name and amount
    void displayItem();

    // Show detailed stats
    void inspectItem();

};
#endif PRODUCTUSABLE_CLASS_H