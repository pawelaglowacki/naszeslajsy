#pragma once
#include <string>

const std::string pathToDirWithFiles = "data/";

struct CodeName
{
    std::string ofNetworkTopology;
    std::string ofUnicastDemands;
    std::string ofAnycastDemands;
    std::string ofPaths;
    std::string ofDataCenters;
};
