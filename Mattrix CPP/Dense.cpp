#include "Dense.h"

Dense::Dense(const Matrix& weights, const Matrix& bias, act_func function):
weights{weights}, bias{bias}, activation_function{function} {}

act_func Dense::get_activation() const{
    return activation_function;
}

Matrix Dense::get_weights() const{
    return weights;
}

Matrix Dense::get_bias() const{
    return bias;
}

Matrix& Dense::operator()(Matrix& m)  const{
    m = weights * m;
    m += bias;
    m = activation_function(m);
    return m;
}
