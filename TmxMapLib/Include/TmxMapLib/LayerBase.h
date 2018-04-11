#pragma once

#include "PropertySet.h"
#include <string>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class Map;

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
        const Map* mMap;

        friend class Map;

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
            const Map* map,
            const int tmxOrder,
            const tinyxml2::XMLElement* layerElement);

        /*
        *   Returns the layer type of this layer.
        */
        LayerType GetLayerType() const;

        /*
        *   Returns the map that owns this layer.
        */
        const Map* GetMap() const;

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
