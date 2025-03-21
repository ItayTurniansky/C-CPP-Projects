// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
typedef Matrix (*act_func)(Matrix);
namespace activation {
    //activation function to use in the dense class.
    Matrix relu( Matrix x); // does ReLu to a matrix if value is less than 0 then it changes to zero
    Matrix softmax( Matrix x); // does softmax to a matrix-calculated with exp.
}
#endif //ACTIVATION_H
