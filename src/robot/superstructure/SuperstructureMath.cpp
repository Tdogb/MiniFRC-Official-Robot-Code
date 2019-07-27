#include "SuperstructureMath.hpp"

SuperstructureMath::SuperstructureMath()
{
}

SuperstructureMath::~SuperstructureMath()
{
}

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
    return true;
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

/*
detectCollision should be same formula as hitbox detection in video games
if the dot product of each?
*/
bool SuperstructureMath::detectCollision() {
    bool collisionHappened[] = {false,false};
    if(BallGeometry(2,0) + BallGeometry(2,1) + BallGeometry(2,2) <= 0) {
        //No collision
        return false;
    }
    else {
        for(int i = 0; i < 2; i++) { //Test x and y
            for(int b = 0; b < 2; b++) {
                if(contains(BallGeometry(i,0), BallGeometry(i,1), FloorGeometry(i,b))) {
                    collisionHappened[i] = true;
                }
            }
        }
    }
    return collisionHappened[0] && collisionHappened[1];
}

bool SuperstructureMath::contains(const float &n0, const float &n1, const float &n2) {
    return n2 >= (n0 > n1 ? n1 : n0) && n2 <= (n0 > n1 ? n0 : n1);
}