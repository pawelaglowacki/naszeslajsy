#include "NetworkOptimization.hpp"
#include <iostream>
#include <string>
using namespace std;
NetworkOptimization::NetworkOptimization(string codeNameOfNetworkTopology, 
                                         string codeNameOfUnicastDemands,
                                         string codeNameOfAnycastDemands,
                                         string codeNameOfPaths,
                                         string codeNameOfDataCenters)
{
    string pathToDirWithFiles("data/");
    network.load(codeNameOfNetworkTopology, codeNameOfPaths, pathToDirWithFiles);
    traffic.load(codeNameOfUnicastDemands, codeNameOfAnycastDemands,
                 codeNameOfDataCenters, pathToDirWithFiles);
}

void NetworkOptimization::printPathsWithLinks()
{
    for (unsigned int i=0; i < network.getAmountOfPaths(); i++)
    {
        cout << "Path " << i << " ";
        vector <int> &linksOfPath = network.paths[i];
        for (unsigned int j=0; j < linksOfPath.size(); j++)
        {
            int numberOfLink = linksOfPath[j];    
            Link link = network.links[numberOfLink];
            cout << link.sourceNode << " -> " << link.destinationNode << " ";
        }
        cout << endl;
    }
}
