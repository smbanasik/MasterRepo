// Defines qualities every tag should have

#ifndef TAG_CLASS_H
#define TAG_CLASS_H

#include <string>

class tag_class {

public:

    // STATIC
    
    // Enum things, change maxes to correlate wwith amount in enumerators

    static enum class tagTypeEnum { itemTag, enchantment, modifier };
    static enum class targetTypeEnum { any, ingredient, part, productUsable, productUnusable };
    static const unsigned tagEnumMaxIndex = 2;
    static const unsigned targetEnumMaxIndex = 4;

    // CONSTRUCTORS

    inline tag_class() {

    }

    // No description tag constructor
    inline tag_class(std::string tagName, unsigned tagType, unsigned targetType, float tagModiAmount) {

        // If the inputted values are over the limit, put them on the max one

        if (tagType > tagEnumMaxIndex) tagType = tagEnumMaxIndex;
        if (targetType > targetEnumMaxIndex) targetType = targetEnumMaxIndex;

        // Checks passed, assign the values

        this->tagName = tagName;
        this->tagType = (tagTypeEnum)tagType;
        this->targetType = (targetTypeEnum)targetType;
        this->tagModiAmount = tagModiAmount;

    }

    // Full tag constructor
    inline tag_class(std::string tagName, std::string tagDesc, unsigned tagType, unsigned targetType, float tagModiAmount) {

        // If the inputted values are over the limit, put them on the max one

        if (tagType > tagEnumMaxIndex) tagType = tagEnumMaxIndex;
        if (targetType > targetEnumMaxIndex) targetType = targetEnumMaxIndex;

        // Checks passed, assign the values

        this->tagName = tagName;
        this->tagDescription = tagDesc;
        this->tagType = (tagTypeEnum)tagType;
        this->targetType = (targetTypeEnum)targetType;
        this->tagModiAmount = tagModiAmount;

    }

    // DECLARING VARS

    std::string tagName = "";
    std::string tagDescription = "";
    tagTypeEnum tagType = tagTypeEnum::itemTag;
    targetTypeEnum targetType = targetTypeEnum::any;
    std::string targetProperty = "";
    std::string targetNameModi = "";
    float tagModiAmount = 0;

    // Imposes this objects stats into the target stats
    void cloneTagInfo(tag_class& target);

    // Overloading = operator to make life easy
    void operator = (const tag_class& source) {

        tagName = source.tagName;
        tagDescription = source.tagDescription;
        tagType = source.tagType;
        targetType = source.targetType;
        tagModiAmount = source.tagModiAmount;

    }

};
#endif TAG_CLASS_H