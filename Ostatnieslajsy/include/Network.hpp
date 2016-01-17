#pragma once 
#include "Definitions.hpp"
#include <string>
#include <vector>
#include <map>
#include <list>

struct Link
{
    unsigned int linkId;
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int distance;
};

struct Path
{
    unsigned int pathId;
    std::list <Link *> links;
    unsigned int distance;
    unsigned int modulation;
};

struct Node
{
    unsigned int nodeId;
    std::list < Link * > neighborLinksFromNode;
    std::list < Link * > neighborLinksToNode;
    bool isDataCenter;
};

class Network
{
    public:
        std::vector< Link > links;
        std::vector< Node > nodes;
        std::vector< Path > paths;

        void load(CodeName codeName); 
        unsigned int getAmountOfLinks() const;
        unsigned int getAmountOfPaths() const;
        unsigned int getAmountOfNodes() const;
        unsigned int getAmountOfDataCenters() const;
    private:
        CodeName codeName;
        unsigned int numberOfReplicas;
        void loadCandidatePaths();
        void loadNetworkTopology();
        void loadDistancesAndModulationsForPaths();
        void loadDataCenters();
        void loadNodes(unsigned int amountOfNodes);
        void findContiguousLinksOfNode(unsigned int node);
};
