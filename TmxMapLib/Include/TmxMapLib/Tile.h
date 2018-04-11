#pragma once

namespace TmxMapLib
{
    class Tile
    {
    private:
        unsigned int mRawGid;
        int mX;
        int mY;

    public:

        /*
        *   Constructs a Tile.
        *   The raw GID is the GID before clearing the flip and rotate flags.
        */
        Tile(const unsigned int rawGid, const int x, const int y);

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

        /*
        *   Returns the tile coordinate X component.
        */
        int GetX() const;

        /*
        *   Returns the tile coordinate Y component.
        */
        int GetY() const;
    };
}
