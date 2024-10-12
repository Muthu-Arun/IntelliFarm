#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<fstream>
#include<sstream>

class rab{
private: 
    int PatternCount;
    int InputNodes ;
    int HiddenNodes ;
    int OutputNodes ;
    double LearningRate = 0.00001;   // Reduced learning rate for smoother convergence
    double Momentum = 0.9;
    double InitialWeightMax = 0.5;
    double Success = 0.001;
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
    std::string hiddenWeightsFile, outputWeightsFile;
    std::string inputFile, targetFile; 

private:
    double max(double);
    void initializeVectors();
    void initializeParameters();
    void initializeWeights();
    void feedForward(int);
    void backpropagate(int);
    void getDataset();
    void saveWeights();
    void loadWeights();


public:
    void setTrainingDataFile(std::string _input, std::string _target);
    void setWeightsFile(std::string _hidden, std::string _output);
    void train();
    void predict(std::vector<double>&);
    rab();
    void loadTrainingData();
    
};