#include "any.h"

any::any(string nr)
{

string tmp="";
tmp+=nr;
tmp+=".dea";
ifstream czyt;
czyt.open(tmp.c_str());

czyt>>NO_demands;
any_demand = new int[NO_demands][3];

for(int i=0;i<NO_demands;i++)
{
    czyt>>any_demand[i][0]; //node
    czyt>>any_demand[i][1]; //downstream
    czyt>>any_demand[i][2]; // upstream
}

czyt.close();

}

any::~any()
{
delete [] any_demand;
}
