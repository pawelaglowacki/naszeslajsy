#include "Network.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Network::load(string codeNameOfNetworkTopology, string codeNameOfPaths, string pathToDirWithFiles)
{
    this->codeNameOfNetworkTopology = codeNameOfNetworkTopology;
    this->codeNameOfPaths = codeNameOfPaths;
    this->pathToDirWithFiles = pathToDirWithFiles;
    loadNetworkTopology();
    loadCandidatePaths();
    loadDistancesAndModulationsForPaths();
}

void Network::loadCandidatePaths()
{
    string fileName = pathToDirWithFiles + codeNameOfPaths + ".pat";
    
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
    unsigned int amountOfLinks;
    ifstream file;
    string fileName = pathToDirWithFiles + codeNameOfNetworkTopology + ".net";
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
                cout<<"link z "<<i <<" do "<<j<< " nr " << numberOfLink << endl;
            }
        }
    }
 
    file.close();
    
    if (numberOfLink != amountOfLinks)
        throw string("Different number of links");
}

void Network::loadDistancesAndModulationsForPaths()
{
    string fileName = pathToDirWithFiles + codeNameOfPaths + ".len";
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

unsigned int Network::getAmountOfLinks()
{
    return links.size();
}

unsigned int Network::getAmountOfPaths()
{
    return paths.size();
}

unsigned int Network::getAmountOfNodes()
{
    return amountOfNodes;
}

