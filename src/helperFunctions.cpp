#include "helperFunctions.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility> 
#include <stdexcept>
#include <sstream> 

std::vector<int> readCsv(std::string filename) {
    
    std::vector<int> result;

    std::ifstream myFile(filename);
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line, colname;
    int val;

    if (myFile.good())
    {
        std::getline(myFile, line);

        std::stringstream ss(line);

        while (std::getline(ss, colname, ','))
        {
            result.push_back(std::stoi(colname));
        }
    }

    myFile.close();
    return result;
}
