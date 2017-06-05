#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/ObjectGroup.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    ObjectGroup::ObjectGroup()
        : LayerBase(LayerType::Object)
    {
    }

    //  =======================================================================
    ObjectGroup::ObjectGroup(const int tmxOrder, const XMLElement* groupElement)
        : LayerBase(LayerType::Object, tmxOrder, groupElement)
    {
        LoadObjectGroup(groupElement);
    }

    //  =======================================================================
    void ObjectGroup::LoadObjectGroup(const XMLElement* groupElement)
    {
        if (groupElement == nullptr)
        {
            throw NullArgumentException("groupElement");
        }

        int objectCount = CountElements(groupElement, "object");
        mObjects.reserve(objectCount);

        const XMLElement* objectElement = groupElement->FirstChildElement("object");
        while (objectElement != nullptr)
        {
            mObjects.emplace_back(objectElement);
            objectElement = objectElement->NextSiblingElement("object");
        }
    }

    //  =======================================================================
    const Object* ObjectGroup::GetObject(const int index) const
    {
        if (index >= 0 && index < mObjects.size())
        {
            return &mObjects[index];
        }
        else
        {
            return nullptr;
        }
    }

    //  =======================================================================
    const std::vector<Object>& ObjectGroup::GetObjects()
    {
        return mObjects;
    }

    //  =======================================================================
    int ObjectGroup::GetObjectCount() const
    {
        return mObjects.size();
    }
}