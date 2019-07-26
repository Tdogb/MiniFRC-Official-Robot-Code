#ifndef __PATHGENERATOR_H__
#define __PATHGENERATOR_H__
#include <vector>
#include "Spline.h"
#include <cstddef>
#include <BasicLinearAlgebra.h>

using namespace BLA;

#define PATHGEN_MAT_COLS 2

class PathGenerator
{
private:
    // std::vector<Point> path = {
    //     {0,0,1,0},
    //     {1,1,0.5,0.5},
    //     {2,3,1,0}
    // };
    std::vector<Matrix<2,1>> &pathPoints;
    std::vector<Matrix<2,1>> &pathTangents;
    std::vector<Spline> splines;
public:
    PathGenerator(std::vector<Matrix<2,1>> &_pathPoints, std::vector<Matrix<2,1>> &_pathTangents);
    ~PathGenerator();
    void generate();
};


#endif // __PATHGENERATOR_H__
