#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int PatternCount = 10;
const int InputNodes = 7;
const int HiddenNodes = 8;
const int OutputNodes = 4;
const float LearningRate = 0.0001;   // Reduced learning rate for smoother convergence
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.00001;
const int MaxTrainingCycles = 1000000;  // Safety limit on training cycles

const int Input[PatternCount][InputNodes] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {0, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 0, 0, 1, 1}   // 9
};

const int Target[PatternCount][OutputNodes] = {
    {0, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 1}
};

float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes + 1][HiddenNodes];
float OutputWeights[HiddenNodes + 1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes + 1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes + 1][OutputNodes];

float Error;
int RandomizedIndex[PatternCount];

void initializeWeights() {
    for (int i = 0; i < HiddenNodes; ++i) {
        for (int j = 0; j <= InputNodes; ++j) {
            HiddenWeights[j][i] = 2.0 * (float(rand()) / RAND_MAX - 0.5) * InitialWeightMax;
            ChangeHiddenWeights[j][i] = 0.0;
        }
    }
    
    for (int i = 0; i < OutputNodes; ++i) {
        for (int j = 0; j <= HiddenNodes; ++j) {
            OutputWeights[j][i] = 2.0 * (float(rand()) / RAND_MAX - 0.5) * InitialWeightMax;
            ChangeOutputWeights[j][i] = 0.0;
        }
    }
}

void feedForward(int p) {
    for (int i = 0; i < HiddenNodes; ++i) {
        float sum = HiddenWeights[InputNodes][i];  // Bias term
        for (int j = 0; j < InputNodes; ++j) {
            sum += Input[p][j] * HiddenWeights[j][i];
        }
        Hidden[i] = std::max(0.0f, sum);  // ReLU
    }

    for (int i = 0; i < OutputNodes; ++i) {
        float sum = OutputWeights[HiddenNodes][i];  // Bias term
        for (int j = 0; j < HiddenNodes; ++j) {
            sum += Hidden[j] * OutputWeights[j][i];
        }
        Output[i] = std::max(0.0f, sum);  // ReLU
    }
}

void backpropagate(int p) {
    Error = 0.0;

    // Compute output layer deltas
    for (int i = 0; i < OutputNodes; ++i) {
        float delta = Target[p][i] - Output[i];
        OutputDelta[i] = delta;
        Error += delta * delta;
    }
    Error *= 0.5;

    // Compute hidden layer deltas
    for (int i = 0; i < HiddenNodes; ++i) {
        float sum = 0.0;
        for (int j = 0; j < OutputNodes; ++j) {
            sum += OutputWeights[i][j] * OutputDelta[j];
        }
        HiddenDelta[i] = (Hidden[i] > 0 ? sum : 0.0);  // ReLU derivative
    }

    // Update weights for hidden-to-output
    for (int i = 0; i < OutputNodes; ++i) {
        ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i];
        OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i];  // Update bias
        for (int j = 0; j < HiddenNodes; ++j) {
            ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i];
            OutputWeights[j][i] += ChangeOutputWeights[j][i];
        }
    }

    // Update weights for input-to-hidden
    for (int i = 0; i < HiddenNodes; ++i) {
        ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i];
        HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i];  // Update bias
        for (int j = 0; j < InputNodes; ++j) {
            ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
            HiddenWeights[j][i] += ChangeHiddenWeights[j][i];
        }
    }
}

void train() {
    for (int cycle = 0; cycle < MaxTrainingCycles; ++cycle) {
        // Randomize the order of patterns
        for (int p = 0; p < PatternCount; ++p) {
            int q = rand() % PatternCount;
            std::swap(RandomizedIndex[p], RandomizedIndex[q]);
        }

        Error = 0.0;

        for (int q = 0; q < PatternCount; ++q) {
            int p = RandomizedIndex[q];
            feedForward(p);
            backpropagate(p);
        }

        if (cycle % 1000 == 0) {
            std::cout << "Cycle " << cycle << ": Error = " << Error << std::endl;
        }

        if (Error < Success) {
            std::cout << "Training complete. Error: " << Error << std::endl;
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for randomness

    // Initialize training pattern index
    for (int i = 0; i < PatternCount; ++i) {
        RandomizedIndex[i] = i;
    }

    initializeWeights();
    train();
    return 0;
}
