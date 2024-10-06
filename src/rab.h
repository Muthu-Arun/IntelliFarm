#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

void getDataset(std::vector<std::vector<double>>& _input,std::vector<std::vector<double>>& _target );
void saveWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output);
void loadWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output);

class rab{
private: 
    int PatternCount;
    int InputNodes ;
    int HiddenNodes ;
    int OutputNodes ;
    double LearningRate = 0.0001;   // Reduced learning rate for smoother convergence
    double Momentum = 0.9;
    double InitialWeightMax = 0.5;
    double Success = 0.00001;
    int MaxTrainingCycles = 1000000;  // Safety limit on training cycles
    std::vector<std::vector<double>> Input;
    std::vector<std::vector<double>> Target;
    std::vector<double> Hidden;
    std::vector<double> Output;
    std::vector<std::vector<double>> HiddenWeights;
    std::vector<std::vector<double>> OutputWeights;
    std::vector<double> HiddenDelta;
    std::vector<double> OutputDelta;
    std::vector<std::vector<double>> ChangeHiddenWeights;
    std::vector<std::vector<double>> ChangeOutputWeights;
    std::vector<double> RandomizedIndex;
    double Error;
private:
    double max(double);
    void initializeVectors();
    void initializeParameters();
    void initializeWeights();
    void feedForward(int);
    void backpropagate(int);

public:
    void train();
    void predict(std::vector<double>&);
    rab();
    
};