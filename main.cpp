#include "field.h"

int main(){
    cout<<"Galois Field\n";
    int gen = 0b1000000000000011;
    Field myField(gen);
    int x,y;
    x= 0b00110;
    y= 30000;
	myField.showBin(myField.power(x,y));
    return 0;
}