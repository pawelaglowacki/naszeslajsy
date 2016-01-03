#include "Ant.hpp"
#include "Definitions.hpp"
using namespace std;

int Ant::goThroughPath(Path * path)
{
    continuityOccupiedSlicesForPath = 0;
    for (unsigned int i = 0; i < path->links.size(); i++)
    {
        for (unsigned int j = 0; j < maxNumberOfSlicesPerLink; j++)
        {
            int slice = 1 << j;
            if (occupiedSlicesOnLinks[path->links[i]->linkId] & slice)
            {
                continuityOccupiedSlicesForPath |= slice;   
            }
        }
    }
    return continuityOccupiedSlicesForPath;
}


Ant::Ant(vector <int> &occupiedSlicesOnLinks): isActive(1), occupiedSlicesOnLinks(occupiedSlicesOnLinks)
{
}
