#ifndef __PATHGENERATOR_H__
#define __PATHGENERATOR_H__
#include <vector>
#include "Spline.h"
#include <cstddef>
#include "robot/autonomous/Vector2D.h"

class PathGenerator
{
private:
    struct Point
    {
        Vector2D position;
        Vector2D tangent;
    };
    // std::vector<Point> path = {
    //     {0,0,1,0},
    //     {1,1,0.5,0.5},
    //     {2,3,1,0}
    // };
    std::vector<Spline> splines;
public:
    PathGenerator(/* args */);
    ~PathGenerator();
    void generate();
};


#endif // __PATHGENERATOR_H__
