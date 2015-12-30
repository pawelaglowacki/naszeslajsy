#pragma once 
#include <string>
#include <vector>

struct Link
{
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int distance;
};

class Network
{
    public:
        std::vector< std::vector< int > > paths;
        std::vector< int > distancesOfPaths;
        std::vector< int > modulationsOfPaths;
        std::vector< Link > links;

        void load(std::string codeNameOfNetworkTopology, std::string codeNameOfPaths, std::string pathToDirWithFiles);
        unsigned int getAmountOfLinks();
        unsigned int getAmountOfPaths();
        unsigned int getAmountOfNodes();
    private:
        std::string codeNameOfNetworkTopology, codeNameOfPaths, pathToDirWithFiles;
        unsigned int amountOfNodes;
        void loadCandidatePaths();
        void loadNetworkTopology();
        void loadDistancesAndModulationsForPaths();
};
