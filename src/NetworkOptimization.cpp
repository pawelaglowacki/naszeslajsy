#include "NetworkOptimization.hpp"
#include <iostream>
#include <string>
using namespace std;
NetworkOptimization::NetworkOptimization(CodeName codeName)
{
    network.load(codeName);
    traffic.load(codeName);
}

void NetworkOptimization::printPathsWithLinks() const
{
    for (unsigned int i=0; i < network.getAmountOfPaths(); i++)
    {
        cout << "Path " << i << " ";
        const vector <int> &linksOfPath = network.paths[i];
        for (unsigned int j=0; j < linksOfPath.size(); j++)
        {
            int numberOfLink = linksOfPath[j];    
            Link link = network.links[numberOfLink];
            cout << link.sourceNode << " -> " << link.destinationNode << " ";
        }
        cout << endl;
    }
}
