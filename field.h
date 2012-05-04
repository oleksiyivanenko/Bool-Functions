// field.h: Oleksiy Ivanenko
// Description: Header file for Field class

#ifndef __FIELD_H__
#define __FIELD_H__
#include <iostream>
#include <bitset>
#include <math.h>
using namespace std;

#define GENERATOR 0b1000000000000011 // Generating polynom

class Field{
    public:

        // Constructors and destructor
        Field();
        Field(int);
        ~Field();

        void run();

        // Basic functions
        void showBin(int);
        int countDeg(int);
        int genNBits(int);

        // Count elements of field
        void countElements();
        void countMultGroup();

        // Show elements of field
        void showElements();
        void showMultGroup();

        // Math operations in field
        int sum(int,int);
        int mul(int,int);
        int reduce(long);
        int power(int,int);
        int gornerPow(int,int);

        // Get functions
        int getDeg();
        int getElemNum();
        int getMultElemNum();
        int* getElem();
        int* getMultElem();

    private:
        int gen, deg, elem_number, mult_elem_number;
        int *elements, *multGroup;
};

#endif