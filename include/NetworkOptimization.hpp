#pragma once
#include <string>
#include <vector>
#include "Network.hpp"
#include "Traffic.hpp"
#include "Definitions.hpp"
#include "Ant.hpp"
struct Demand
{
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int requiredSlices;
};

class NetworkOptimization
{
    public:
        NetworkOptimization(CodeName codeName, unsigned int numberOfAnts); 
        void printPathsWithLinks() const;
        void runUnicastDemands();
    private:
        Network network;
        Traffic traffic;
        const double pheromoneValue = 0.20;
        const double deltaS = 6.25;
        const unsigned int numberOfAnts;
        unsigned int maxBitOfPaths;
        std::vector < Ant > ants;
        std::vector < int > occupiedSlicesOnLinks; // global for all demands
        std::vector < int > maxBitOfSlicesOnLinks; // global for all demands
        std::vector < double > pheromones; // local for one demand
        std::vector < int > requiredSlicesOnPaths; // local for one demand
        void createStructureForPheromones();
        void cleanStructureForPheromones();
        void runAnts(unsigned int sourceNode, unsigned int destinationNode, unsigned int volume);
        std::vector <Path *> findCandidatePaths(unsigned int srcNode, unsigned int dstNode, unsigned int volume); 
        std::vector < Path * > findPathsStartingWithNode(unsigned int node);
        void storeOnlyPathsEndingOnNode(std::vector< Path * > * paths, unsigned int node);
        void calculateRequiredSlices(std::vector < Path * > * paths, unsigned int volume);
        int howManySlices(int slicesInBits);
        double howMuchPheromonesOnPath(Path *path);
        double calculateCostFunction(unsigned int numberOfOccupiedSlices, double pheromonesOnPath);
        int chooseBestPathBasedOnCostFunction(std::vector <double>& costFunctionsForPaths);
        void releasePheromones(Path * path);
        void crossPaths(std::vector< Path *>  paths, Ant &ant);
        void selectTheBestPathBasedOnPheromones(std::vector< Path *> paths);
};
