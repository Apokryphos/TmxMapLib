#pragma once

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
//  ===========================================================================
int countElements(const tinyxml2::XMLElement* parent, const char* name);
}