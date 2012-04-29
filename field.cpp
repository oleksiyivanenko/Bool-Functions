#include "field.h"

// Constructor in case you have another generator
Field::Field(int g){
    gen = g;
    deg = countDeg(gen);
    polynom = gen & genNBits(deg);
    elem_number = pow(2,deg);
    mult_elem_number = elem_number - 1;
    elements = new int [elem_number];
    countElements(elements);
    multGroup = new int [mult_elem_number];
    for(int i = 0;i<mult_elem_number;i++){
        multGroup[i]=elements[i+1];
    }

}

// Destructor
Field::~Field(){
    if(elements != NULL) {
        delete [] elements;
    }
    if(multGroup != NULL) {
        delete [] multGroup;
    }
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
    return bits;
}


// Counts element of Field
void Field::countElements(int *elements){
    elements[0]=0;
    elements[1]=1;
    for(int i=2;i<elem_number;i++){
        elements[i]=elements[i-1]<<1;
        if (countDeg(elements[i]) >= deg){
            elements[i] ^= gen;
        }
    }
}

// Show field elements
void Field::showElements(){
    for(int i=0;i<elem_number;i++){
        showBin(elements[i]);
    }
}

// Show elements of multiplication group
void Field::showMultGroup(){
    for(int i = 0;i < mult_elem_number;i++){
        showBin(multGroup[i]);
    }
}

// Multiplication in Field
int Field::mul(int a, int b){
    int elem;
    int x=0,y=0;
    for(int i = 0; i < mult_elem_number; i++){
        if(multGroup[i]==a){
            x=i;
            break;
        }
    }
    for(int i = 0; i < mult_elem_number; i++){
        if(multGroup[i]==b){
            y=i;
            break;
        }
    }
    elem = multGroup[(x+y)%mult_elem_number];
    return elem;
}

// Raising to power
int Field::power(int a, int pwr){
    int elem = a;
    pwr %= mult_elem_number;
    if (pwr == 0) {
        return 1;
    }
    for(int i = 1;i<pwr;i++){
        elem = mul(elem,a);
    }
    return elem;
}