#pragma once
#include <string>
#include <vector>
#include "Network.hpp"
#include "Traffic.hpp"
#include "Definitions.hpp"

class NetworkOptimization
{
    public:
        NetworkOptimization(CodeName codeName); 
        void printPathsWithLinks() const;
    private:
        Network network;
        Traffic traffic;
        const double pheromoneValue = 0.20;
        std::vector < Ant > ants;
        std::vector < double > pheromones;
        void createStructureForPheromones()
};
