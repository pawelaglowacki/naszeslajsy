#pragma once
#include <vector>

class Ant
{
    public:
        Ant();
        int goThroughPath(vector <int> &path);
        void setActive(bool verdict);
        bool getActive();
    private:
        bool isActive;
};
