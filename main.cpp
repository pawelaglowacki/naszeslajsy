#include <iostream>
#include <string>
#include "NetworkOptimization.hpp"
using namespace std;

int main()
{
    try
    {
        NetworkOptimization networkOptimization("ee", "50", "00", "e02", "10");
        networkOptimization.printPathsWithLinks();
    }
    catch (string exception)
    {
        cerr << "Error occured \"" << exception << "\"" << endl;
    }

    return 0;
}
