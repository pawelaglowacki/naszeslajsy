#ifndef NET_H
#define NET_H
#include <iostream>
#include <fstream>
using namespace std;

class net
{
    public:
        int **Kilometers; // n x n dim matrix of length on links
        int NO_nodes;
        int NO_links;
        double pheromon_level; // to jest z dupy na razie
        int links[48][3]; // link -> from, to, km
        net();
        ~net();

        int getLength(int x, int y)
        {
            return Kilometers[x][y];
        }


    protected:
    private:
};

#endif // NET_H
