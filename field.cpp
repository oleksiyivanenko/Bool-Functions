#include "field.h"

// Default constructor
Field::Field(){
    gen= 0b1000000000000011;
}

// Constructor in case you have another generator
Field::Field(int g){
    gen = g;
}

// Show our int's in binary form
void Field::showBin(int shown){
    cout<< bitset < 16 >(shown)<<"\n";
}

// Show generator polynom
void Field::showGen(){
    showBin(gen);
}

// Sum operation in our Field
int Field::sum(int a, int b){
    return a ^ b;
}

// Returns degree of polynom
int Field::countDeg(int polinom){
    int k = 0;
    while (polinom != 0){
        polinom >>= 1;
        k++;
    }
    return k-1;
}

// Returns n bits
int Field::genNBits(int n){
    int bits = 1;
    for(int i = 0;i < n-1;i++){
        bits <<= 1;
        bits++;
    }
    showBin(bits);
    return bits;
}