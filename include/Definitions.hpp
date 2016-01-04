#pragma once
#include <string>

const std::string pathToDirWithFiles = "data/";
const int maxNumberOfSlicesPerLink = 20;

struct CodeName
{
    std::string pattern;
    std::string ofNetworkTopology;
    std::string ofUnicastDemands;
    std::string ofAnycastDemands;
    std::string ofPaths;
    std::string ofDataCenters;
};
