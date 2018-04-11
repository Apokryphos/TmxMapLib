#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Property.h"
#include <tinyxml2.h>
#include <stdexcept>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
Property::Property(
    const std::string& name,
    const std::string& value,
    PropertyType type)
    :   mName(name),
        mValue(value),
        mType(type) {
}

//  ===========================================================================
Property::Property(const XMLElement* propertyElement) {
    if (propertyElement == nullptr) {
        throw NullArgumentException("propertyElement");
    }

    if (propertyElement->Attribute("name") == nullptr) {
        throw XmlAttributeException("name");
    }

    mName = propertyElement->Attribute("name");

    if (propertyElement->Attribute("type") == nullptr) {
        mType = PropertyType::String;

        if (propertyElement->Attribute("value") != nullptr) {
            mValue = propertyElement->Attribute("value");
        } else {
            //  Multi-line strings are stored in XML text
            mValue = propertyElement->GetText();
        }
    } else {
        std::string type = propertyElement->Attribute("type");

        if (type == "bool") {
            mType = PropertyType::Bool;
        } else if (type == "float") {
            mType = PropertyType::Float;
        } else if (type == "int") {
            mType = PropertyType::Int;
        } else if (type == "color") {
            mType = PropertyType::Color;
        } else {
            throw std::runtime_error("Property type case is not implemented.");
        }

        if (propertyElement->Attribute("value") == nullptr) {
            throw XmlAttributeException("value");
        }

        mValue = propertyElement->Attribute("value");
    }
}

//  ===========================================================================
bool Property::getBoolValue() const {
    if (mValue == "true") {
        return true;
    } else if (mValue == "false") {
        return false;
    }

    throw std::invalid_argument("Cannot convert string value to boolean.");
}

//  ===========================================================================
bool Property::getBoolValue(const bool defaultValue) const {
    try {
        return this->getBoolValue();
    } catch (const std::exception&) {
        return defaultValue;
    }
}

//  ===========================================================================
double Property::getDoubleValue() const {
    return stod(mValue);
}

//  ===========================================================================
double Property::getDoubleValue(const double defaultValue) const {
    try {
        return this->getDoubleValue();
    } catch (const std::exception&) {
        return defaultValue;
    }
}

//  ===========================================================================
float Property::getFloatValue() const {
    return stof(mValue);
}

//  ===========================================================================
float Property::getFloatValue(const float defaultValue) const {
    try {
        return this->getFloatValue();
    } catch (const std::exception&) {
        return defaultValue;
    }
}

//  ===========================================================================
int Property::getIntValue() const {
    return std::stoi(mValue);
}

//  ===========================================================================
int Property::getIntValue(const int defaultValue) const {
    try {
        return this->getIntValue();
    } catch (const std::exception&) {
        return defaultValue;
    }
}

//  ===========================================================================
const std::string& Property::getName() const {
    return mName;
}

//  ===========================================================================
PropertyType Property::getType() const {
    return mType;
}

//  ===========================================================================
const std::string& Property::getValue() const {
    return mValue;
}

//  ===========================================================================
void Property::queryBoolValue(bool& value) const {
    try {
        value = this->getBoolValue();
    } catch (const std::exception&) {
        return;
    }
}

//  ===========================================================================
void Property::queryBoolValue(bool& value, const bool defaultValue) const {
    try {
        value = this->getBoolValue();
    } catch (const std::exception&) {
        value = defaultValue;
    }
}

//  ===========================================================================
void Property::queryDoubleValue(double& value) const {
    try {
        value = this->getDoubleValue();
    } catch (const std::exception&) {
        return;
    }
}

//  ===========================================================================
void Property::queryDoubleValue(double& value, const double defaultValue) const {
    try {
        value = this->getDoubleValue();
    } catch (const std::exception&) {
        value = defaultValue;
    }
}

//  ===========================================================================
void Property::queryFloatValue(float& value) const {
    try {
        value = this->getFloatValue();
    } catch (const std::exception&) {
        return;
    }
}

//  ===========================================================================
void Property::queryFloatValue(float& value, const float defaultValue) const {
    try {
        value = this->getFloatValue();
    } catch (const std::exception&) {
        value = defaultValue;
    }
}

//  ===========================================================================
void Property::queryIntValue(int& value) const {
    try {
        value = this->getIntValue();
    } catch (const std::exception&) {
        return;
    }
}

//  ===========================================================================
void Property::queryIntValue(int& value, const int defaultValue) const {
    try {
        value = this->getIntValue();
    } catch (const std::exception&) {
        value = defaultValue;
    }
}
}