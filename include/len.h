#ifndef LEN_H
#define LEN_H
#include <fstream>
#include <iostream>
using namespace std;

class len
{
    public:
        int NO_paths;
        int (*arrayOfKmAndMp)[2];
        len(string);
        virtual ~len();
    protected:
    private:
};

#endif // LEN_H
