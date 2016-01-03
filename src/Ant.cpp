#include "Ant.hpp"
#include "Definitions.hpp"
using namespace std;

int Ant::goThroughPath(Path * path, unsigned int maxNumberOfSlices)
{
    if (maxNumberOfSlices == 0)
        return 0;
    int continuityOccupiedSlicesForPath = 0;
    for (Link * link: path->links)
    {
        for (unsigned int j = 0; j < maxNumberOfSlices; j++)
        {
            int slice = 1 << j;
            if (occupiedSlicesOnLinks[link->linkId] & slice)
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
