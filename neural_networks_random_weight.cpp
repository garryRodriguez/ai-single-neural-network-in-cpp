#include <iostream>
#include <cmath>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

float randomWeight() {
    // Random number between -1 and +1
    return ((float) rand() / RAND_MAX) * 2 - 1;
}

int main() {
    srand(time(NULL)); // Seed random generator

    float w1 = randomWeight();
    float w2 = randomWeight();
    float bias = randomWeight();

    std::cout << "Random weights:\n";
    std::cout << "w1 = " << w1 << "\n";
    std::cout << "w2 = " << w2 << "\n";
    std::cout << "bias = " << bias << "\n";

    return 0;
}