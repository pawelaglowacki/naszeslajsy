#include "Network.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Network::load(CodeName codeName)
{
    this->codeName = codeName;
    loadNetworkTopology();
    loadCandidatePaths();
    loadDistancesAndModulationsForPaths();
    loadDataCenters();
}

void Network::loadCandidatePaths()
{
    string fileName = pathToDirWithFiles + codeName.ofPaths + ".pat";
    
    ifstream file;
    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");
    
    int amountOfPaths;
    file >> amountOfPaths;
    paths.resize(amountOfPaths);

    int isActive;
    for(unsigned int nrOfPath = 0; nrOfPath < getAmountOfPaths(); nrOfPath++)
    {
        for(unsigned int link = 0; link < getAmountOfLinks(); link++)
        {
            file >> isActive;
            if(isActive)
            {
                paths[nrOfPath].push_back(link);
            }
        }
    }

    file.close();
}

void Network::loadNetworkTopology()
{
    unsigned int amountOfLinks, amountOfNodes;
    ifstream file;
    string fileName = pathToDirWithFiles + codeName.ofNetworkTopology + ".net";
    file.open(fileName);
    if (!file.is_open()) throw string(fileName + " does not exist");

    file >> amountOfNodes;
    file >> amountOfLinks;
    
    links.resize(amountOfLinks);

    unsigned int numberOfLink = 0;
    for(unsigned int i = 0; i < amountOfNodes; i++)   
    {
        for(unsigned int j = 0; j < amountOfNodes; j++)
        {
            int distanceOfLink;
            file >> distanceOfLink;
            if(distanceOfLink)
            {
                Link link;
                link.sourceNode = i;
                link.destinationNode = j;
                link.distance = distanceOfLink;
                links[numberOfLink] = link;
                numberOfLink++; 
            }
        }
    }
 
    file.close();
    
    if (numberOfLink != amountOfLinks)
        throw string("Different number of links");

    loadContiguousLinksOfNodes(amountOfNodes);
}

void Network::loadDistancesAndModulationsForPaths()
{
    string fileName = pathToDirWithFiles + codeName.ofPaths + ".len";
    ifstream file;

    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");

    unsigned int amountOfPaths;
    file >> amountOfPaths;
    if (amountOfPaths != getAmountOfPaths()) 
    {
        throw string("Different amount of paths in '" + fileName + "' file(" + to_string(amountOfPaths) + "). Should be " + to_string(getAmountOfPaths()) + ".");    
    }
    
    distancesOfPaths.resize(amountOfPaths);
    modulationsOfPaths.resize(amountOfPaths);                            

    for(unsigned int i=0; i<amountOfPaths; i++)
    {
        file >> distancesOfPaths[i];
        file >> modulationsOfPaths[i];
    }

    file.close();
}

void Network::loadDataCenters()
{
    string fileName = pathToDirWithFiles + codeName.ofDataCenters + ".rep";
    ifstream file;

    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");

    unsigned int numberOfReplicas;
    file >> numberOfReplicas;
    
    for(unsigned int i=0; i<numberOfReplicas; i++)
    {
        int node;
        file >> node;
        dataCenters[node] = true;
    }

    file.close();
}

void Network::loadContiguousLinksOfNodes(unsigned int amountOfNodes)
{
    nodes.resize(amountOfNodes);
    for (size_t node = 0; node < listOfLinksFromNodes.size(); node++)
    {
        for (size_t linkId = 0; linkId < links.size(); linkId++)
        {
            if (links[linkId].sourceNode == node)
            {
                listOfLinksFromNodes[node].push_back(linkId);
            }

            if (links[linkId].destinationNode == node)
            {
                listOfLinksToNodes[node].push_back(linkId);
            }
        }
    }
}

unsigned int Network::getAmountOfLinks() const
{
    return links.size();
}

unsigned int Network::getAmountOfPaths() const
{
    return paths.size();
}

unsigned int Network::getAmountOfNodes() const
{
    return listOfLinksFromNodes.size();
}

unsigned int Network::getAmountOfDataCenters() const
{
    return dataCenters.size();
}
