#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/PropertySet.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>
#include <vector>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
PropertySet::PropertySet() {}

//  ===========================================================================
PropertySet::PropertySet(const tinyxml2::XMLElement* propertiesElement) {
    this->loadProperties(propertiesElement);
}

//  ===========================================================================
bool PropertySet::getBoolValue(
    const std::string& propertyName,
    const bool defaultValue) const {
    const Property* property = this->getProperty(propertyName);

    return
        property != nullptr ?
        property->getBoolValue(defaultValue) :
        defaultValue;
}

//  ===========================================================================
double PropertySet::getDoubleValue(
    const std::string& propertyName,
    const double defaultValue) const {
    const Property* property = this->getProperty(propertyName);

    return
        property != nullptr ?
        property->getDoubleValue(defaultValue) :
        defaultValue;
}

//  ===========================================================================
float PropertySet::getFloatValue(
    const std::string& propertyName,
    const float defaultValue) const {
    const Property* property = this->getProperty(propertyName);

    return
        property != nullptr ?
        property->getFloatValue(defaultValue) :
        defaultValue;
}

//  ===========================================================================
int PropertySet::getIntValue(
    const std::string& propertyName,
    const int defaultValue) const {
    const Property* property = this->getProperty(propertyName);

    return
        property != nullptr ?
        property->getIntValue(defaultValue) :
        defaultValue;
}

//  ===========================================================================
std::vector<const Property*> PropertySet::getProperties() const {
    std::vector<const Property*> properties;

    for (const auto& pair : mProperties) {
        properties.push_back(&pair.second);
    }

    return properties;
}

//  ===========================================================================
const Property* PropertySet::getProperty(const std::string& name) const {
    auto p = mProperties.find(name);
    return p != mProperties.end() ? &p->second : nullptr;
}

//  ===========================================================================
std::string PropertySet::getValue(
    const std::string& propertyName,
    const std::string& defaultValue) const {
    const Property* property = this->getProperty(propertyName);

    return
        property != nullptr ?
        property->getValue() :
        defaultValue;
}

//  ===========================================================================
bool PropertySet::hasProperty(const std::string& name) const {
    auto p = mProperties.find(name);
    return p != mProperties.end();
}

//  ===========================================================================
bool PropertySet::hasProperty(
    const std::string& name,
    const PropertyType type) const {
    auto p = mProperties.find(name);
    return
        p != mProperties.end() ?
        p->second.getType() == type :
        false;
}

//  ===========================================================================
void PropertySet::loadProperties(const XMLElement* propertiesElement) {
    if (propertiesElement == nullptr) {
        throw NullArgumentException("propertiesElement");
    }

    int propertyCount = countElements(propertiesElement, "property");
    mProperties.reserve(propertyCount);

    const XMLElement* propertyElement = propertiesElement->FirstChildElement("property");
    while (propertyElement != nullptr) {
        if (propertyElement->Attribute("name") == nullptr) {
            throw XmlAttributeException("name");
        }

        mProperties.emplace(
            propertyElement->Attribute("name"),
            propertyElement);

        propertyElement = propertyElement->NextSiblingElement("property");
    }
}
}