#include"./run.h"
namespace Ai{
    void initialize(){
        rab r1;
        r1.setTrainingDataFile("~/dev/dataSets/input.csv", "~/dev/dataSets/target.csv");
        r1.setWeightsFile("~/dev/dataSets/hiddenWeights.bin","~/dev/dataSets/OutputWeights.bin");
        r1.loadTrainingData();
        r1.train();
    }

std::vector<double> getPrediction(const std::vector<double> &input){
    std::vector<double> predicted_val = r1.predict(input);
    return predicted_val;


}
}

