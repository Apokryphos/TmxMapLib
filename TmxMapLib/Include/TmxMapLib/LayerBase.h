#ifndef TMXMAPLIB_LAYER_BASE_HEADER_INCLUDED
#define TMXMAPLIB_LAYER_BASE_HEADER_INCLUDED

#include "PropertySet.h"
#include <string>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    enum class LayerType
    {
        Tile,
        Object,
        Image,
    };

    class LayerBase
    {
    private:
        int mTmxOrder;
        LayerType mLayerType;
        double mOpacity;
        bool mVisible;
        std::string mName;
        PropertySet mProperties;

        friend class TmxMap;

        void LoadLayer(const tinyxml2::XMLElement* layerElement);

    public:

        /*
        *   Constructs a LayerBase.
        */
        LayerBase(const LayerType layerType);

        /*
        *   Constructs a LayerBase.
        */
        LayerBase(
            const LayerType layerType,
            const int tmxOrder,
            const tinyxml2::XMLElement* layerElement);

        /*
        *   Returns the layer type of this layer.
        */
        LayerType GetLayerType() const;

        /*
        *   Returns the name of this layer.
        */
        const std::string& GetName() const;

        /*
        *   Returns the layer opacity as a value from zero to one.
        */
        double GetOpacity() const;

        /*
        *   Returns the set of properties for this layer.
        */
        const PropertySet& GetPropertySet() const;

        /*
        *   The order this layer appears in the TMX file.
        *   (i.e. the same order they are rendered in Tiled).
        */
        int GetTmxOrder() const;

        /*
        *   Returns whether the layer is shown or hidden.
        */
        bool GetVisible() const;
    };
}

#endif