#include "tagHandler_class.h"
#include "tag_class.h"
#include "productUsable_class.h"

// Create an array of tags based off of arrays of inputs
void tagHandler_class::tagArrayMaker(std::vector<tag_class>& tagArr, std::vector<std::string> tagName, 
    std::vector<unsigned> tagType, std::vector<unsigned> targetType, std::vector<unsigned> tagModiAmount) {

    for (int i = 0; i < tagName.size(); i++) {

        // Create tag class and push it into array
        tag_class temp(tagName[i], tagType[i], targetType[i], tagModiAmount[i]);

        tagArr.push_back(temp);
    }

}

static void tagArrayMaker(std::vector<tag_class>& tagArr, std::vector<std::string> tagName, std::vector<std::string> tagDesc,
    std::vector<unsigned> tagType, std::vector<unsigned> targetType, std::vector<unsigned> tagModiAmount) {

    for (int i = 0; i < tagName.size(); i++) {

        // Create tag class and push it into array
        tag_class temp(tagName[i], tagDesc[i], tagType[i], targetType[i], tagModiAmount[i]);

        tagArr.push_back(temp);
    }

}


// Take two tag arrays and a string array. Compare the string array to tag array 1, and insert any matches into tag array 2.
void tagHandler_class::tagStringCopy(std::vector<tag_class> tagArr1, std::vector<tag_class>& tagArr2, std::vector<std::string> tagName) {

    // Loop through names, compare that one name through each entry of array
    for (int i = 0; i < tagName.size(); i++) {
        for (int j = 0; j < tagArr1.size(); j++) {

            // Compare names to array one
            if (tagName[i] == tagArr1[j].tagName) {

                tagArr2.push_back(tagArr1[j]);
                // Match has been made, exit loop and move onto next string element
                break;
            }
        }
    }
}

// Take a tag array and string, then return a tag from the tag array as it's own object
void tagHandler_class::tagArrayExtract(std::vector<tag_class> tagArr, tag_class& target, std::string tagName) {

    for (int i = 0; i < tagArr.size(); i++) {

        if (tagName == tagArr[i].tagName) {

            tagArr[i].cloneTagInfo(target);

        }
    }
}

// Function that acts if it's applicable to any
void tagHandler_class::tagImplementer(tag_class tag, item_class& target) {
    
    
    
}

// Function that acts if it's an ingredient
void tagHandler_class::tagImplementer(tag_class tag, ingredient_class& target) {
    
    std::cout << "INGREDIENT FUNC RAN!" << std::endl;
    
}

// Function that acts if it's a productUsable
void tagHandler_class::tagImplementer(tag_class tag, productUsable_class& target) {
    
    std::cout << "PRODUCT USABLE FUNC RAN!" << std::endl;
    
}