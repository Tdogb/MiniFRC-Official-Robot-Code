#include "SuperstructureMath.h"

SuperstructureMath::SuperstructureMath()
{
}

SuperstructureMath::~SuperstructureMath()
{
}

BLA::Matrix<3,3> BallGeometry =
{
    -0.064648f,   0.064648f,  0.064648f,
    0.111350f,   0.060219f,  0.060219f,
    0.012000f,   0.012000f,  0.030242f
};

BLA::Matrix<3,2> FloorGeometry =
{
    -0.075f,  0.075f,
    0.085f, -0.085f,
    0.000f,  0.000f
};

BLA::Matrix<3,3> axisMat = {
    0,        0,       0,
    0.0505,   0.0505,  0.0505,
    0,        0,       0
};

BLA::Matrix<3,1> E1 = {
    1,
    0,
    0
};

BLA::Matrix<3,3> elevatorRotationMat;
BLA::Matrix<3,3> mechanismRotationMat;
BLA::Matrix<3,3> tempMatrix;
BLA::Matrix<3,3> tempMatrix2;
BLA::Matrix<3,1> tempMatrix3;

void SuperstructureMath::setElevatorHeight(float height) {
    for(int i = 0; i < BallGeometry.GetColCount(); i++) {
        BallGeometry(3,i) += height;
    }
}
/*
IMPORTANT: Need to check at multiple time intervals along the path to this location
*/
bool SuperstructureMath::calculateElevatorRotation(float theta) { //Theta is relative here
    float sinT = sinf(theta);
    float cosT = cosf(theta);
    elevatorRotationMat = 
    {
        cosT,  -sinT,   0.f,
        sinT,   cosT,   0.f,
        0.f,     0.f,   1.f
    };

    BLA::Multiply(elevatorRotationMat, BallGeometry, tempMatrix);
    BLA::Multiply(elevatorRotationMat, axisMat, tempMatrix2);
    BLA::Multiply(elevatorRotationMat, E1, tempMatrix3);
    BallGeometry = tempMatrix;
    axisMat = tempMatrix2;
    E1 = tempMatrix3;
    return false;
}

bool SuperstructureMath::calculateMechanismRotation(float theta) {
    float sinT = sinf(theta);
    float cosT = cosf(theta);
    float cosTI = 1- cosT;
    float x = E1(0);
    float y = E1(1);
    float z = E1(2);
    auto D1 = [cosT](float E) -> float { return cosT+pow(E,2)*(1-cosT); };
    auto D2 = [cosTI, sinT](float U1, float U2, float U3) -> float { return U1*U2*cosTI + U3*sinT; };
    mechanismRotationMat = {
        D1(x),        D2(x,y,-z),   D2(x,z,y),
        D2(y,x,z),    D1(y),        D2(y,z,-x),
        D2(z,x,-y),   D2(z,y,x),    D1(z)
    };
    BallGeometry -= axisMat;
    BLA::Multiply(mechanismRotationMat, BallGeometry, tempMatrix);
    tempMatrix += axisMat;
    BallGeometry = tempMatrix;
    printMatrix(&BallGeometry);
}

void SuperstructureMath::printMatrix(BLA::Matrix<3,3> *mat) {
    for(int i = 0; i < mat->GetRowCount(); i++) {
        Serial.println();
        Serial.print("(");
        for(int b = 0; b < mat->GetColCount(); b++) {
            Serial.print((*mat)(b,i),4);
            Serial.print(", ");
        }
        Serial.print(")");
    }
    Serial.println();
}


void detectCollision() {
    for(int i = 0; i < BallGeometry.GetRowCount(); i++) {
    }
}