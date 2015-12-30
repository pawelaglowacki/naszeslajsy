#include "Traffic.hpp"
#include <fstream>
using namespace std;

void Traffic::load(string codeNameOfUnicastDemands, string codeNameOfAnycastDemands, string codeNameOfDataCenters, string pathToDirWithFiles)
{
    this->codeNameOfUnicastDemands = codeNameOfUnicastDemands;
    this->codeNameOfAnycastDemands = codeNameOfAnycastDemands;
    this->codeNameOfDataCenters = codeNameOfDataCenters;
    this->pathToDirWithFiles = pathToDirWithFiles;
    loadUnicastDemands();
}

void Traffic::loadUnicastDemands()
{
    unsigned int numberOfDemands;
    string fileName = pathToDirWithFiles + codeNameOfUnicastDemands + ".dem";

    ifstream file;
    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");

    file >> numberOfDemands;
    unicastDemands.resize(numberOfDemands);

    for (unsigned int i=0; i<numberOfDemands; i++)
    {
        UnicastDemand demand;
        file >> demand.sourceNode;
        file >> demand.destinationNode;
        file >> demand.volume;

        unicastDemands.push_back(demand);
    }
                                    
    file.close();
}

unsigned int Traffic::getAmountOfUnicastDemands()
{
    return unicastDemands.size();
}

