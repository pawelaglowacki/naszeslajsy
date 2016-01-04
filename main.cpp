#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "NetworkOptimization.hpp"
#include "Definitions.hpp"
using namespace std;
#define SPECIFIC_SET 3

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
        codeName.pattern = pattern;
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
        vector <string> scenarios {"euro16_k2.txt", "euro16_k3.txt", "euro16_k5.txt", "euro16_k10.txt", "euro16_k30.txt"};
        for (string scenario: scenarios)
        {
            cout << "Scenario " << scenario << endl;
            vector <CodeName> codeNames = testAlgorithm(scenario);
#if SPECIFIC_SET 
            CodeName codeName = codeNames[SPECIFIC_SET];
#else
            for (CodeName codeName: codeNames)
            {
#endif
                const int numberOfAnts = 100;
                cout << "Codename " << codeName.pattern << endl;
                NetworkOptimization networkOptimization(codeName, numberOfAnts);
                clock_t begin = clock();
                //networkOptimization.printPathsWithLinks();
                networkOptimization.runUnicastDemands();
                networkOptimization.runAnycastDemands();
                clock_t end = clock();
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                cout << "Elapsed " << elapsed_secs << " seconds." << endl;
                networkOptimization.printStatistics();
                cout << endl;
#ifndef SPECIFIC_SET
            }
#endif

        }
    }
    catch (string exception)
    {
        cerr << "Error occured \"" << exception << "\"" << endl;
    }

    return 0;
}
