#include <BasicLinearAlgebra.h>
namespace SuperstructureMath {
    BLA::Matrix<3,8> ballGeometry =
    {   
        0.060219,	0.060219,	0.11135,	0.11135,    0.060219,	0.060219,	0.11135,	0.11135,
        0.064648,	0.064648,	0.064648,	0.064648,   -0.064648,	-0.064648,	-0.064648,	-0.064648,
        0.012000,	0.030242, 	0.030242,	0.012000,   0.012000,	0.030242,   0.030242,	0.012000
    };

    BLA::Matrix<3,4> floor =
    {
        -0.075,  +0.075,  +0.075,  -0.075,    
        +0.085,  +0.085,  -0.085,  -0.085,
        0.f,     0.f,     0.f,     0.f
    };
    
    void setElevatorHeight(float height) {
        for(size_t i = 0; i < ballGeometry.Cols; i++) {
            ballGeometry(3,i) += height;
        }
    }
    /*
    IMPORTANT: Need to check at multiple time intervals along the path to this location
    */
    bool calculateRotation(float theta) {
        float sinT = sinf(theta);
        float cosT = cosf(theta);
        BLA::Matrix<3,3> rotationMatrix = 
        {
            cosT,  -sinT,   0.f,
            sinT,   cosT,   0.f,
            0.f,     0.f,   1.f
        };
        BLA::Matrix<3,8> tempMatrix;
        BLA::Multiply(rotationMatrix,ballGeometry,tempMatrix);
        ballGeometry = tempMatrix;

        return false;
    }

}

