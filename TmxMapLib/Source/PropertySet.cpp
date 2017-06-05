#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/PropertySet.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    PropertySet::PropertySet()
    {
    }

    //  =======================================================================
    PropertySet::PropertySet(const tinyxml2::XMLElement* propertiesElement)
    {
        LoadProperties(propertiesElement);
    }

    //  =======================================================================
    const Property* PropertySet::GetProperty(const std::string& name) const
    {
        auto p = mProperties.find(name);
        return p != mProperties.end() ? &p->second : nullptr;
    }

    //  =======================================================================
    bool PropertySet::HasProperty(const std::string& name) const
    {
        auto p = mProperties.find(name);
        return p != mProperties.end();
    }

    //  =======================================================================
    bool PropertySet::HasProperty(
        const std::string& name,
        const PropertyType type) const
    {
        auto p = mProperties.find(name);
        return
            p != mProperties.end() ?
            p->second.GetType() == type :
            false;
    }

    //  =======================================================================
    void PropertySet::LoadProperties(const XMLElement* propertiesElement)
    {
        if (propertiesElement == nullptr)
        {
            throw NullArgumentException("propertiesElement");
        }

        int propertyCount = CountElements(propertiesElement, "property");
        mProperties.reserve(propertyCount);

        const XMLElement* propertyElement = propertiesElement->FirstChildElement("property");
        while (propertyElement != nullptr)
        {
            if (propertyElement->Attribute("name") == nullptr)
            {
                throw XmlAttributeException("name");
            }

            mProperties.emplace(
                propertyElement->Attribute("name"),
                propertyElement);

            propertyElement = propertyElement->NextSiblingElement("property");
        }
    }
}