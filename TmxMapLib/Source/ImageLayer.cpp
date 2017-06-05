#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/ImageLayer.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    ImageLayer::ImageLayer(const int tmxOrder, const XMLElement* imageLayerElement)
        : LayerBase(LayerType::Image, tmxOrder, imageLayerElement)
    {
        LoadImageLayer(imageLayerElement);
    }

    //  =======================================================================
    const Image& ImageLayer::GetImage() const
    {
        return mImage;
    }

    //  =======================================================================
    void ImageLayer::LoadImageLayer(const XMLElement* imageLayerElement)
    {
        if (imageLayerElement == nullptr)
        {
            throw NullArgumentException("imageLayerElement");
        }

        const XMLElement* imageElement = imageLayerElement->FirstChildElement("image");

        if (imageElement == nullptr)
        {
            throw XmlElementException("image");
        }

        mImage.LoadImage(imageElement);
    }
}