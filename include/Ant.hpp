#pragma once
#include <vector>
#include "Network.hpp"
class Ant
{
    public:
        Ant(std::vector <int> &occupiedSlicesOnLinks);
        int goThroughPath(Path *path, unsigned int maxNumberOfSlices);
        void setActive(bool verdict);
        bool getActive();
    private:
        bool isActive;
        int continuityFreeSlicesForPath;
        std::vector <int> &occupiedSlicesOnLinks;
};
