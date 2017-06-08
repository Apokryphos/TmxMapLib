#ifndef TMXMAPLIB_FRAME_HEADER_INCLUDED
#define TMXMAPLIB_FRAME_HEADER_INCLUDED

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    class Frame
    {
    private:
        int mTileId;
        int mDuration;

        /*
        *   Loads frame from XML element.
        */
        void LoadFrame(const tinyxml2::XMLElement* frameElement);

    public:

        /*
        *   Constructs a frame from an XML element.
        */
        Frame(const tinyxml2::XMLElement* frameElement);

        /*
        *   Returns the frame duration in milliseconds.
        */
        int GetDuration() const;

        /*
        *   Returns the local ID of the frame tile within its parent tileset.
        */
        int GetTileId() const;
    };
}

#endif