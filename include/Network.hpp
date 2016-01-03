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
}

class Network
{
    public:
        std::vector< Link > links;
        std::vector< Node > nodes;
        std::vector< Path > paths;
      //  std::vector< std::vector< int > > paths;
       // std::vector< int > distancesOfPaths;
       // std::vector< int > modulationsOfPaths;
 //       std::vector< std::list < int > > listOfLinksFromNodes;
   //     std::vector< std::list < int > > listOfLinksToNodes;
     //   std::map<int, bool> dataCenters;

        void load(CodeName codeName); 
        unsigned int getAmountOfLinks() const;
        unsigned int getAmountOfPaths() const;
        unsigned int getAmountOfNodes() const;
    private:
        CodeName codeName;
        void loadCandidatePaths();
        void loadNetworkTopology();
        void loadDistancesAndModulationsForPaths();
        void loadDataCenters();
        void loadNodes(unsigned int amountOfNodes);
        void findContiguousLinksOfNode(int node);
};
