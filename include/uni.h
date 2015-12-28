#ifndef UNI_H
#define UNI_H
#include <iostream>
#include <fstream>

using namespace std;
// dem files, unicast demands

class uni
{
    public:
        int NO_demands;
        int (*uni_demand)[3]; //list of single unicast demands, one demand: src, dst, value
        uni(string);
        virtual ~uni();
    protected:
    private:
};

#endif // UNI_H
