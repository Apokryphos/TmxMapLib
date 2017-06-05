#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/LayerBase.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    LayerBase::LayerBase(const LayerType layerType)
        :   mLayerType(layerType),
            mTmxOrder(0),
            mOpacity(1),
            mVisible(true)
    {
    }

    //  =======================================================================
    LayerBase::LayerBase(
        const LayerType layerType,
        const int tmxOrder,
        const XMLElement* layerElement)
        :
            mLayerType(layerType),
            mTmxOrder(tmxOrder),
            mOpacity(1),
            mVisible(true)
    {
        LoadLayer(layerElement);
    }

    //  =======================================================================
    LayerType LayerBase:: GetLayerType() const
    {
        return mLayerType;
    }

    //  =======================================================================
    const std::string& LayerBase::GetName() const
    {
        return mName;
    }

    //  =======================================================================
    double LayerBase::GetOpacity() const
    {
        return mOpacity;
    }

    //  =======================================================================
    const PropertySet& LayerBase::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    int LayerBase::GetTmxOrder() const
    {
        return mTmxOrder;
    }

    //  =======================================================================
    void LayerBase::LoadLayer(const XMLElement* layerElement)
    {
        if (layerElement == nullptr)
        {
            throw NullArgumentException("layerElement");
        }

        if (layerElement->Attribute("name"))
        {
            mName = layerElement->Attribute("name");
        }

        layerElement->QueryDoubleAttribute("opacity", &mOpacity);
        layerElement->QueryBoolAttribute("visible", &mVisible);

        if (layerElement->FirstChildElement("properties"))
        {
            mProperties.LoadProperties(layerElement->FirstChildElement("properties"));
        }
    }

    //  =======================================================================
    bool LayerBase::GetVisible() const
    {
        return mVisible;
    }
}