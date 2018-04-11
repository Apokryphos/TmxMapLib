#pragma once

#include "Property.h"
#include <unordered_map>
#include <string>
#include <vector>

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
class PropertySet
{
private:
    std::unordered_map<std::string, Property> mProperties;

    //  Friend classes that need to call LoadProperties
    friend class LayerBase;
    friend class Map;
    friend class Object;
    friend class Tileset;
    friend class TilesetTile;

    /*
    *   Loads properties from the specified XML element.
    */
    void loadProperties(const tinyxml2::XMLElement* propertiesElement);

public:

    /*
    *   Constructs an empty PropertySet.
    */
    PropertySet();

    /*
    *   Constructs a PropertySet from an XML element.
    */
    PropertySet(const tinyxml2::XMLElement* propertiesElement);

    /*
    *   Returns the value of the specified property as a bool.
    *   Returns the default value if the property does not exist or
    *   the value string cannot be converted.
    */
    bool getBoolValue(
        const std::string& propertyName,
        const bool defaultValue) const;

    /*
    *   Returns the value of the specified property as an double.
    *   Returns the default value if the property does not exist or
    *   the value string cannot be converted.
    */
    double getDoubleValue(
        const std::string& propertyName,
        const double defaultValue) const;

    /*
    *   Returns the value of the specified property as an float.
    *   Returns the default value if the property does not exist or
    *   the value string cannot be converted.
    */
    float getFloatValue(
        const std::string& propertyName,
        const float defaultValue) const;

    /*
    *   Returns the value of the specified property as an int.
    *   Returns the default value if the property does not exist or
    *   the value string cannot be converted.
    */
    int getIntValue(
        const std::string& propertyName,
        const int defaultValue) const;

    /*
    *   Returns all properties in this set.
    */
    std::vector<const Property*> getProperties() const;

    /*
    *   Returns the property with the specified name or null.
    *   if the property doesn't exist.
    */
    const Property* getProperty(const std::string& name) const;

    /*
    *   Returns the value of the specified property.
    *   Returns the default value if the property does not exist.
    */
    std::string getValue(
        const std::string& propertyName,
        const std::string& defaultValue) const;

    /*
    *   Checks if the property with the specified name exists.
    */
    bool hasProperty(const std::string& name) const;

    /*
    *   Checks if the property with the specified name and type exists.
    */
    bool hasProperty(
        const std::string& name,
        const PropertyType type) const;
};
}
