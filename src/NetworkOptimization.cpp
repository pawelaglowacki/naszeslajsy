#include "NetworkOptimization.hpp"
#include "Ant.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>

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

void NetworkOptimization::createStructureForPheromones()
{
    for (Link link: network.links)
    {
 //       pheromones
    }
}

vector <vector<int > & > NetworkOptimization::findCandidatePathsForUnicastDemand(UnicastDemand demand)
{
    vector < vector < int > & > foundPaths = findPathsContainsSourceNode(demand.sourceNode);
    foundPaths = storeOnlyPathsContainsDestNode(foundPaths, demand.destinationNode);

}

vector<vector< int > &> NetworkOptimization::findPathsContainsSourceNode(unsigned int node)
{
    vector < vector < int > & > foundPaths;
    for (vector <int > &path: network.paths)
    {
        for (int link: listOfLinksFromNodes[node])
        {
            vector < int >::iterator result;
            result = find(path.begin(), path.end(), link);
            if (result != path.end())
            {
                foundPaths.push_back(path);
               // startingPositions
               // todo: continue
                break;
            }
        }
    }
    return foundPaths;
}

vector<vector< int > &> NetworkOptimization::storeOnlyPathsContainsDestNode(
                                vector < vector < int > & > & selectedPaths,
                                unsigned int node)
{
    vector < vector < int > & > foundPaths;
    for (vector <int > & path: selectedPaths)
    {
        for (int link: listOfLinksToNodes[node])
        {
            vector < int >::iterator result;
            result = find(path.begin(), path.end(), link);
            if (result != path.end())
            {
                foundPaths.push_back(path);
                break;
            }
        }
    }
    return foundPaths;
}

void NetworkOptimization::crossPaths(Ant &ant)
{
    vector <int> continuityFreeSlicesForPaths;
    vector <vector <int> *> candidatePathsWithContinuityFreeSlices;
    int maximumNumberOfFreeSlices = 0; // todo: add finding paths
    for (vector <int> &path: network.paths)
    {
        int continuityFreeSlices = ant.goThroughPath(path); // represented in bits
        int numberOfFreeSlices = howManySlices(continuityFreeSlices); //todo: implement howManySlices
        if (numberOfFreeSlices > maximumNumberOfFreeSlices)
        {
            maximumNumberOfFreeSlices = numberOfFreeSlices;
            candidatePathsWithContinuityFreeSlices.clean();
            candidatePathsWithContinuityFreeSlices.push_back(&path);
        }
        else if (maximumNumberOfFreeSlices && 
                 numberOfFreeSlices == maximumNumberOfFreeSlices)
        {
            candidatePathsWithContinuityFreeSlices.push_back(&path);
        
    }
    
    vector <int> * selectedPath;
    if (!candidatePathsWithContinuityFreeSlices.empty())
    {
        selectedPath = selectPath(candidatePathsWithContinuityFreeSlices);
        releasePheromones(*selectedPath);

    }
    else
       ant.setActive(false); 
}

void NetworkOptimization::releasePheromones(vector <int> &path)
{
    //todo: resize przy createPheromonesStructure
    for (int linkId: path)
    {
        pheromones[linkId] += pheromoneValue;
    }
}

vector <int> * NetworkOptimization::selectPath(vector <vector <int> *> & paths)
{
    size_t numberOfPossiblePaths = paths.size();
    srand(time(NULL));
    if (numberOfPossiblePaths > 1)
    {
        int randomValue = rand()%numberOfPossiblePaths;
        //todo: check pheromones
        return paths[randomValue];
    }
    else if (numberOfPossiblePaths)
        return paths.back();
    else
        return NULL;
}

void NetworkOptimization::runAnts(int numberOfAnts, int timeToLive)
{
    for (int i = 0; i<numberOfAnts; i++)
    {
        ants.push_back(Ant);
        Ant &ant = ants.back();
        crossPaths(ant);
        //todo: after each iteration do updatePheromones
    }
}

