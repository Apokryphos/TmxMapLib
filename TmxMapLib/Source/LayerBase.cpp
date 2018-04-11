#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/LayerBase.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
LayerBase::LayerBase(const LayerType layerType)
    :
        mTmxOrder(0),
        mLayerType(layerType),
        mOpacity(1),
        mVisible(true),
        mMap(nullptr) {
}

//  ===========================================================================
LayerBase::LayerBase(
    const LayerType layerType,
    const Map* map,
    const int tmxOrder,
    const XMLElement* layerElement)
    :
        mTmxOrder(tmxOrder),
        mLayerType(layerType),
        mOpacity(1),
        mVisible(true),
        mMap(map) {
    this->loadLayer(layerElement);
}

//  ===========================================================================
LayerType LayerBase::getLayerType() const {
    return mLayerType;
}

//  ===========================================================================
const Map* LayerBase::getMap() const {
    return mMap;
}

//  ===========================================================================
const std::string& LayerBase::getName() const {
    return mName;
}

//  ===========================================================================
double LayerBase::getOpacity() const {
    return mOpacity;
}

//  ===========================================================================
const PropertySet& LayerBase::getPropertySet() const {
    return mProperties;
}

//  ===========================================================================
int LayerBase::getTmxOrder() const {
    return mTmxOrder;
}

//  ===========================================================================
bool LayerBase::getVisible() const {
    return mVisible;
}

//  ===========================================================================
void LayerBase::loadLayer(const XMLElement* layerElement) {
    if (layerElement == nullptr) {
        throw NullArgumentException("layerElement");
    }

    if (layerElement->Attribute("name")) {
        mName = layerElement->Attribute("name");
    }

    layerElement->QueryDoubleAttribute("opacity", &mOpacity);
    layerElement->QueryBoolAttribute("visible", &mVisible);

    if (layerElement->FirstChildElement("properties")) {
        mProperties.loadProperties(layerElement->FirstChildElement("properties"));
    }
}
}