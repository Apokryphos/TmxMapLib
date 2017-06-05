#ifndef TMXMAPLIB_IMAGE_LAYER_HEADER_INCLUDED
#define TMXMAPLIB_IMAGE_LAYER_HEADER_INCLUDED

#include "Image.h"
#include "LayerBase.h"
#include <vector>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class ImageLayer : public LayerBase
    {
    private:
        Image mImage;

        void LoadImageLayer(const tinyxml2::XMLElement* imageLayerElement);

    public:

        /*
        *   Constructs an ImageLayer from the specified XML element.
        */
        ImageLayer(const int tmxOrder, const tinyxml2::XMLElement* layerElement);

        /*
        *   Returns the image for this layer.
        */
        const Image& GetImage() const;
    };
}

#endif