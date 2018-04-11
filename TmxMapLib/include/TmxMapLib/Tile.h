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

    bool getFlipDiagonally() const;
    bool getFlipHorizontally() const;
    bool getFlipVertically() const;

    /*
    *   Returns the global ID for this tile.
    */
    int getGid() const;

    /*
    *   Returns the raw global ID for this tile.
    *   The raw GID is the GID before clearing the flip and rotate flags.
    */
    unsigned int getRawGid() const;

    /*
    *   Returns the tile coordinate X component.
    */
    int getX() const;

    /*
    *   Returns the tile coordinate Y component.
    */
    int getY() const;
};
}
