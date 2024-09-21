#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<memory>
#include<string>
#define log(x) std::cout << x << "\n"
void getDataset(std::vector<std::vector<int>>& _input,std::vector<std::vector<int>>& _target ){

    std::string fileName = "./dataSets/input.csv";  // CSV file to read
    std::ifstream file(fileName);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        
    }

    std::string line, word;
    std::vector<std::vector<std::string>> data;
    std::vector<std::vector<int>> idata;
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
        std::vector<int> row;
        for(int j = 0; j < data[i].size();j++){
            // log(data[i][j]);
            
            row.push_back(std::stoi(data[i][j]));
        }
        _input.push_back(row);
    }
    data.clear();
    std::ifstream tfile("./dataSets/target.csv");
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
        std::vector<int> row;
        for(int j = 0; j < data[i].size();j++){
            // log(data[i][j]);
            
            row.push_back(std::stoi(data[i][j]));
        }
        _target.push_back(row);
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