#ifndef TMXMAPLIB_PROPERTY_SET_HEADER_INCLUDED
#define TMXMAPLIB_PROPERTY_SET_HEADER_INCLUDED

#include "Property.h"
#include <unordered_map>
#include <string>

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
        friend class TmxMap;
        friend class LayerBase;
        friend class Object;
        friend class Tileset;
        friend class TilesetTile;

        /*
        *   Loads properties from the specified XML element.
        */
        void LoadProperties(const tinyxml2::XMLElement* propertiesElement);

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
        *   Returns the property with the specified name or null.
        *   if the property doesn't exist.
        */
        const Property* GetProperty(const std::string& name) const;

        /*
        *   Checks if the property with the specified name exists.
        */
        bool HasProperty(const std::string& name) const;

        /*
        *   Checks if the property with the specified name and type exists.
        */
        bool HasProperty(
            const std::string& name,
            const PropertyType type) const;
    };
}

#endif