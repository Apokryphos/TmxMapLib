#ifndef TMXMAPLIB_POINT_HEADER_INCLUDED
#define TMXMAPLIB_POINT_HEADER_INCLUDED

namespace TmxMapLib
{
    class Point
    {
    public:
        double X;
        double Y;

        Point(double x = 0, double y = 0)
            : X(x), Y(y)
        {
        }
    };
}

#endif