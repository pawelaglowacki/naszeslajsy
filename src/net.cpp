#include "net.h"

net::net()
{

pheromon_level = 0;
ifstream czyt;
czyt.open("ee.net");

czyt >> NO_nodes;
czyt >> NO_links;

Kilometers = new int *[NO_nodes];
for (int i = 0; i < NO_nodes; i++)
Kilometers[i] = new int [NO_nodes];

int linkNr = 0;

for(int i=0;i<NO_nodes;i++)
    for(int j=0;j<NO_nodes;j++)
    {
        czyt >> Kilometers[i][j];
        if(Kilometers[i][j] > 0)
        {
            links[linkNr][0] = i;
            links[linkNr][1] = j;
            links[linkNr][2] = Kilometers[i][j];
            linkNr++;
     //       cout<<"link z "<<i <<" do "<<j<<endl;
        }
    }
czyt.close();

}

net::~net()
{

for(int i=0;i<NO_nodes;i++)
    delete [] Kilometers[i];
    delete [] Kilometers;
    Kilometers = nullptr;
}
