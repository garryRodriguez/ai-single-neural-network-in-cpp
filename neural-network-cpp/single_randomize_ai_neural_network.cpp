#include <iostream>
#include <cmath>
#include <cstdlib> //srand(), rand()
#include <ctime>
using namespace std;

//sigmoid activation
float sigmoid(float x){
    return 1.0f / (1.0f + exp(-x));
}

//neuron output
float neuron(float x1, float x2, float w1, float w2, float bias){
    float sum = w1 * x1  + w2 * x2 + bias;
    return sigmoid(sum);
}

int main(){
    //seed random time generator
    srand(time(0));

    //random weights and bias initialization (-0.5 to 0.5)
    float w1 = ((float)rand() / RAND_MAX) - 0.5f;
    float w2 = ((float)rand() / RAND_MAX) - 0.5f;
    float bias = ((float)rand() / RAND_MAX) - 0.5f;

    float learning_rate = 0.1f;
    float error_threshold = 0.01f; //Stop when total error is small enough

    //Base training data (x1, x2, target)
    vector<vector<float>> data = {
        {1, 1, 1},  //Target = 1
        {0, 1, 0}   //Target = 0
    };

    int epoch = 0; // initialize epoch to zero (epoch means one full round of the training)

    while (true)
    {
        float total_error = 0.0f;

        /**
         * For loop -- modern style available in c++11
         *  This loops over the training sample data in line 31
         * Instead of using the origina training data, the ( for (auto &sample : data) ) uses
         * the data already in the memory, thus making it very fast
         * 
         * Note: The & means -- reference only. The meaning of that in this context is
         * we are using the original training data element in memory,thus making it very fast
         * 
         * The : (range-based for loop) --- “For each sample inside data…”
         * 
         * Shorter and safer way than : for (int i = 0; i < data.size(); i++) {
                vector<float> &sample = data[i];
            }
         */
        for (auto &sample : data)
        {
            float base_x1 = sample[0]; //input #1
            float base_x2 = sample[1]; //input #2
            float target = sample[2];  //expected (target output)

            //Randomize inputs slightly for each epoch

            //How much variation
            //This control how much "random wiggle" we'll allow on the input values
            float noise_factor = 0.1f;

            //Create the noisy versions
            //Step 1: (float)rand() / RAND_MAX → gives a random number between 0.0 and 1.0.
            //Step 2: * 2 * noise_factor → scales it to a range between 0.0 and 0.2 (because noise_factor = 0.1).
            //Step 3: - noise_factor → shifts it down by 0.1, so now the range is -0.1 to +0.1.
            //Step 4: base_x1 + (...) → adds that random offset to the original input.
            
            // So if base_x1 = 1:
            // one time it could become 1.07
            // another time it could be 0.93
            // another time 1.02
            // That’s how we simulate imperfect, real-world input data — small variations each epoch.

            float x1 = base_x1 + (((float)rand() / RAND_MAX) * 2 * noise_factor - noise_factor);
            float x2 = base_x2 + (((float)rand() / RAND_MAX) * 2 * noise_factor - noise_factor);

            //Run the neuron
            //This calculates the neuron’s output using the current weights and bias.
            float output = neuron(x1, x2, w1, w2, bias);

            //Compute the error
            //This measures how wrong the neuron’s prediction was.

            //Example:
            //If the target is 1
            //and the output was 0.8
            //then the error is 0.2
            //If the target is 0 and the output was 0.3, the error is -0.3.
            //The sign (positive or negative) tells whether the output is too high or too low.
            float error = target - output;


            //Add to total error
            //fabs() = floating-point absolute value
            //→ it removes the negative sign, so we just measure how big the mistake was.
            //This way, we can sum up all errors (no matter if positive or negative) and later check:
            // “Is the total error small enough to stop training?”
            total_error += fabs(error); //Returns the absolute value of a floating-point number

            //Update weights and bias
            w1 += learning_rate * error * x1; // same as w1 = w1 + learning_rate * error * x1
            w2 += learning_rate * error * x2; // same as w2 = w2 + learning_rate * error * x2
            bias += learning_rate * error;

            cout << "Input: " << x1 << ", " << x2
                 << "| Output: " << output
                 << "| Error: " << error
                 << "| w1= " << w1
                 << "| w2= " << w2
                 << "| bias= " << bias << endl;
        }   

        epoch++; //increment epoch for each training round
        cout << "Epoch " << epoch << "total error: " << total_error << endl;

        //stop if total error is below threshold
        if (total_error < error_threshold)
        {
            cout << "Training complete!" << endl;
            break;
        }
    }

    cout << "Final weights: w1=" << w1 << " w2=" << w2 << " bias " << endl;

    return 0;
}