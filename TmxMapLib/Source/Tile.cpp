#include "TmxMapLib/GidUtil.h"
#include "TmxMapLib/Tile.h"

namespace TmxMapLib
{
    //  =======================================================================
    Tile::Tile(const unsigned int rawGid, const int x, const int y)
    :   mRawGid(rawGid),
        mX(x),
        mY(y)
    {
    }

    //  =======================================================================
    bool Tile::GetFlipDiagonally() const
    {
        return TmxMapLib::GetFlipDiagonally(mRawGid);
    }

    //  =======================================================================
    bool Tile::GetFlipHorizontally() const
    {
        return TmxMapLib::GetFlipHorizontally(mRawGid);
    }

    //  =======================================================================
    bool Tile::GetFlipVertically() const
    {
        return TmxMapLib::GetFlipVertically(mRawGid);
    }

    //  =======================================================================
    int Tile::GetGid() const
    {
        return TmxMapLib::GetGid(mRawGid);
    }

    //  =======================================================================
    unsigned int Tile::GetRawGid() const
    {
        return mRawGid;
    }

    //  =======================================================================
    int Tile::GetX() const
    {
        return mX;
    }

    //  =======================================================================
    int Tile::GetY() const
    {
        return mY;
    }
}