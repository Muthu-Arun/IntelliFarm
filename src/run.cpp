#include"./run.h"
namespace Ai{
    rab r1;
    void initialize(){
        
        r1.setTrainingDataFile("./../dataSets/processedInput.csv", "./../dataSets/processedTarget.csv");
        r1.setWeightsFile("./../dataSets/hiddenWeights.bin","./../dataSets/OutputWeights.bin");
        r1.loadTrainingData();
        r1.train();
    }
static void print(const std::vector<double>& pvect){
    std::cout << "Printing Predicted Value : ";
    for(double i : pvect){
        std::cout << i << " ";
    }
    std::cout << "\n";
}
std::vector<double> getPrediction(const std::vector<double>& input){
    std::vector<double> predicted_val = r1.predict(input);
    print(predicted_val);
    return predicted_val;


}
}

