#include "PathGenerator.h"
//#include "Path.h"


PathGenerator::PathGenerator(std::vector<Matrix<2,1>> &_pathPoints, std::vector<Matrix<2,1>> &_pathTangents)
:pathPoints(_pathPoints),pathTangents(_pathTangents)
{
    generate();
}

PathGenerator::~PathGenerator()
{

}
/*
{x,y,t,t}
*/
void PathGenerator::generate() {
    for(size_t i = 0; i < pathPoints.size() - 1; i++) {
        splines.push_back({pathPoints[i], pathPoints[i+1], pathTangents[i], pathPoints[i+1]});
        //splines.push_back({{pathPoints[i](0)&&pathPoints[i](1)},{pathPoints[i+1](0)&&pathPoints[i+1](1)},{pathPoints[i](2)&&pathPoints[i](3)},{pathPoints[i+1](2)&&pathPoints[i+1](3)}});
    }
}
