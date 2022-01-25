// Handles tags, assigning them to their type and calculating their affects
#ifndef TAG_HANDLERCLASS_H
#define TAG_HANDLERCLASS_H

#include "tag_class.h"
class item_class;
class productUsable_class;
class ingredient_class;

#include <iostream>
#include <vector>
#include <string>

class tagHandler_class {
public:

    // FUNCTIONS

    // Create an array of tags based off of arrays of inputs
    static void tagArrayMaker(std::vector<tag_class>& tagArr, std::vector<std::string> tagName, std::vector<unsigned> tagType, std::vector<unsigned> targetType, std::vector<unsigned> tagModiAmount);

    // Create an array of tags based off of arrays of inputs with tag description
    static void tagArrayMaker(std::vector<tag_class>& tagArr, std::vector<std::string> tagName, std::vector<std::string> tagDesc, std::vector<unsigned> tagType, std::vector<unsigned> targetType, std::vector<unsigned> tagModiAmount);

    // Take two tag arrays and a string array. Compare the string array to tag array 1, and copy any matches into tag array 2.
    static void tagStringCopy(std::vector<tag_class> tagArr1, std::vector<tag_class>& tagArr2, std::vector<std::string> tagName);

    // Take a tag array and string, then return a tag from the tag array as it's own object
    static void tagArrayExtract(std::vector<tag_class> tagArr, tag_class& target, std::string tagName);

    // Function handles the harvestability of an item based off of its tags
    static void tagHarvestability(productUsable_class target);

    // Function that acts if it's applicable to any
    static void tagImplementer(tag_class tag, item_class& target);

    // Function that acts if it's an ingredient
    static void tagImplementer(tag_class tag, ingredient_class& target);

    // Function that acts if it's a productUsable
    static void tagImplementer(tag_class tag, productUsable_class& target);

    // TEMPLATES

    // Tag Verify Change functions should be run whenever tags are modified. This includes when an item (or any of it's children) are defined or redefined at any point.
    // The templates should only be used on item_class and it's children

    // Function that takes in a series of tags and compares them all to one target
    template <typename Item>
    inline static void tagVerifyChange(std::vector<tag_class> tagArr, Item target) {

        bool tagOnItem = false;

        // Loop through each tag in array
        for (int j = 0; j < tagArr.size(); j++) {

            // Check if tag can be applicable to item
            if (tagArr[j].targetType == tag_class::targetTypeEnum::any || static_cast<int>(tagArr[j].targetType) == static_cast<int>(target.targetType)) {

                // Run through tags, check if item has tag
                for (int i = 0; i < target.itemTags.size(); i++) {

                    if (target.itemTags[i].tagName == tagArr[j].tagName) {

                        tagOnItem = true;
                    }

                }
                if (tagOnItem == true) {

                    tagHandler_class::tagImplementer(tagArr[j], target);
                }
                else {

                    std::cout << "Tag is not on item." << std::endl;

                }

            }
            else {

                std::cout << "Tag not applicable to item." << std::endl;

            }
        }
    }

    // Function that determines if the tag is applicable and then implements changes
    template <typename Item>
    inline static void tagVerifyChange(tag_class tag, Item target) {

        bool tagOnItem = false;

        // Check if tag can be applicable to item
        if (tag.targetType == tag_class::targetTypeEnum::any || static_cast<int>(tag.targetType) == static_cast<int>(target.targetType)) {

            // Run through tags, check if item has tag
            for (int i = 0; i < target.itemTags.size(); i++) {

                if (target.itemTags[i].tagName == tag.tagName) {

                    tagOnItem = true;
                }

            }
            if (tagOnItem == true) {

                tagHandler_class::tagImplementer(tag, target);
            }
            else {

                std::cout << "Tag is not on item." << std::endl;

            }

        }
        else {

            std::cout << "Tag not applicable to item." << std::endl;

        }
    }

};
#endif TAG_HANDLERCLASS_H