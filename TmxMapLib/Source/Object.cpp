#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/GidUtil.h"
#include "TmxMapLib/Object.h"
#include <tinyxml2.h>
#include <iterator>
#include <sstream>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    void Object::LoadPoints(const tinyxml2::XMLElement* polyElement)
    {
        if (polyElement == nullptr)
        {
            throw NullArgumentException("polyElement");
        }

        if (polyElement->Attribute("points"))
        {
            //  Points are CSV separated by spaces
            std::stringstream pointsStream(polyElement->Attribute("points"));

            //  Break points pair string into CSV pairs
            std::istream_iterator<std::string> itr(pointsStream);
            std::istream_iterator<std::string> end;
            std::vector<std::string> pairStrings(itr, end);

            //  Breaks CSV pairs into points
            for (auto pairString : pairStrings)
            {
                double pointX, pointY;
                std::stringstream stream(pairString);
                stream >> pointX;
                stream.ignore();
                stream >> pointY;
                mPoints.emplace_back(pointX, pointY);
            }
        }
    }

    //  =======================================================================
    void Object::LoadObject(const tinyxml2::XMLElement* objectElement)
    {
        if (objectElement->QueryIntAttribute("id", &mId) != XML_NO_ERROR)
        {
            throw XmlAttributeException("id");
        }

        if (objectElement->Attribute("name"))
        {
            mName = objectElement->Attribute("name");
        }

        if (objectElement->Attribute("type"))
        {
            mType = objectElement->Attribute("type");
        }

        if (objectElement->QueryDoubleAttribute("x", &mX) != XML_NO_ERROR)
        {
            throw XmlAttributeException("x");
        }

        if (objectElement->QueryDoubleAttribute("y", &mY) != XML_NO_ERROR)
        {
            throw XmlAttributeException("y");
        }

        objectElement->QueryDoubleAttribute("width", &mWidth);
        objectElement->QueryDoubleAttribute("height", &mHeight);

        if (objectElement->Attribute("gid"))
        {
            unsigned int rawGid;
            objectElement->QueryUnsignedAttribute("gid", &rawGid);
            mTile = std::make_unique<Tile>(rawGid);

            mObjectType = ObjectType::Tile;
        }
        else if (objectElement->FirstChildElement("ellipse"))
        {
            mObjectType = ObjectType::Ellipse;
        }
        else if (objectElement->FirstChildElement("polygon"))
        {
            mObjectType = ObjectType::Polygon;
            LoadPoints(objectElement->FirstChildElement("polygon"));
        }
        else if (objectElement->FirstChildElement("polyline"))
        {
            mObjectType = ObjectType::Polyline;
            LoadPoints(objectElement->FirstChildElement("polyline"));
        }
        else
        {
            mObjectType = ObjectType::Basic;
        }

        if (objectElement->FirstChildElement("properties"))
        {
            mProperties.LoadProperties(objectElement->FirstChildElement("properties"));
        }
    }

    //  =======================================================================
    Object::Object(const tinyxml2::XMLElement* objectElement)
    {
        LoadObject(objectElement);
    }

    //  =======================================================================
    double Object::GetHeight() const
    {
        return mHeight;
    }

    //  =======================================================================
    int Object::GetId() const
    {
        return mId;
    }

    //  =======================================================================
    const std::string& Object::GetName() const
    {
        return mName;
    }

    //  =======================================================================
    ObjectType Object::GetObjectType() const
    {
        return mObjectType;
    }

    //  =======================================================================
    int Object::GetPointCount() const
    {
        return mPoints.size();
    }

    //  =======================================================================
    const std::vector<Point>& Object::GetPoints() const
    {
        return mPoints;
    }

    //  =======================================================================
    const PropertySet& Object::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    const Tile* Object::GetTile() const
    {
        return mTile.get();
    }

    //  =======================================================================
    const std::string& Object::GetType() const
    {
        return mType;
    }

    //  =======================================================================
    double Object::GetWidth() const
    {
        return mWidth;
    }

    //  =======================================================================
    double Object::GetX() const
    {
        return mX;
    }

    //  =======================================================================
    double Object::GetY() const
    {
        return mY;
    }
}