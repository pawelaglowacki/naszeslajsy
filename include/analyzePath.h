#ifndef ANALYZEPATH_H
#define ANALYZEPATH_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class analyzePath
{
    public:
        int NO_Paths;
        vector<int> (*paths);
    //    int (*paths)[10]; // zamien 10 na dowolne cos
        int getNumberOfPaths();
        void showPathNr(int);
        analyzePath(string);
        protected:
    private:
};

#endif // ANALYZEPATH_H
