#include "NetworkOptimization.hpp"
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

int NetworkOptimization::runAntsAnycast(unsigned int sourceNode, vector<int> destinationNodes, unsigned int volume)
{

    vector < Path * > paths;
    vector < Path * > tmpPaths;
    for(int DC : destinationNodes)
    {
        tmpPaths = findCandidatePaths(sourceNode, DC, volume);
        paths.insert(paths.end() , tmpPaths.begin() , tmpPaths.end());
        // zasysa wszystkie mozliwe sciezki do datacenterow
    }

    for (unsigned int i = 0; i<numberOfAnts; i++)
    {
        try
        {
            ants.push_back(Ant(occupiedSlicesOnLinks));
            Ant &ant = ants.back();
            crossPaths(paths, ant);
        }
        catch (string fail)
        {
            cout << "Could not find path for demand << " << fail << endl;
            return 0;
        }
        //todo: after each iteration do updatePheromones
    }
    int dst =  selectTheBestPathBasedOnPheromones(paths);
// tutaj jest juz zdeterminowany data center
    return dst; // nr data centera
}

void NetworkOptimization::runAnycastDemands()//p
{
    occupiedSlicesOnLinks.resize(network.getAmountOfLinks());
    maxBitOfSlicesOnLinks.resize(network.getAmountOfLinks());

    vector <int> dataCenters;

    for(Node dC : network.nodes)
    {
        if(dC.isDataCenter)
            dataCenters.push_back(dC.nodeId);
    }

    int selectedDatacenter = 0;

    for (AnycastDemand &demand: traffic.anycastDemands)
    {
        createStructureForPheromones();
        selectedDatacenter = runAntsAnycast(demand.node, dataCenters, demand.upstream); // zamiast destination node jest kilka destination nodes
        runAnts(selectedDatacenter, demand.node, demand.downstream);
        cleanStructureForPheromones();
    }
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
}

void NetworkOptimization::cleanStructureForPheromones()
{
    pheromones.clear();
    //occupiedSlicesOnLinks.clean();
    requiredSlicesOnPaths.clear();
}

void NetworkOptimization::calculateRequiredSlices(vector < Path * > * paths, unsigned int volume)
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
    calculateRequiredSlices(&foundPaths, volume);
    return foundPaths; // todo: remember to check exception!!
}

vector < Path * > NetworkOptimization::findPathsStartingWithNode(unsigned int node)
{
    vector < Path * > foundPaths;
    for (Path &path: network.paths)
    {
        Link firstLink = *(path.links.front());
        
        if (firstLink.sourceNode == node)
            foundPaths.push_back(&path);   
    }
    if (foundPaths.empty())
        throw string("There are no paths for demand (source node issue)");
    
    return foundPaths;
}

void NetworkOptimization::storeOnlyPathsEndingOnNode(vector< Path * > * paths, unsigned int node)
{
    for (size_t i=0; i<paths->size(); i++)
    {
        Link lastLink = *(paths->at(i)->links.back());
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
    releasePheromones(paths[bestPathId]);
}

int NetworkOptimization::chooseBestPathBasedOnCostFunction(vector <double>& costFunctionsForPaths)
{
    double maxCostFunction=0;
    int pathId;
    for(unsigned int i=0; i<costFunctionsForPaths.size(); i++)
    {
       // cout << "Path " << i << " has costFunctions " << costFunctionsForPaths[i] << endl;
        if(costFunctionsForPaths[i] > maxCostFunction)
        {
            maxCostFunction = costFunctionsForPaths[i];
            pathId = i;           
        }
    }
    return pathId;
}

double NetworkOptimization::howMuchPheromonesOnPath(Path *path)
{
    double sumOfPheromones=0;
    for (Link *link: path->links)
    {
        sumOfPheromones += pheromones[link->linkId];   
    }
    return sumOfPheromones;
}

double NetworkOptimization::calculateCostFunction(unsigned int numberOfOccupiedSlices, double pheromonesOnPath)
{
    uniform_real_distribution<double> unif(0,5);
    default_random_engine re;
    double randomValue = unif(re);
    double result = ((1/exp(numberOfOccupiedSlices))+1) * (pheromonesOnPath+1) * (1+randomValue);

    return result;
}

void NetworkOptimization::releasePheromones(Path *path)
{
    for (Link *link: path->links)
    {
        pheromones[link->linkId] += pheromoneValue;
    }
}

void NetworkOptimization::disspatePheromones()
{
    for (double &pheromone: pheromones)
    {
        if (pheromone < pheromoneDisspate)
            pheromone = 0;
        else
            pheromone -= pheromoneDisspate;
    }
}

void NetworkOptimization::runAnts(unsigned int sourceNode, unsigned int destinationNode, unsigned int volume)
{

    vector < Path * > paths = findCandidatePaths(sourceNode, destinationNode, volume);
    for (unsigned int i = 0; i<numberOfAnts; i++)
    {
        try
        {
            ants.push_back(Ant(occupiedSlicesOnLinks));
            Ant &ant = ants.back();
            crossPaths(paths, ant);
        }
        catch (string fail)
        {
            cout << "Could not find path for demand << " << fail << endl;
            return;
        }
        disspatePheromones();
    }
    selectTheBestPathBasedOnPheromones(paths);
}

void NetworkOptimization::runUnicastDemands()
{
    occupiedSlicesOnLinks.resize(network.getAmountOfLinks());
    maxBitOfSlicesOnLinks.resize(network.getAmountOfLinks());
    for (UnicastDemand &demand: traffic.unicastDemands)
    {
        createStructureForPheromones(); 
        runAnts(demand.sourceNode, demand.destinationNode, demand.volume);
        cleanStructureForPheromones();
    }

    printStatistics();
}

void NetworkOptimization::printStatistics()
{
    int globalMaxBit=0;
    for (int maxBit: maxBitOfSlicesOnLinks)
    {
        if (maxBit > globalMaxBit)
            globalMaxBit = maxBit;
    }

    cout << "The result is " << globalMaxBit << endl;
}

int NetworkOptimization::selectTheBestPathBasedOnPheromones(vector< Path *> paths)
{
    double maxNumberOfPheromones=0;
    int bestPathId=0;
    int i=0;
    for (Path *path: paths)
    {
        double sumOfPheromones;
        sumOfPheromones = howMuchPheromonesOnPath(path);
        //cout << "Path number " << path->pathId << " has " << sumOfPheromones << " pheromones." << endl;
        if (sumOfPheromones > maxNumberOfPheromones)
        {
            maxNumberOfPheromones = sumOfPheromones;
            bestPathId = i;
        }
        i++;
    }
    int dst=0;
    if (maxNumberOfPheromones)
    {
        int requiredSlices = requiredSlicesOnPaths[bestPathId];
        int continuitySlices = findContinuitySlicesOnPath(paths[bestPathId]);
        int startingSlice = findFreeSlices(continuitySlices, requiredSlices);
        

        for (Link *link: paths[bestPathId]->links)
        {
            for (int j=0; j < requiredSlicesOnPaths[bestPathId]; j++)
                occupiedSlicesOnLinks[link->linkId] |= startingSlice+j;
            
            maxBitOfSlicesOnLinks[link->linkId] = startingSlice+requiredSlicesOnPaths[bestPathId];
            dst = link->destinationNode;
        }
        maxBitOfPaths = startingSlice + requiredSlicesOnPaths[bestPathId];
    }
    return dst;
}

int NetworkOptimization::findFreeSlices(int continuitySlices, int requiredSlices)
{
    int startingSlice=0;
    int counter=0;

    for (unsigned int i=0; i < maxBitOfPaths+requiredSlices; i++)
    {
        int slice = 1 < i;

        if ((continuitySlices & slice ) == 0)
        {
            if (counter == 0)
            {
                startingSlice=i;
            }
            counter++;
            if (counter == requiredSlices)
                break;
        }
    }

    return startingSlice;
}

int NetworkOptimization::findContinuitySlicesOnPath(Path *path)
{
    int continuitySlices = occupiedSlicesOnLinks[path->links.front()->linkId];
    for (Link *link: path->links)
    {
        continuitySlices &= occupiedSlicesOnLinks[link->linkId];   
    }
    return continuitySlices;
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
}
