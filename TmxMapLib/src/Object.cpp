#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/GidUtil.h"
#include "TmxMapLib/Object.h"
#include "TmxMapLib/ObjectGroup.h"
#include "TmxMapLib/Map.h"
#include <tinyxml2.h>
#include <cassert>
#include <iterator>
#include <sstream>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
void Object::loadPoints(const tinyxml2::XMLElement* polyElement) {
    if (polyElement == nullptr) {
        throw NullArgumentException("polyElement");
    }

    if (polyElement->Attribute("points")) {
        //  Points are CSV separated by spaces
        std::stringstream pointsStream(polyElement->Attribute("points"));

        //  Break points pair string into CSV pairs
        std::istream_iterator<std::string> itr(pointsStream);
        std::istream_iterator<std::string> end;
        std::vector<std::string> pairStrings(itr, end);

        //  Breaks CSV pairs into points
        for (auto pairString : pairStrings) {
            double pointX, pointY;
            std::stringstream stream(pairString);
            stream >> pointX;
            stream.ignore();
            stream >> pointY;
            mPoints.emplace_back(pointX, pointY);
        }
    }
}

//  ===========================================================================
void Object::loadObject(const tinyxml2::XMLElement* objectElement) {
    if (objectElement->QueryIntAttribute("id", &mId) != XML_SUCCESS) {
        throw XmlAttributeException("id");
    }

    if (objectElement->Attribute("name")) {
        mName = objectElement->Attribute("name");
    }

    if (objectElement->Attribute("type")) {
        mType = objectElement->Attribute("type");
    }

    if (objectElement->QueryDoubleAttribute("x", &mX) != XML_SUCCESS) {
        throw XmlAttributeException("x");
    }

    if (objectElement->QueryDoubleAttribute("y", &mY) != XML_SUCCESS) {
        throw XmlAttributeException("y");
    }

    objectElement->QueryDoubleAttribute("width", &mWidth);
    objectElement->QueryDoubleAttribute("height", &mHeight);

    if (objectElement->Attribute("gid")) {
        //  Map should be valid since Tile objects don't exist in
        //  tileset collision object groups
        assert(mObjectGroup->getMap() != nullptr);

        unsigned int rawGid;
        objectElement->QueryUnsignedAttribute("gid", &rawGid);
        mTile = std::make_shared<Tile>(
            rawGid,
            mX / mObjectGroup->getMap()->getTileWidth(),
            mY / mObjectGroup->getMap()->getTileHeight());

        mObjectType = ObjectType::Tile;
    } else if (objectElement->FirstChildElement("ellipse")) {
        mObjectType = ObjectType::Ellipse;
    } else if (objectElement->FirstChildElement("polygon")) {
        mObjectType = ObjectType::Polygon;
        this->loadPoints(objectElement->FirstChildElement("polygon"));
    } else if (objectElement->FirstChildElement("polyline")) {
        mObjectType = ObjectType::Polyline;
        this->loadPoints(objectElement->FirstChildElement("polyline"));
    } else {
        mObjectType = ObjectType::Basic;
    }

    if (objectElement->FirstChildElement("properties")) {
        mProperties.loadProperties(objectElement->FirstChildElement("properties"));
    }
}

//  ===========================================================================
Object::Object(
    const ObjectGroup* objectGroup,
    const tinyxml2::XMLElement* objectElement)
:   mObjectGroup(objectGroup) {
    if (objectGroup == nullptr) {
        throw NullArgumentException("objectGroup");
    }

    this->loadObject(objectElement);
}

//  ===========================================================================
double Object::getHeight() const {
    return mHeight;
}

//  ===========================================================================
int Object::getId() const {
    return mId;
}

//  ===========================================================================
const std::string& Object::getName() const {
    return mName;
}

//  ===========================================================================
ObjectType Object::getObjectType() const {
    return mObjectType;
}

//  ===========================================================================
int Object::getPointCount() const {
    return mPoints.size();
}

//  ===========================================================================
const std::vector<Point>& Object::getPoints() const {
    return mPoints;
}

//  ===========================================================================
const PropertySet& Object::getPropertySet() const {
    return mProperties;
}

//  ===========================================================================
const Tile* Object::getTile() const {
    return mTile.get();
}

//  ===========================================================================
const std::string& Object::getType() const {
    return mType;
}

//  ===========================================================================
double Object::getWidth() const {
    return mWidth;
}

//  ===========================================================================
double Object::getX() const {
    return mX;
}

//  ===========================================================================
double Object::getY() const {
    return mY;
}
}