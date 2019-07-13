#include <robot/util/math/MMath.h>
#include "BallIntakeGeo.h"

namespace SuperstructureMath {

void setElevatorHeight(double height) {
    MMath::addScalar(NULL, height, 3, sizeof(BallGeometry::geo), sizeof(BallGeometry::geo[0]));
}

void setElevatorRotation(double theta) {
    // double rotationTransformation[][] = {
        
    // }
}
}

