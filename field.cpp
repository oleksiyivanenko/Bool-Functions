#include "field.h"
Field::Field(){
    gen= 0b1000000000000011;
}

Field::Field(int g){
    gen = g;
}

void Field::showBin(int shown){
    cout<< bitset < 16 >(shown)<<"\n";
}

void Field::showGen(){
    showBin(gen);
}

int Field::sum(int a, int b){
    return a ^ b;
}