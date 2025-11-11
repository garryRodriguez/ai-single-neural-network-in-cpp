#include <iostream>
#include <cmath>
using namespace std;

// simple activation (Sigmoid)
float sigmoid(float x){
    return 1.0f / (1.0f + exp(-x));
}

// single neuron: output = sigmoid(w1*x1 + w2*x2 + bias)
float neuron(float x1, float x2){
    float w1 = 0.5f;
    float w2 = -0.7f;
    float bias = 0.1f;

    float sum = w1 * x1 + w2 * x2 + bias;
    return sigmoid(sum);
}

int main(){
    float user_x1, user_x2;

    cout << "Enter first input: ";
    cin >> user_x1;

    cout << "Enter second output: ";
    cin >> user_x2;

    float output = neuron(user_x1, user_x2);
    cout << "Output: " << output << endl;
    return 0;
}