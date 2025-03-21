#include "MlpNetwork.h"
#define VECTOR_SIZE 10
MlpNetwork::MlpNetwork(const Matrix weights[MLP_SIZE], const Matrix biases[MLP_SIZE]) : layers{
    Dense(weights[0], biases[0], activation::relu),
    Dense(weights[1], biases[1], activation::relu),
    Dense(weights[2], biases[2], activation::relu),
    Dense(weights[3], biases[3], activation::softmax)
} {}

digit MlpNetwork::operator()(Matrix input)const  {
    input = input.vectorize();
    for (int i=0; i < MLP_SIZE; i++) {
        input = layers[i](input);
    }

    float max_probability = 0;
    unsigned int max_index = 0;

    for (int i = 0; i < VECTOR_SIZE; ++i) {
        if (input[i] > max_probability) {
            max_probability = input[i];
            max_index = i;
        }
    }

    digit result = {max_index, max_probability};
    return result;
}
