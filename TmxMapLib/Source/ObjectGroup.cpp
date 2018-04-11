#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/ObjectGroup.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
ObjectGroup::ObjectGroup()
    : LayerBase(LayerType::Object) {
}

//  ===========================================================================
ObjectGroup::ObjectGroup(
    const Map* map,
    const int tmxOrder,
    const XMLElement* groupElement)
    : LayerBase(LayerType::Object, map, tmxOrder, groupElement) {
    this->loadObjectGroup(groupElement);
}

//  ===========================================================================
const Object* ObjectGroup::getObject(const size_t index) const {
    if (index < mObjects.size()) {
        return &mObjects[index];
    } else {
        return nullptr;
    }
}

//  ===========================================================================
const std::vector<Object>& ObjectGroup::getObjects() const {
    return mObjects;
}

//  ===========================================================================
int ObjectGroup::getObjectCount() const {
    return mObjects.size();
}

//  ===========================================================================
void ObjectGroup::loadObjectGroup(const XMLElement* groupElement) {
    if (groupElement == nullptr) {
        throw NullArgumentException("groupElement");
    }

    int objectCount = countElements(groupElement, "object");
    mObjects.reserve(objectCount);

    const XMLElement* objectElement = groupElement->FirstChildElement("object");
    while (objectElement != nullptr) {
        mObjects.emplace_back(this, objectElement);
        objectElement = objectElement->NextSiblingElement("object");
    }
}
}