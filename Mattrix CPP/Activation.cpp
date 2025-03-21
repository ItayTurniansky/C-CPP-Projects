#include <cmath>
#include "Activation.h"

Matrix activation::softmax(Matrix x) {
        float sum = 0;
        for (int i = 0; i < x.get_rows()* x.get_cols(); ++i) {
            sum += std::exp(x[i]);
        }
        for (int j = 0; j < x.get_cols()*x.get_rows(); ++j) {
            x[j] = std::exp(x[j]) / sum;
            }
        return x;
}

Matrix activation::relu(Matrix x) {
        for (int i = 0; i < x.get_rows()*x.get_cols(); ++i) {
         if (x[i]<0) {
             x[i]=0;
         }
        }
        return x;
}
