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
                link.linkId = numberOfLink;
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

    loadNodes(amountOfNodes);
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
        Path path;
        path.pathId = nrOfPath;
        for(unsigned int linkId = 0; linkId < getAmountOfLinks(); linkId++)
        {
            file >> isActive;
            if(isActive)
            {
                path.links.push_back(&links[linkId]);
            }
        }
        paths[nrOfPath] = path;
    }

    file.close();
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

    for(unsigned int i=0; i<amountOfPaths; i++)
    {
        file >> paths[i].distance;
        file >> paths[i].modulation;
    }

    file.close();
}

void Network::loadDataCenters()
{
    string fileName = pathToDirWithFiles + codeName.ofDataCenters + ".rep";
    ifstream file;

    file.open(fileName.c_str());
    if (!file.is_open()) throw string(fileName + " does not exist");

    file >> numberOfReplicas;

    for(unsigned int i=0; i<numberOfReplicas; i++)
    {
        int node;
        file >> node;
        nodes[node].isDataCenter = true;
    }

    file.close();
}

void Network::loadNodes(unsigned int amountOfNodes)
{
    for (size_t i = 0; i < amountOfNodes; i++)
    {
        Node node;
        node.nodeId = i;
        nodes.push_back(node);
        findContiguousLinksOfNode(i);
    }
}

void Network::findContiguousLinksOfNode(unsigned int node)
{
    for (size_t linkId = 0; linkId < links.size(); linkId++)
    {
        if (links[linkId].sourceNode == node)
        {
            nodes[node].neighborLinksFromNode.push_back(&links[linkId]);
        }

        if (links[linkId].destinationNode == node)
        {
            nodes[node].neighborLinksToNode.push_back(&links[linkId]);
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
    return nodes.size();
}

unsigned int Network::getAmountOfDataCenters() const
{
    return numberOfReplicas;
}
