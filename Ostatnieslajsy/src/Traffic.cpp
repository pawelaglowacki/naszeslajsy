#include "Traffic.hpp"
#include <fstream>
using namespace std;

void Traffic::load(CodeName codeName)
{
    this->codeName = codeName;
    loadUnicastDemands();
    loadAnycastDemands();
}

void Traffic::loadUnicastDemands()
{
    unsigned int numberOfDemands;
    string fileName = pathToDirWithFiles + codeName.ofUnicastDemands + ".dem";

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

void Traffic::loadAnycastDemands()
{
    unsigned int numberOfDemands;
    string fileName = pathToDirWithFiles + codeName.ofAnycastDemands + ".dea";

    ifstream file;
    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");

    file >> numberOfDemands;
    anycastDemands.resize(numberOfDemands);

    for (unsigned int i=0; i<numberOfDemands; i++)
    {
        AnycastDemand demand;
        file >> demand.node;
        file >> demand.downstream;
        file >> demand.upstream;

        anycastDemands.push_back(demand);
    }
                                    
    file.close();
}

unsigned int Traffic::getAmountOfUnicastDemands() const
{
    return unicastDemands.size();
}

unsigned int Traffic::getAmountOfAnycastDemands() const
{
    return anycastDemands.size();
}

