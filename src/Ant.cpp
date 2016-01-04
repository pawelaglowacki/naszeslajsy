#include "Ant.hpp"
#include "Definitions.hpp"
using namespace std;

int Ant::goThroughPath(Path * path)
{
    int continuitySlices = occupiedSlicesOnLinks[path->links.front()->linkId];
    for (Link *link: path->links)
    {
        continuitySlices &= occupiedSlicesOnLinks[link->linkId];   
    }
    return continuitySlices;
}


Ant::Ant(vector <int> &occupiedSlicesOnLinks): isActive(1), occupiedSlicesOnLinks(occupiedSlicesOnLinks)
{
}
