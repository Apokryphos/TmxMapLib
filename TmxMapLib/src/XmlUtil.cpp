#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
int countElements(const XMLElement* parent, const char* name) {
    int count = 0;
    const XMLElement* element = parent->FirstChildElement(name);
    while (element != nullptr) {
        ++count;
        element = element->NextSiblingElement(name);
    }

    return count;
}
}