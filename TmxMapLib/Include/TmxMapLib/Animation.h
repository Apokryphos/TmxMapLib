#pragma once

#include "Frame.h"
#include <vector>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class Animation
    {
    private:
        std::vector<Frame> mFrames;

        //  Friend classes that need to call LoadAnimation
        friend class TilesetTile;

        /*
        *   Loads animation from XML element.
        */
        void LoadAnimation(const tinyxml2::XMLElement* animElement);

    public:

        /*
        *   Constructs an empty Animation.
        */
        Animation();

        /*
        *   Returns the frame at the specified index.
        *   Throws an out_of_range exception if the index is invalid.
        */
        const Frame& GetFrame(int index) const;

        /*
        *   Returns the number of frames in this animation.
        */
        int GetFrameCount() const;

        /*
        *   Returns all of the frames in this animation.
        */
        const std::vector<Frame>& GetFrames() const;
    };
}
