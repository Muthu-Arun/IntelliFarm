#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
static int PatternCount;
static int InputNodes ;
static int HiddenNodes ;
static int OutputNodes ;
static const double LearningRate = 0.0001;   // Reduced learning rate for smoother convergence
static const double Momentum = 0.9;
static const double InitialWeightMax = 0.5;
static const double Success = 0.00001;
static const int MaxTrainingCycles = 1000000;  // Safety limit on training cycles


// static void loadTrainingData();
void getDataset(std::vector<std::vector<double>>& _input,std::vector<std::vector<double>>& _target );
void saveWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output);
void loadWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output);
static std::vector<std::vector<double>> Input;

static std::vector<std::vector<double>> Target;
static double max(double x){
    if(x >= 0)
        return x;
    else
        return 0;
}

static std::vector<double> Hidden;
static std::vector<double> Output;
static std::vector<std::vector<double>> HiddenWeights;
static std::vector<std::vector<double>> OutputWeights;
static std::vector<double> HiddenDelta;
static std::vector<double> OutputDelta;
static std::vector<std::vector<double>> ChangeHiddenWeights;
static std::vector<std::vector<double>> ChangeOutputWeights;
static std::vector<double> RandomizedIndex;
// double Hidden[HiddenNodes];
// double Output[OutputNodes];
// double HiddenWeights[InputNodes + 1][HiddenNodes];
// double OutputWeights[HiddenNodes + 1][OutputNodes];
// double HiddenDelta[HiddenNodes];
// double OutputDelta[OutputNodes];
// double ChangeHiddenWeights[InputNodes + 1][HiddenNodes];
// double ChangeOutputWeights[HiddenNodes + 1][OutputNodes];

static double Error;

static void initializeParameters(){
    PatternCount = Input.size();
    InputNodes = Input[0].size();
    HiddenNodes = InputNodes+1;
    OutputNodes = Target[0].size();

}
// int RandomizedIndex[PatternCount];
static void initializeVectors(){
    Input.resize(PatternCount, std::vector<double>(InputNodes));
    Target.resize(PatternCount, std::vector<double>(OutputNodes));
  Hidden.resize(HiddenNodes);
  Output.resize(OutputNodes);
  HiddenWeights.resize(InputNodes + 1,std::vector<double>(HiddenNodes));
  OutputWeights.resize(HiddenNodes + 1,std::vector<double>(OutputNodes));
  HiddenDelta.resize(HiddenNodes);
  OutputDelta.resize(OutputNodes);
  ChangeHiddenWeights.resize(InputNodes + 1,std::vector<double>(HiddenNodes));
  ChangeOutputWeights.resize(HiddenNodes + 1,std::vector<double>(OutputNodes));
  RandomizedIndex.resize(PatternCount);

}


static void initializeWeights() {
    for (int i = 0; i < HiddenNodes; ++i) {
        for (int j = 0; j <= InputNodes; ++j) {
            HiddenWeights[j][i] = 2.0 * (double(rand()) / RAND_MAX - 0.5) * InitialWeightMax;
            ChangeHiddenWeights[j][i] = 0.0;
        }
    }
    
    for (int i = 0; i < OutputNodes; ++i) {
        for (int j = 0; j <= HiddenNodes; ++j) {
            OutputWeights[j][i] = 2.0 * (double(rand()) / RAND_MAX - 0.5) * InitialWeightMax;
            ChangeOutputWeights[j][i] = 0.0;
        }
    }
}

static void feedForward(int p) {
    for (int i = 0; i < HiddenNodes; ++i) {
        double sum = HiddenWeights[InputNodes][i];  // Bias term
        for (int j = 0; j < InputNodes; ++j) {
            sum += Input[p][j] * HiddenWeights[j][i];
        }
        Hidden[i] = max(sum);  // ReLU
    }

    for (int i = 0; i < OutputNodes; ++i) {
        double sum = OutputWeights[HiddenNodes][i];  // Bias term
        for (int j = 0; j < HiddenNodes; ++j) {
            sum += Hidden[j] * OutputWeights[j][i];
        }
        Output[i] = max(sum);  // ReLU
    }
}

static void backpropagate(int p) {
    Error = 0.0;

    // Compute output layer deltas
    for (int i = 0; i < OutputNodes; ++i) {
        double delta = Target[p][i] - Output[i];
        OutputDelta[i] = delta;
        Error += delta * delta;
    }
    Error *= 0.5;

    // Compute hidden layer deltas
    for (int i = 0; i < HiddenNodes; ++i) {
        double sum = 0.0;
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

static void train() {
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
    srand(static_cast<unsigned>(time(0)));  
    getDataset(Input,Target);
    initializeParameters();
    initializeVectors();
    // loadTrainingData();
    // Initialize training pattern index
    for (int i = 0; i < PatternCount; ++i) {
        RandomizedIndex[i] = i;
    }
    
    initializeWeights();
    train();
    saveWeights(HiddenWeights,OutputWeights);
    return 0;
}
