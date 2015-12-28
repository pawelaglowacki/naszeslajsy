#include <iostream>
#include <string>
#include "net.h"
#include "uni.h"
#include "any.h"
#include "len.h"
#include "analyzePath.h"

using namespace std;

void wyswietl_wszystko(string rozszerzenie)
{
string plik="";

char tmp, tmp2;
    for(int i=0;i<=54;i++)
    {
        int liczba = i%100;
        tmp = '0' + (liczba/10);
        liczba = i%10;
        tmp2 = '0' + (liczba/1.0);
        plik+=tmp;
        plik+=tmp2;
        plik+=rozszerzenie;


        ifstream czyt;
        czyt.open(plik.c_str());
        char c;
        while(czyt.get(c))
        {
        cout<<c;
        }
        czyt.close();

        plik = "";
    }
}

void anal(analyzePath & pat, net & siec)
{

    for(int i = 0; i< pat.NO_Paths ; i++) //480
    {   cout<<"Path "<<i<<" ";
        for(int j = 0 ; j < pat.paths[i].size() ; j++)
        {
              // przelec wszstkie edge w path i napisz co to
              cout<<siec.links[pat.paths[i].at(j)][0]<<" -> ";
              cout<<siec.links[pat.paths[i].at(j)][1]<<" ";
        }
        cout<<endl;
    }

}


int main()
{
analyzePath pat("e02");
cout<<"num of paths in e02.pat file "<<pat.getNumberOfPaths()<<endl;

pat.showPathNr(479);

len dupa("e02");

//wyswietl_wszystko(".dem");
net siec;


//mamy siec .net i pat .pat

anal(pat, siec);

//cout<<siec.NO_links<<endl;
//cout<<siec.NO_nodes<<endl;

//uni unidemand("54");
//cout<<unidemand.uni_demand[0][2]<<endl;

//any anydemand("52");
//cout<<anydemand.any_demand[0][1];


    return 0;
}
