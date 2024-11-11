#include"rab.h"

double rab::max(double x){
    if(x >= 0)
        return x;
    else
        return 0;
}


void rab::initializeParameters(){
    PatternCount = Input.size();
    InputNodes = Input[0].size();
    HiddenNodes = InputNodes+1;
    OutputNodes = Target[0].size();

}
// int RandomizedIndex[PatternCount];
void rab::initializeVectors(){
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


void rab::initializeWeights() {
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

void rab::feedForward(int p) {
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

void rab::backpropagate(int p) {
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

void rab::train() {
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
    saveWeights();
}

std::vector<double> rab::predict(const std::vector<double>& _input){
     loadWeights();
    for (int i = 0; i < HiddenNodes; ++i) {
        double sum = HiddenWeights[InputNodes][i];  // Bias term
        for (int j = 0; j < InputNodes; ++j) {
            sum += _input[j] * HiddenWeights[j][i];
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
    for(double i : Output){
        std::cout<< i <<" ";
    }
    std::cout<<"\n\n";
    return Output;
}

rab::rab(){
    std::cout<<"Constructor called \n";
    srand(static_cast<unsigned>(time(0)));
}

void rab::loadTrainingData(){
    getDataset();
    initializeParameters();
    initializeVectors();
    initializeWeights();
    // Initialize training pattern index
    for (int i = 0; i < PatternCount; ++i) {
        RandomizedIndex[i] = i;
    }
}

void rab::setTrainingDataFile(std::string _input,std::string _target){
    inputFile = _input; targetFile = _target;
}

void rab::setWeightsFile(std::string _hidden, std::string _output){
    hiddenWeightsFile = _hidden; outputWeightsFile = _output;
}

/*
int main() {
    srand(static_cast<unsigned>(time(0)));  
    getDataset(Input,Target);
    initializeParameters();
    initializeVectors();
    // Initialize training pattern index
    for (int i = 0; i < PatternCount; ++i) {
        RandomizedIndex[i] = i;
    }
    

    predict();
    std::cin.get();
    // initializeWeights();
    // train();
    std::cout<<"\n\n";
    saveWeights(HiddenWeights,OutputWeights);
    return 0;
}
*/
void rab::getDataset(){

 
    std::ifstream file(inputFile);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << inputFile << std::endl;
        
    }

    std::string line, word;
    std::vector<std::vector<std::string>> data;
    // std::vector<std::vector<int>> idata;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream s(line);
        std::vector<std::string> row;
        // std::cout<<"\n"<<s.str(); break;
        // Parse each word (comma separated)
        while (std::getline(s, word, ',')) {
            row.push_back(word);
        }
        
        data.push_back(row);
        
    }
    for(int i = 0;i < data.size();i++){
        std::vector<double> row;
        for(int j = 0; j < data[i].size();j++){
            // log(data[i][j]);
            
            row.push_back(std::stod(data[i][j]));
        }
        Input.push_back(row);
    }
    data.clear();
    std::ifstream tfile(targetFile);
        while (std::getline(tfile, line)) {
        std::stringstream s(line);
        std::vector<std::string> row;
        // std::cout<<"\n"<<s.str(); break;
        // Parse each word (comma separated)
        while (std::getline(s, word, ',')) {
            row.push_back(word);
        }
        
        data.push_back(row);
       
    }
    for(int i = 0;i < data.size();i++){
        std::vector<double> row;
        for(int j = 0; j < data[i].size();j++){
            // log(data[i][j]);
            
            row.push_back(std::stod(data[i][j]));
        }
        Target.push_back(row);
    }
    // for(int i = 0;i<_input.size();i++){
    //     for(int j = 0; j< _input[i].size();j++){
    //         std::cout<< _input[i][j] << " ";
    //     }
    //     std::cout<<"Target "<< _target[i][0] <<"\n ";

    // }
    file.close();
    tfile.close();
    // return data;

}

void rab::saveWeights(){
    std::ofstream hwfile(hiddenWeightsFile,std::ios::binary);
    for(std::vector<double>& row : HiddenWeights){
        for(double i : row){
            hwfile.write(reinterpret_cast<const char*>(&i),sizeof(i));
            // LOG(i);
        }
        // LN;
    }
    hwfile.close();
    std::ofstream owfile(outputWeightsFile,std::ios::binary);
    for(std::vector<double>& row : OutputWeights){
        for(double i : row){
            owfile.write(reinterpret_cast<const char*>(&i),sizeof(i));
            // LOG(i);
        }
        // LN;
    }
    owfile.close();
}

void rab::loadWeights(){
    std::ifstream owfile(outputWeightsFile,std::ios::binary);
    for(std::vector<double>& row : OutputWeights){
        for(double& i : row){
            owfile.read(reinterpret_cast<char*>(&i),sizeof(i));
            // LOG(i);
        }
        // LN;
        
    }
    owfile.close();
    std::ifstream hwfile(hiddenWeightsFile,std::ios::binary);
    for(std::vector<double>& row : HiddenWeights){
        for(double& i : row){
            hwfile.read(reinterpret_cast<char*>(&i),sizeof(i));
            // LOG(i);
        }
        // LN;
        
    }
    hwfile.close();
    
}

int main(){
    rab r;
    r.setTrainingDataFile("./../dataSets/tempinput.csv","./../dataSets/temptarget.csv");
    r.setWeightsFile("./../dataSets/hiddenWeights.bin","./../dataSets/OutputWeights.bin");
    r.loadTrainingData();
    r.train();
    std::vector<double> sample = {2,125.4};
    r.predict(sample);
}
int maine(){
    rab r;
    r.setWeightsFile("./dataSets/hiddenWeights.bin","./dataSets/OutputWeights.bin");
    r.setTrainingDataFile("./dataSets/input.csv","./dataSets/target.csv");
    r.loadTrainingData();
    std::vector<double> sample = {0,0,0,1,1258.0,0};
    r.predict(sample);
    return 0;
}
