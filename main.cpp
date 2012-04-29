#include "main.h"

int main(){
    cout<<"Galois Field\n";
    Field myField;
    cout<<"Generator: ";
    myField.showGen();
    myField.genNBits(15);
    return 0;
}