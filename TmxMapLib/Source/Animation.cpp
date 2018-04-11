#include "TmxMapLib/Animation.h"
#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
Animation::Animation() {}

//  ===========================================================================
const Frame& Animation::getFrame(int index) const {
    return mFrames.at(index);
}

//  ===========================================================================
int Animation::getFrameCount() const {
    return mFrames.size();
}

//  ===========================================================================
const std::vector<Frame>& Animation::getFrames() const {
    return mFrames;
}

//  ===========================================================================
void Animation::loadAnimation(const XMLElement* animElement) {
    if (animElement == nullptr) {
        throw NullArgumentException("animElement");
    }

    int frameCount = countElements(animElement, "frame");
    mFrames.reserve(frameCount);

    const XMLElement* frameElement = animElement->FirstChildElement("frame");
    while (frameElement != nullptr) {
        mFrames.emplace_back(frameElement);

        frameElement = frameElement->NextSiblingElement("frame");
    }
}
}