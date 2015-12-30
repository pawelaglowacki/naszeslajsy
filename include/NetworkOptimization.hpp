#pragma once
#include <string>
#include <vector>
#include "Network.hpp"
#include "Traffic.hpp"

class NetworkOptimization
{
    public:
        NetworkOptimization(std::string codeNameOfNetworkTopology, 
                            std::string codeNameOfUnicastDemands,
                            std::string codeNameOfAnycastDemands,
                            std::string codeNameOfPaths,
                            std::string codeNameOfDataCenters);
        void printPathsWithLinks();
    private:
        Network network;
        Traffic traffic;
};
