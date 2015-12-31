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
};
