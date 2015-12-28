#include "len.h"

len::len(string nr) // e02
{

string tmp="";
tmp+=nr;
tmp+=".len";
ifstream czyt;
czyt.open(tmp.c_str());

czyt>>NO_paths;
arrayOfKmAndMp = new int[NO_paths][2];

for(int i=0;i<NO_paths;i++)
{
    czyt>>arrayOfKmAndMp[i][0]; //km
    czyt>>arrayOfKmAndMp[i][1]; //Mp
}

czyt.close();}

len::~len()
{
    //dtor
}
