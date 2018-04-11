#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/ImageLayer.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
ImageLayer::ImageLayer(
    const Map* map,
    const int tmxOrder,
    const XMLElement* imageLayerElement)
    : LayerBase(LayerType::Image, map, tmxOrder, imageLayerElement) {
    this->loadImageLayer(imageLayerElement);
}

//  ===========================================================================
const Image& ImageLayer::getImage() const {
    return mImage;
}

//  ===========================================================================
void ImageLayer::loadImageLayer(const XMLElement* imageLayerElement) {
    if (imageLayerElement == nullptr) {
        throw NullArgumentException("imageLayerElement");
    }

    const XMLElement* imageElement = imageLayerElement->FirstChildElement("image");

    if (imageElement == nullptr) {
        throw XmlElementException("image");
    }

    mImage.loadImage(imageElement);
}
}