//#include <BasicLinearAlgebra.h>
#include <Eigen.h>

using namespace Eigen;

MatrixXf ballGeometry(3,3);
MatrixXf floorGeometry(3,2);

void init() {
    ballGeometry << -0.064648f,   0.064648f,  0.064648f,
                    0.111350f,   0.060219f,  0.060219f,
                    0.012000f,   0.012000f,  0.030242f;
    floorGeometry << -0.075f,  0.075f,
                      0.085f, -0.085f,
                      0.000f,  0.000f;
}

bool calculateElevatorRotation(float theta) {
    float sinT = sinf(theta);
    float cosT = cosf(theta);

    MatrixXf rotationMatrix(3,3);
    rotationMatrix <<   cosT,  -sinT,   0.f,
                        sinT,   cosT,   0.f,
                        0.f,     0.f,   1.f;
    ballGeometry = rotationMatrix * ballGeometry;

    return false;
}

// namespace SuperstructureMath {
//     BLA::Matrix<3,8> ballGeometry =
//     {   
//         0.064648f,	0.064648f,	0.064648f,	0.064648f,   -0.064648f,	-0.064648f,	-0.064648f,	-0.064648f, /* x */
//         0.060219f,	0.060219f,	0.11135f,	0.11135f,    0.060219f,	    0.060219f,	0.11135f,	0.11135f, /* y */
//         0.012000f,	0.030242f, 	0.030242f,	0.012000f,   0.012000f,	    0.030242f,   0.030242f,	0.012000f /* z */
//     };

//     BLA::Matrix<3,3> fastBallGeometry =
//     {
//         -0.064648f,   0.064648f,  0.064648f,
//          0.111350f,   0.060219f,  0.060219f,
//          0.012000f,   0.012000f,  0.030242f
//     };

//     BLA::Matrix<3,2> FloorGeometry =
//     {
//         -0.075f,  0.075f,
//          0.085f, -0.085f,
//          0.000f,  0.000f
//     };
    
//     void setElevatorHeight(float height) {
//         for(size_t i = 0; i < fastBallGeometry.GetColCount(); i++) {
//             fastBallGeometry(3,i) += height;
//         }
//     }
//     /*
//     IMPORTANT: Need to check at multiple time intervals along the path to this location
//     */
//     bool calculateElevatorRotation(float theta) { //Theta is relative here
//         float sinT = sinf(theta);
//         float cosT = cosf(theta);
//         BLA::Matrix<3,3> rotationMatrix = 
//         {
//             cosT,  -sinT,   0.f,
//             sinT,   cosT,   0.f,
//             0.f,     0.f,   1.f
//         };
//         BLA::Matrix<3,3> tempMatrix;
//         BLA::Multiply(rotationMatrix,fastBallGeometry,tempMatrix);
//         fastBallGeometry = tempMatrix;

//         return false;
//     }

//     bool calculateMechanismRotation(float theta) {

//     }

//     void detectCollision() {
//         for(size_t i = 0; i < fastBallGeometry.GetRowCount(); i++) {

//         }
//     }

// }

