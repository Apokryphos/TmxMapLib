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

    void loadPoints(const tinyxml2::XMLElement* polyElement);
    void loadObject(const tinyxml2::XMLElement* objectElement);

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
    const Tile* getTile() const;

    /*
    *   Returns the height of this object in pixels.
    */
    double getHeight() const;

    /*
    *   Returns the unique object ID of this object.
    */
    int getId() const;

    /*
    *   Returns the name of this object.
    */
    const std::string& getName() const;

    /*
    *   Returns the object type.
    */
    ObjectType getObjectType() const;

    /*
    *   Returns the number of points.
    */
    int getPointCount() const;

    /*
    *   Returns the points.
    */
    const std::vector<Point>& getPoints() const;

    /*
    *   Returns the set of properties for this object.
    */
    const PropertySet& getPropertySet() const;

    /*
    *   Returns the type string for this object.
    */
    const std::string& getType() const;

    /*
    *   Returns the width of this object in pixels.
    */
    double getWidth() const;

    /*
    *   Returns the position X component of this object.
    */
    double getX() const;

    /*
    *   Returns the position Y component of this object.
    */
    double getY() const;
};
}
