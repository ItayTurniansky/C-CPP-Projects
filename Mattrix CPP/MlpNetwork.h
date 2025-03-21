// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit { //digit struct
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28}; //default layers
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

class MlpNetwork {
public:
	MlpNetwork(const Matrix weights[MLP_SIZE], const Matrix biases[MLP_SIZE]); //constructor with two arrays of 4X4 matrices.
	digit operator()(Matrix input)const ;
private:
	Dense layers[MLP_SIZE]; //layers array for neuron network.
};

#endif // MLPNETWORK_H