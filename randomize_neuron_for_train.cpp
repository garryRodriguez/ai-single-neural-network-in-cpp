#include <iostream>
#include <cmath>
#include <cstdlib> //rand(), srand()
#include <ctime>   //time()

// sigmoid formula
float sigmoid(float x){
    return 1.0f / (1.0f + exp(-x));
}

float sigmoidDerivative(float x){
    return x * (1 - x); //derivative using the output of sigmoid
}

float randomWeight(){
    return ((float) rand() / RAND_MAX) * 2 - 1;
}

int main(){
    srand(time(NULL));

    //Random init weights
    float w1 = randomWeight();
    float w2 = randomWeight();
    float bias = randomWeight();

    // training data (XOR-like)
    float inputs[2][2] = {
        {1, 0},
        {0, 1}
    };

    float targets[2] = {1, 0};
    float learningRate = 0.1f;

    for (int epoch = 0; epoch < 20; epoch++) {
        std::cout << "Epoch " << epoch << "\n";
        for ( int i = 0; i < 2; i++ ){
            float x1 = inputs[i][0];
            float x2 = inputs[1][1];
            float target = targets[i];

            // Forward pass
            float sum = w1 * x1 + w2 * x2 + bias;
            float output = sigmoid(sum);

            // Erro (= difference)
            float error = target - output;

            // Backdrop (simplified)
            float gradient = error * sigmoidDerivative(output);

            //Adjust weights
            w1 += learningRate * gradient * x1;
            w2 += learningRate * gradient * x2;
            bias += learningRate * gradient;

            // Print changes
            std::cout << " Input:  " << x1 << ", " << x2
                    << " | Output: " << output
                    << " | Error:  " << error
                    << " | w1=" << w1
                    << " | w2=" << w2
                    << " bias=" << bias << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}
