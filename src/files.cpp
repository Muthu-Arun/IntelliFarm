#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::string fileName = "./dataSets/cropProductionDataset.csv";  // CSV file to read
    std::ifstream file(fileName);
    
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return 1;
    }

    std::string line, word;
    std::vector<std::vector<std::string>> data;

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
    
    file.close();
    std::cin.get();
    std::ofstream fileOut("./dataSets/filtered.csv");
    if(!fileOut.is_open())
        return 0;
    for(auto const &wrow: data){
        for(size_t i = 0;i<wrow.size();i++){
            if(wrow[0] != "Tamil Nadu" && wrow[0] != "State"){

                continue;
            }
                
            fileOut << wrow[i];
            if(i == wrow.size()-1){
                fileOut <<"\n";
                continue;
            }
                
            fileOut << ",";
        }
    }
    std::cin.get();
    // Display the CSV content
    for (const auto& row : data) {
        for (const auto& column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
