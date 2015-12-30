#pragma once
#include <string>
#include <vector>

struct UnicastDemand
{
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int volume;
};

class Traffic
{
    public:
        std::vector< UnicastDemand > unicastDemands;

        void load(std::string codeNameOfUnicastDemands, std::string codeNameOfAnycastDemands,
                  std::string codeNameOfDataCenters, std::string pathToDirWithFiles);   
        unsigned int getAmountOfUnicastDemands();
    
    private:
        std::string codeNameOfUnicastDemands, codeNameOfAnycastDemands, codeNameOfDataCenters;
        std::string pathToDirWithFiles;
        void loadUnicastDemands();
        void loadAnycastDemands();
};
