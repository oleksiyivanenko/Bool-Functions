#ifndef __FIELD_H__
#define __FIELD_H__
#include <iostream>
using namespace std;

class Field{
    public:
        Field();
        Field(int);
        void showBin();
    private:
        int generator;
};

#endif