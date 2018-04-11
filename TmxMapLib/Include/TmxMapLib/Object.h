#pragma once

#include "Point.h"
#include "PropertySet.h"
#include "Tile.h"
#include <memory>
#include <string>
#include <vector>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class ObjectGroup;

    enum class ObjectType
    {
        Basic,
        Ellipse,
        Polygon,
        Polyline,
        Tile,
    };

    class Object
    {
    private:
        int mId;
        ObjectType mObjectType;
        double mX;
        double mY;
        double mWidth;
        double mHeight;
        std::string mName;
        std::string mType;
        PropertySet mProperties;
        std::vector<Point> mPoints;
        std::shared_ptr<Tile> mTile;
        const ObjectGroup* mObjectGroup;

        void LoadPoints(const tinyxml2::XMLElement* polyElement);
        void LoadObject(const tinyxml2::XMLElement* objectElement);

    public:

        /*
        *   Constructs an Object from the specified XML element.
        */
        Object(
            const ObjectGroup* objectGroup,
            const tinyxml2::XMLElement* objectElement);

        /*
        *   Returns the tile for an ObjectType::Tile object or
        *   null for all other ObjectTypes.
        */
        const Tile* GetTile() const;

        /*
        *   Returns the height of this object in pixels.
        */
        double GetHeight() const;

        /*
        *   Returns the unique object ID of this object.
        */
        int GetId() const;

        /*
        *   Returns the name of this object.
        */
        const std::string& GetName() const;

        /*
        *   Returns the object type.
        */
        ObjectType GetObjectType() const;

        /*
        *   Returns the number of points.
        */
        int GetPointCount() const;

        /*
        *   Returns the points.
        */
        const std::vector<Point>& GetPoints() const;

        /*
        *   Returns the set of properties for this object.
        */
        const PropertySet& GetPropertySet() const;

        /*
        *   Returns the type string for this object.
        */
        const std::string& GetType() const;

        /*
        *   Returns the width of this object in pixels.
        */
        double GetWidth() const;

        /*
        *   Returns the position X component of this object.
        */
        double GetX() const;

        /*
        *   Returns the position Y component of this object.
        */
        double GetY() const;
    };
}
