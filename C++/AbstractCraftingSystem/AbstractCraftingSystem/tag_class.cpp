#include "tag_class.h"

// Imposes this objects stats into the target stats
void tag_class::cloneTagInfo(tag_class& target) {

    target.tagName = tagName;
    target.tagDescription = tagDescription;
    target.tagType = tagType;
    target.targetType = targetType;
    target.tagModiAmount = tagModiAmount;

}