#ifndef TMXMAPLIB_OBJECT_GROUP_HEADER_INCLUDED
#define TMXMAPLIB_OBJECT_GROUP_HEADER_INCLUDED

#include "LayerBase.h"
#include "Object.h"
#include <vector>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class ObjectGroup : public LayerBase
    {
    private:
        std::vector<Object> mObjects;

        //  Friend classes that need to call LoadObjectGroup
        friend class TilesetTile;

        void LoadObjectGroup(const tinyxml2::XMLElement* groupElement);

    public:

        /*
        *   Constructs an empty ObjectGroup.
        */
        ObjectGroup();

        /*
        *   Constructs an ObjectGroup from the specified XML element.
        */
        ObjectGroup(
            const Map* map,
            const int tmxOrder,
            const tinyxml2::XMLElement* groupElement);

        /*
        *   Returns the object at the specified index or null
        *   if the index is out of range.
        */
        const Object* GetObject(const int index) const;

        /*
        *   Returns the objects in this group.
        */
        const std::vector<Object>& GetObjects() const;

        /*
        *   Returns the total number of objects in this group.
        */
        int GetObjectCount() const;
    };
}

#endif