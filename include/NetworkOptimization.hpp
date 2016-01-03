#pragma once
#include <string>
#include <vector>
#include "Network.hpp"
#include "Traffic.hpp"
#include "Definitions.hpp"

struct Demand
{
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int requiredSlices;
};

class NetworkOptimization
{
    public:
        NetworkOptimization(CodeName codeName); 
        void printPathsWithLinks() const;
    private:
        Network network;
        Traffic traffic;
        const double pheromoneValue = 0.20;
        const double deltaS = 6.25;
        const unsigned int numberOfAnts;
        std::vector < Ant > ants;
        std::vector < int > occupiedSlicesOnLinks;
        std::vector < double > pheromones;
        std::vector < int > requiredSlicesOnPaths;
        void createStructureForPheromones();
        int howManySlices(int slicesInBits);
};
