#include "PathGenerator.h"
#include "Path.h"


PathGenerator::PathGenerator(/* args */)
{
}

PathGenerator::~PathGenerator()
{
}

void PathGenerator::generate() {
    for(size_t i = 0; i < path.size() - 1; i++) {
        splines.push_back({path[i].position,path[i+1].position, path[i].tangent, path[i+1].tangent});
    }
}
