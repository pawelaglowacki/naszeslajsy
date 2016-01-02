#include <iostream>
#include <fstream>
#include <string>
#include "NetworkOptimization.hpp"
#include "Definitions.hpp"
using namespace std;


vector <CodeName> testAlgorithm(string nameOfTestingFile)
{
    vector < CodeName > codeNames;
    string fileName = pathToDirWithFiles + nameOfTestingFile;
           
    ifstream file;
    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");
                       
    while (!file.eof())
    {
        string pattern;
        file >> pattern;
        
        CodeName codeName;
        codeName.ofNetworkTopology = pattern.substr(0, 2);
        codeName.ofUnicastDemands = pattern.substr(2, 2);
        codeName.ofAnycastDemands = pattern.substr(4, 2);
        codeName.ofPaths = pattern.substr(6, 3);
        codeName.ofDataCenters = pattern.substr(9, 2);
        codeNames.push_back(codeName);
    }
    file.close();
    
    return codeNames;
}

int main()
{
    try
    {
        vector <CodeName> codeNames = testAlgorithm("euro16_k2.txt");
        for (CodeName codeName: codeNames)
        {
            NetworkOptimization networkOptimization(codeName);
            networkOptimization.printPathsWithLinks();
            return 0;
        }
    }
    catch (string exception)
    {
        cerr << "Error occured \"" << exception << "\"" << endl;
    }

    return 0;
}
