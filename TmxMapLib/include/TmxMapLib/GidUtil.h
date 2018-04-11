#pragma once

namespace TmxMapLib
{
const unsigned int FLIPPED_HORIZONTALLY_FLAG    = 0X80000000;
const unsigned int FLIPPED_VERTICALLY_FLAG      = 0X40000000;
const unsigned int FLIPPED_DIAGONALLY_FLAG      = 0X20000000;

//  ===============================================================================
inline bool getFlipDiagonally(const unsigned int rawGid) {
    return rawGid & FLIPPED_DIAGONALLY_FLAG;
}

//  ===============================================================================
inline bool getFlipHorizontally(const unsigned int rawGid) {
    return rawGid & FLIPPED_HORIZONTALLY_FLAG;
}

//  ===============================================================================
inline bool getFlipVertically(const unsigned int rawGid) {
    return rawGid & FLIPPED_VERTICALLY_FLAG;
}

//  ===============================================================================
inline int getGid(const unsigned int rawGid) {
    return
        rawGid & ~(FLIPPED_HORIZONTALLY_FLAG    |
                    FLIPPED_VERTICALLY_FLAG     |
                    FLIPPED_DIAGONALLY_FLAG);
}
}
