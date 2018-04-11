#pragma once

namespace TmxMapLib
{
    const unsigned int FLIPPED_HORIZONTALLY_FLAG    = 0X80000000;
    const unsigned int FLIPPED_VERTICALLY_FLAG      = 0X40000000;
    const unsigned int FLIPPED_DIAGONALLY_FLAG      = 0X20000000;

    //  =======================================================================
    inline bool GetFlipDiagonally(const unsigned int rawGid)
    {
        return rawGid & FLIPPED_DIAGONALLY_FLAG;
    }

    //  =======================================================================
    inline bool GetFlipHorizontally(const unsigned int rawGid)
    {
        return rawGid & FLIPPED_HORIZONTALLY_FLAG;
    }

    //  =======================================================================
    inline bool GetFlipVertically(const unsigned int rawGid)
    {
        return rawGid & FLIPPED_VERTICALLY_FLAG;
    }

    //  =======================================================================
    inline int GetGid(const unsigned int rawGid)
    {
        return
            rawGid & ~(FLIPPED_HORIZONTALLY_FLAG    |
                        FLIPPED_VERTICALLY_FLAG     |
                        FLIPPED_DIAGONALLY_FLAG);
    }
}
