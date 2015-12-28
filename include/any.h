#ifndef ANY_H
#define ANY_H
#include <fstream>
#include <iostream>
using namespace std;

class any
{
    public:
        int NO_demands;
        int (*any_demand)[3]; //list of single anycast demands, one demand: node, downstream, upstream
        any(string);
        virtual ~any();
        protected:
    private:
};

#endif // ANY_H
