#pragma once

namespace TmxMapLib
{
class Point
{
public:
    double X;
    double Y;

    Point(double x = 0, double y = 0)
        : X(x), Y(y) {
    }
};
}
