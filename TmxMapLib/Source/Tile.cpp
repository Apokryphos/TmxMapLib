#include "TmxMapLib/GidUtil.h"
#include "TmxMapLib/Tile.h"

namespace TmxMapLib
{
//  ===========================================================================
Tile::Tile(const unsigned int rawGid, const int x, const int y)
:   mRawGid(rawGid),
    mX(x),
    mY(y) {
}

//  ===========================================================================
bool Tile::getFlipDiagonally() const {
    return TmxMapLib::getFlipDiagonally(mRawGid);
}

//  ===========================================================================
bool Tile::getFlipHorizontally() const {
    return TmxMapLib::getFlipHorizontally(mRawGid);
}

//  ===========================================================================
bool Tile::getFlipVertically() const {
    return TmxMapLib::getFlipVertically(mRawGid);
}

//  ===========================================================================
int Tile::getGid() const {
    return TmxMapLib::getGid(mRawGid);
}

//  ===========================================================================
unsigned int Tile::getRawGid() const {
    return mRawGid;
}

//  ===========================================================================
int Tile::getX() const {
    return mX;
}

//  ===========================================================================
int Tile::getY() const {
    return mY;
}
}