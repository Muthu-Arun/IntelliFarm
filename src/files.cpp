#include <iostream>
#include <fstream>
#include <vector>
#define LOG(x) std::cout<< x << " "
#define LN std::cout<< "\n "
void saveWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output){
    std::ofstream hwfile("./dataSets/hiddenWeights.bin",std::ios::binary);
    for(std::vector<double>& row : _hidden){
        for(double i : row){
            hwfile.write(reinterpret_cast<const char*>(&i),sizeof(i));
            // LOG(i);
        }
    }
    hwfile.close();
    std::ofstream owfile("./dataSets/OutputWeights.bin",std::ios::binary);
    for(std::vector<double>& row : _output){
        for(double i : row){
            owfile.write(reinterpret_cast<const char*>(&i),sizeof(i));
            // LOG
        }
    }
    owfile.close();
}

void loadWeights(std::vector<std::vector<double>>& _hidden,std::vector<std::vector<double>>& _output){
    std::ifstream owfile("./dataSets/OutputWeights.bin",std::ios::binary);
    for(std::vector<double>& row : _output){
        for(double& i : row){
            owfile.read(reinterpret_cast<char*>(&i),sizeof(i));
            LOG(i);
        }
        LN;
        
    }
    owfile.close();
    std::ifstream hwfile("./dataSets/hiddenWeights.bin",std::ios::binary);
    for(std::vector<double>& row : _hidden){
        for(double& i : row){
            hwfile.read(reinterpret_cast<char*>(&i),sizeof(i));
            LOG(i);
        }
        LN;
        
    }
    hwfile.close();
    
}