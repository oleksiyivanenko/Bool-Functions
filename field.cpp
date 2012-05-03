// field.cpp: Oleksiy Ivanenko
// Description: Methods which creates and works with Galois Fields

#include "field.h"

// Default constructor
Field::Field(){
    gen = GENERATOR;
    deg = countDeg(gen);
    elem_number = pow(2,deg);
    mult_elem_number = elem_number - 1;
    countElements();
    countMultGroup();
    cout<<"Field created\n";
}

// Constructor in case you have another generator
Field::Field(int generator){
    gen = generator;
    deg = countDeg(gen);
    elem_number = pow(2,deg);
    mult_elem_number = elem_number - 1;
    countElements();
    countMultGroup();
    cout<<"Field created\n";
}

// Destructor
Field::~Field(){
    if(elements != NULL) {
        delete[] elements;
    }
    if(multGroup != NULL) {
        delete[] multGroup;
    }
}

// Show our int's in binary form
void Field::showBin(int shown){
    cout<< bitset < 16 >(shown);
}

// Returns degree of polynom
int Field::countDeg(int polynom){
    int k = 0;
    while (polynom != 0){
        polynom >>= 1;
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

// Counts elements of Field
void Field::countElements(){
    elements = new int [elem_number];
    elements[0]=0;
    elements[1]=1;
    for(int i=2;i<elem_number;i++){
        elements[i] = elements[i-1] + 1;
        // elements[i]=elements[i-1]<<1;
        // if (countDeg(elements[i]) >= deg){
        //     elements[i] ^= gen;
        // }
    }
}

// Counts elements of Multiplication group
void Field::countMultGroup(){
    multGroup = new int [mult_elem_number];
    for(int i = 0;i < mult_elem_number;i++){
        multGroup[i]=elements[i+1];
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

// Sum operation in our Field
int Field::sum(int a, int b){
    return a ^ b;
}

// Multiplication in Field
int Field::mul(int a, int b){
    long product = 0;
    int x = 1;
    for(int i = 0;i <= countDeg(b);i++){
        if((b & x) != 0){
            product ^= (long)a << i;
        }
        x <<= 1;
    }
    return reduce(product);
}

// Reduce module deg
int Field::reduce(long a){
    while(countDeg(a) >= deg){
        a ^= (gen << countDeg(a) - deg);
    }
    return a;
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

// Gorner algorithm for rising to power
int Field::gornerPow(int a, int pwr){
    if(a == 0) return 0;
    int product;
    int term = a;
    pwr %= mult_elem_number;
    if(pwr & 1 == 1){
        product = a;
    }
    else{
        product = 1;
    }
    pwr >>= 1;
    while(pwr != 0){
        term = mul(term,term);
        if(pwr & 1 == 1){
            product = mul(product,term);
        }
        pwr >>= 1;
    }
    return product;
}

// Returns degree of generator polynom
int Field::getDeg(){
    return deg;
}
// Returns number of elements in field
int Field::getElemNum(){
    return elem_number;
}

// Returns number of elements in multiplication group
int Field::getMultElemNum(){
    return mult_elem_number;
}

// Returns pointer to array with field elements
int* Field::getElem(){
    return elements;
}

// Returns pointer to array with multiplication group elements
int* Field::getMultElem(){
    return multGroup;
}
