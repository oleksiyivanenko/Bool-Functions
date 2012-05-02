// field.h: Oleksiy Ivanenko
// Description: Header file for Field class

#ifndef __FIELD_H__
#define __FIELD_H__
#include <iostream>
#include <bitset>
#include <math.h>
using namespace std;

class Field{
    public:
        Field();
        ~Field();
        void showBin(int);
        void showGen();
        int sum(int,int);
        int countDeg(int);
        int genNBits(int);
        int mul(int,int);
        void countElements();
        void showElements();
        void showMultGroup();
        int getElemNum();
        int getMultElemNum();
        int power(int,int);
        int gornerPow(int,int);
        int* getElem();
        int* getMultElem();
        int getDeg();

    private:
        int gen, deg, elem_number, mult_elem_number;
        int *elements, *multGroup;
};

#endif