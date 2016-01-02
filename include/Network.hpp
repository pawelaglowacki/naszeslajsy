#pragma once 
#include "Definitions.hpp"
#include <string>
#include <vector>
#include <map>
#include <list>

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
        std::vector< std::list < int > > listOfLinksFromNodes;
        std::vector< std::list < int > > listOfLinksToNodes;
        std::map<int, bool> dataCenters;

        void load(CodeName codeName); 
        unsigned int getAmountOfLinks() const;
        unsigned int getAmountOfPaths() const;
        unsigned int getAmountOfNodes() const;
        unsigned int getAmountOfDataCenters() const;
    private:
        CodeName codeName;
        void loadCandidatePaths();
        void loadNetworkTopology();
        void loadDistancesAndModulationsForPaths();
        void loadDataCenters();
        void loadContiguousLinksOfNodes(unsigned int amountOfNodes);
};
