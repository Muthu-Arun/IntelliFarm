#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<memory>
std::unique_ptr<std::vector<std::vector<std::string>>>& getDataset(){

    std::string fileName = "./dataSets/cropProductionDataset.csv";  // CSV file to read
    std::ifstream file(fileName);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        
    }

    std::string line, word;
    std::unique_ptr<std::vector<std::vector<std::string>>> data = std::make_unique<std::vector<std::vector<std::string>>>();

    // Read each line from the file
    while (std::getline(file, line)) {
        std::stringstream s(line);
        std::vector<std::string> row;
        // std::cout<<"\n"<<s.str(); break;
        // Parse each word (comma separated)
        while (std::getline(s, word, ',')) {
            row.push_back(word);
        }
        data->push_back(row);
    }
    
    file.close();
    return data;

}