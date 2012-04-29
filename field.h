#ifndef __FIELD_H__
#define __FIELD_H__
#include <iostream>
#include <bitset>
using namespace std;

class Field{
    public:
        Field();
        Field(int);
        void showBin(int);
        void showGen();
        int sum(int,int);
    private:
        int gen;
};

#endif