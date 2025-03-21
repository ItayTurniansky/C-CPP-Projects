//Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
    //class that represents a layer of the network with getters and one operator that denses a layer based on the given function.
public:
    Dense(const Matrix& weights, const Matrix& bias, act_func func);
    Matrix get_weights() const;
    Matrix get_bias() const;
    act_func get_activation() const ;
    Matrix& operator()( Matrix& m) const;
private:
    Matrix weights; // weights for the formula
    Matrix bias; // bias matrix for the formula
    act_func activation_function = nullptr; // activation func
};

#endif //DENSE_H
