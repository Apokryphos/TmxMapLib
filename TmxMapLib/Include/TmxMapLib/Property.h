#ifndef TMXMAPLIB_PROPERTY_HEADER_INCLUDED
#define TMXMAPLIB_PROPERTY_HEADER_INCLUDED

#include <string>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    enum class PropertyType
    {
        String,
        Bool,
        Int,
        Float,
        Color,
        //File,
    };

    class Property
    {
    private:
        std::string mName;
        std::string mValue;
        PropertyType mType;

    public:

        /*
        *   Constructs a Property.
        */
        Property(
            const std::string& name,
            const std::string& value,
            PropertyType type);

        /*
        *   Constructs a Property from an XML element.
        */
        Property(const tinyxml2::XMLElement* propertyElement);

        /*
        *   Returns the value of this property as a bool.
        *   Throws an exception if the value string cannot be converted.
        */
        bool GetBoolValue() const;

        /*
        *   Returns the value of this property as a bool.
        *   Returns the default value if the value string cannot be converted.
        */
        bool GetBoolValue(const bool defaultValue) const;

        /*
        *   Returns the value of this property as a double.
        *   Throws an exception if the value string cannot be converted.
        */
        double GetDoubleValue() const;

        /*
        *   Returns the value of this property as a double.
        *   Returns the default value if the value string cannot be converted.
        */
        double GetDoubleValue(const double defaultValue) const;

        /*
        *   Returns the value of this property as a float.
        *   Throws an exception if the value string cannot be converted.
        */
        float GetFloatValue() const;

        /*
        *   Returns the value of this property as a float.
        *   Returns the default value if the value string cannot be converted.
        */
        float GetFloatValue(const float defaultValue) const;

        /*
        *   Returns the value of this property as an integer.
        *   Throws an exception if the value string cannot be converted.
        */
        int GetIntValue() const;

        /*
        *   Returns the value of this property as an integer.
        *   Returns the default value if the value string cannot be converted.
        */
        int GetIntValue(const int defaultValue) const;

        /*
        *   Returns the name of this property.
        */
        const std::string& GetName() const;

        /*
        *   Returns the type of this property.
        */
        PropertyType GetType() const;

        /*
        *   Returns the string value of this property.
        */
        const std::string& GetValue() const;

        /*
        *   Attempts to convert the value string to a bool. Does not change
        *   the input value if conversion fails.
        */
        void QueryBoolValue(bool& value) const;

        /*
        *   Attempts to convert the value string to a bool. Uses the default
        *   value if the conversion fails.
        */
        void QueryBoolValue(bool& value, const bool defaultValue) const;

        /*
        *   Attempts to convert the value string to a double. Does not change
        *   the input value if conversion fails.
        */
        void QueryDoubleValue(double& value) const;

        /*
        *   Attempts to convert the value string to a double. Uses the default
        *   value if the conversion fails.
        */
        void QueryDoubleValue(double& value, const double defaultValue) const;

        /*
        *   Attempts to convert the value string to a float. Does not change
        *   the input value if conversion fails.
        */
        void QueryFloatValue(float& value) const;

        /*
        *   Attempts to convert the value string to a float. Uses the default
        *   value if the conversion fails.
        */
        void QueryFloatValue(float& value, const float defaultValue) const;

        /*
        *   Attempts to convert the value string to an int. Does not change
        *   the input value if conversion fails.
        */
        void QueryIntValue(int& value) const;

        /*
        *   Attempts to convert the value string to an int. Uses the default
        *   value if the conversion fails.
        */
        void QueryIntValue(int& value, const int defaultValue) const;
    };
}

#endif