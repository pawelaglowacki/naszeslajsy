#include "analyzePath.h"

analyzePath::analyzePath(string k) // k == e02
{

string tmp="";
tmp+=k;
tmp+=".pat";

ifstream czyt;
czyt.open(tmp.c_str());

czyt>>NO_Paths; //480

paths = new vector<int>[NO_Paths];

int cyfra;
for(int nrOfPath = 0; nrOfPath < NO_Paths ; nrOfPath++) //480 razy
for(int link= 0 ; link < 48 ; link++)
{
    czyt >> cyfra;
    if(cyfra == 1)
    {
    paths[nrOfPath].push_back(link);
    }
}

czyt.close();
}

int analyzePath::getNumberOfPaths()
{
    return NO_Paths;
}

void analyzePath::showPathNr(int nr)
{
   cout<<"links index = ";
   for(int i = 0 ; i < paths[nr].size() ; i++)
   {
       cout<<paths[nr].at(i)<<" ";
   }
cout<<endl;
}
