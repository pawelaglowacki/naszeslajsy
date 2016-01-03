#include "NetworkOptimization.hpp"
#include "Ant.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
using namespace std;
NetworkOptimization::NetworkOptimization(CodeName codeName, unsigned int numberOfAnts): numberOfAnts(numberOfAnts)
{
    network.load(codeName);
    traffic.load(codeName);
}

void NetworkOptimization::printPathsWithLinks() const
{
    for (unsigned int i=0; i < network.getAmountOfPaths(); i++)
    {
        cout << "Path " << i << " ";
        const list <Link *> linksOfPath = network.paths[i].links;
        for (Link *link: linksOfPath)
        {
            cout << link->sourceNode << " -> " << link->destinationNode << " ";
        }
        cout << endl;
    }
}

void NetworkOptimization::createStructureForPheromones()
{
    unsigned int amountOfLinks = network.getAmountOfLinks();
    pheromones.resize(amountOfLinks);
    occupiedSlicesOnLinks.resize(amountOfLinks);
}

void NetworkOptimization::cleanStructureForPheromones()
{
    pheromones.clean();
    occupiedSlicesOnLinks.clean();
    requiredSlicesOnPaths.clean();
}

int NetworkOptimization::calculateRequiredSlices(vector < Path * > * paths, unsigned int volume)
{
    for (Path *path: *paths)
    {
        int requiredSlices = volume/(path->modulation * 2 * deltaS);
        requiredSlicesOnPaths.push_back(requiredSlices); 
    }
}

vector <Path * > NetworkOptimization::findCandidatePaths(unsigned int srcNode, unsigned int dstNode, unsigned int volume)
{
    vector < Path * > foundPaths = findPathsStartingWithNode(srcNode);
    storeOnlyPathsEndingOnNode(&foundPaths, dstNode);
    calculateRequiredSlices(foundPaths, volume);
    storePathsHaveFullfilledSlices(foundPaths);//todo: delete paths which has no range of required slices
    return foundPaths; // todo: remember to check exception!!
}

vector < Path * > NetworkOptimization::findPathsStartingWithNode(unsigned int node)
{
    vector < Path * > foundPaths;
    for (Path *path: network.paths)
    {
        Link firstLink = *(path->links.front());
        
        if (firstLink.sourceNode == node)
            foundPaths.push_back(path);   
    }
    if (foundPaths.empty())
        throw string("There are no paths for demand (source node issue)");
    
    return foundPaths;
}

void NetworkOptimization::storeOnlyPathsEndingOnNode(vector< Path * > * paths, unsigned int node)
{
    for (size_t i=0; i<paths->size(); i++)
    {
        Link lastLink = *(paths[i]->links.back());
        if (lastLink.destinationNode != node)
            paths->erase(paths->begin() + i);
    }
    if (paths->empty())
        throw string("There are no paths for demand (destination node issue)");
}

void NetworkOptimization::crossPaths(vector< Path *>  paths, Ant &ant)
{
    vector <double> costFunctionsForPaths;
    
    for (Path *path: paths)
    {
        int continuityOccupiedSlices = ant.goThroughPath(path); // represented in bits
        int numberOfOccupiedSlices = howManySlices(continuityOccupiedSlices);
        double pheromonesOnPath = howMuchPheromonesOnPath(path);
        double costFunction = calculateCostFunction(numberOfOccupiedSlices, pheromonesOnPath);
        costFunctionsForPaths.push_back(costFunction);
    }

    int bestPathId = chooseBestPathBasedOnCostFunction(costFunctionsForPaths);
    releasePheromones(*paths[bestPathId]);
}

int NetworkOptimization::chooseBestPathBasedOnCostFunction(vector <double> costFunctionsForPaths)
{
    double maxCostFunction=0;
    int pathId;
    for(unsigned int i=0; i<costFunctionsForPaths.size(); i++)
    {
        if(costFunctionsForPaths[i] > maxCostFunction)
        {
            maxCostFunction = costFunctionsForPaths[i];
            pathId = i;           
        }
    }
    return pathId;
}

double NetworkOptimization::howMuchPheromonesOnPath(vector <Link *> *path)
{
    double sumOfPheromones=0;
    for (Link *link: *path)
    {
        sumOfPheromones += pheromones[link->linkId];   
    }
    return sumOfPheromones;
}

double NetworkOptimization::calculateCostFunction(unsigned int numberOfOccupiedSlices, pheromonesOnPath)
{
    uniform_real_distribution<double> unif(0,1);
    default_random_engine re;
    double randomValue = unif(re);
    double result = ((1/exp(numberOfOccupiedSlices))+1) * (pheromonesOnPath+1) * (1+randomValue);

    return result;
}

void NetworkOptimization::releasePheromones(vector <Link *> path)
{
    for (Link *link: path)
    {
        pheromones[link->linkId] += pheromoneValue;
    }
}

void NetworkOptimization::runAnts(unsigned int sourceNode, unsigned int destinationNode, unsigned int volume)
{

    vector < Path * > paths = findCandidatePaths(sourceNode, destinationNode, volume);

    for (int i = 0; i<numberOfAnts; i++)
    {
        try
        {
            ants.push_back(Ant(occupiedSlicesOnLinks));
            Ant &ant = ants.back();
            crossPaths(paths, ant, demand);
        }
        catch (string fail)
        {
            cout << "Could not find path for demand << " << fail << endl;
            return;
        }
        //todo: after each iteration do updatePheromones
    }
    selectTheBestPathBasedOnPheromones(paths);
}

void NetworkOptimization::runUnicastDemands()
{
    for (UnicastDemand &demand: traffic.unicastDemands)
    {
        createStructureForPheromones(); 
        runAnts(demand.sourceNode, demand.destinationNode);
        cleanStructureForPheromones();
    }
}

void NetworkOptimization::selectTheBestPathBasedOnPheromones(vector< Path *> paths)
{
    maxNumberOfPheromones=0;
    Path *bestPath=nullptr;
    for (Path *path: paths)
    {
        double sumOfPheromones;
        sumOfPheromones = howMuchPheromonesOnPath(path);
        if (sumOfPheromones > maxNumberOfPheromones)
        {
            maxNumberOfPheromones = sumOfPheromones;
            bestPath = path;
        }
    }

    if (maxNumberOfPheromones)
        occuppySlicesOnLinks //todo: to continue
}

int NetworkOptimization::howManySlices(int slicesInBits)
{
    int counter = 0;
    for (unsigned int i=0; i < maxNumberOfSlicesPerLink; i++)
    {
        int slice = 1 << i;
        if (slicesInBits & slice)
        {
            counter++;
        }
    }
    return counter;
