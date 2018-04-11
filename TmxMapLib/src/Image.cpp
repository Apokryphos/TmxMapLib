#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Image.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
Image::Image() {}

//  ===========================================================================
Image::Image(const tinyxml2::XMLElement* imageElement) {
    this->loadImage(imageElement);
}

//  ===========================================================================
int Image::getHeight() const {
    return mHeight;
}

//  ===========================================================================
int Image::getWidth() const {
    return mWidth;
}

//  ===========================================================================
const std::string& Image::getSource() const {
    return mSource;
}

//  ===========================================================================
void Image::loadImage(const XMLElement* imageElement) {
    if (imageElement == nullptr) {
        throw NullArgumentException("imageElement");
    }

    if (imageElement->Attribute("source")) {
        mSource = imageElement->Attribute("source");
    } else {
        throw XmlAttributeException("source");
    }

    if (imageElement->QueryIntAttribute("width", &mWidth) != XML_SUCCESS) {
        throw XmlAttributeException("width");
    }

    if (imageElement->QueryIntAttribute("height", &mHeight) != XML_SUCCESS) {
        throw XmlAttributeException("height");
    }
}
}