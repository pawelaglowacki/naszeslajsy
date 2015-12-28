#include "uni.h"

uni::uni(string nr)
{
//
string tmp="";
tmp+=nr;
tmp+=".dem";
ifstream czyt;
czyt.open(tmp.c_str());

czyt>>NO_demands;
uni_demand = new int[NO_demands][3];

for(int i=0;i<NO_demands;i++)
{
    czyt>>uni_demand[i][0]; //src
    czyt>>uni_demand[i][1]; //dst
    czyt>>uni_demand[i][2]; // value Hd
}

czyt.close();

}

uni::~uni()
{
delete [] uni_demand;
}
