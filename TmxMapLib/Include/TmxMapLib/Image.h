#pragma once

#include <string>

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
class Image
{
private:
    int mWidth;
    int mHeight;
    std::string mSource;

    //  Friend classes that need to call LoadImage
    friend class ImageLayer;
    friend class Tileset;

    /*
    *   Loads image from XML element.
    */
    void loadImage(const tinyxml2::XMLElement* imageElement);

public:
    /*
    *   Constructs an empty image.
    */
    Image();

    /*
    *   Constructs an image from an XML element.
    */
    Image(const tinyxml2::XMLElement* imageElement);

    /*
    *   Returns the height of this image in pixels.
    */
    int getHeight() const;

    /*
    *   Returns the width of this image in pixels.
    */
    int getWidth() const;

    /*
    *   Returns the source filename of this image.
    */
    const std::string& getSource() const;
};
}
