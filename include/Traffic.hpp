#pragma once
#include "Definitions.hpp"
#include <string>
#include <vector>

struct UnicastDemand
{
    unsigned int sourceNode;
    unsigned int destinationNode;
    unsigned int volume;
};

struct AnycastDemand
{
    unsigned int node;
    unsigned int downstream;
    unsigned int upstream;
};

class Traffic
{
    public:
        std::vector< UnicastDemand > unicastDemands;
        std::vector< AnycastDemand > anycastDemands;

        void load(CodeName codeName);   
        unsigned int getAmountOfUnicastDemands() const;
        unsigned int getAmountOfAnycastDemands() const;
    
    private:
        CodeName codeName;
        void loadUnicastDemands();
        void loadAnycastDemands();
};
