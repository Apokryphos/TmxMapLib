#ifndef TMXMAPLIB_TILE_HEADER_INCLUDED
#define TMXMAPLIB_TILE_HEADER_INCLUDED

namespace TmxMapLib
{
    class Tile
    {
    private:
        unsigned int mRawGid;

    public:

        /*
        *   Constructs a Tile.
        *   The raw GID is the GID before clearing the flip and rotate flags.
        */
        Tile(const unsigned int rawGid);

        bool GetFlipDiagonally() const;
        bool GetFlipHorizontally() const;
        bool GetFlipVertically() const;

        /*
        *   Returns the global ID for this tile.
        */
        int GetGid() const;

        /*
        *   Returns the raw global ID for this tile.
        *   The raw GID is the GID before clearing the flip and rotate flags.
        */
        unsigned int GetRawGid() const;
    };
}

#endif