#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Property.h"
#include <tinyxml2.h>
#include <stdexcept>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    Property::Property(
        const std::string& name,
        const std::string& value,
        PropertyType type)
        :   mName(name),
            mValue(value),
            mType(type)
    {
    }

    //  =======================================================================
    Property::Property(const XMLElement* propertyElement)
    {
        if (propertyElement == nullptr)
        {
            throw NullArgumentException("propertyElement");
        }

        if (propertyElement->Attribute("name") == nullptr)
        {
            throw XmlAttributeException("name");
        }

        mName = propertyElement->Attribute("name");

        if (propertyElement->Attribute("type") == nullptr)
        {
            mType = PropertyType::String;

            if (propertyElement->Attribute("value") != nullptr)
            {
                mValue = propertyElement->Attribute("value");
            }
            else
            {
                //  Multi-line strings are stored in XML text
                mValue = propertyElement->GetText();
            }
        }
        else
        {
            std::string type = propertyElement->Attribute("type");

            if (type == "bool")
            {
                mType = PropertyType::Bool;
            }
            else if (type == "float")
            {
                mType = PropertyType::Float;
            }
            else if (type == "int")
            {
                mType = PropertyType::Int;
            }
            else if (type == "color")
            {
                mType = PropertyType::Color;
            }
            else
            {
                throw std::runtime_error("Property type case is not implemented.");
            }

            if (propertyElement->Attribute("value") == nullptr)
            {
                throw XmlAttributeException("value");
            }

            mValue = propertyElement->Attribute("value");
        }
    }

    //  =======================================================================
    bool Property::GetBoolValue() const
    {
        if (mValue == "true")
        {
            return true;
        }
        else if (mValue == "false")
        {
            return false;
        }

        throw std::invalid_argument("Cannot convert string value to boolean.");
    }

    //  =======================================================================
    bool Property::GetBoolValue(const bool defaultValue) const
    {
        try
        {
            return GetBoolValue();
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
    }

    //  =======================================================================
    double Property::GetDoubleValue() const
    {
        return stod(mValue);
    }

    //  =======================================================================
    double Property::GetDoubleValue(const double defaultValue) const
    {
        try
        {
            return GetDoubleValue();
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
    }

    //  =======================================================================
    float Property::GetFloatValue() const
    {
        return stof(mValue);
    }

    //  =======================================================================
    float Property::GetFloatValue(const float defaultValue) const
    {
        try
        {
            return GetFloatValue();
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
    }

    //  =======================================================================
    int Property::GetIntValue() const
    {
        return std::stoi(mValue);
    }

    //  =======================================================================
    int Property::GetIntValue(const int defaultValue) const
    {
        try
        {
            return GetIntValue();
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
    }

    //  =======================================================================
    const std::string& Property::GetName() const
    {
        return mName;
    }

    //  =======================================================================
    PropertyType Property::GetType() const
    {
        return mType;
    }

    //  =======================================================================
    const std::string& Property::GetValue() const
    {
        return mValue;
    }

    //  =======================================================================
    void Property::QueryBoolValue(bool& value) const
    {
        try
        {
            value = GetBoolValue();
        }
        catch (const std::exception&)
        {
            return;
        }
    }

    //  =======================================================================
    void Property::QueryBoolValue(bool& value, const bool defaultValue) const
    {
        try
        {
            value = GetBoolValue();
        }
        catch (const std::exception&)
        {
            value = defaultValue;
        }
    }

    //  =======================================================================
    void Property::QueryDoubleValue(double& value) const
    {
        try
        {
            value = GetDoubleValue();
        }
        catch (const std::exception&)
        {
            return;
        }
    }

    //  =======================================================================
    void Property::QueryDoubleValue(double& value, const double defaultValue) const
    {
        try
        {
            value = GetDoubleValue();
        }
        catch (const std::exception&)
        {
            value = defaultValue;
        }
    }

    //  =======================================================================
    void Property::QueryFloatValue(float& value) const
    {
        try
        {
            value = GetFloatValue();
        }
        catch (const std::exception&)
        {
            return;
        }
    }

    //  =======================================================================
    void Property::QueryFloatValue(float& value, const float defaultValue) const
    {
        try
        {
            value = GetFloatValue();
        }
        catch (const std::exception&)
        {
            value = defaultValue;
        }
    }

    //  =======================================================================
    void Property::QueryIntValue(int& value) const
    {
        try
        {
            value = GetIntValue();
        }
        catch (const std::exception&)
        {
            return;
        }
    }

    //  =======================================================================
    void Property::QueryIntValue(int& value, const int defaultValue) const
    {
        try
        {
            value = GetIntValue();
        }
        catch (const std::exception&)
        {
            value = defaultValue;
        }
    }
}