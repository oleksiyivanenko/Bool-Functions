#include "field.h"
Field::Field(){
    generator = 16;
}

Field::Field(int g){
    generator = g;
}

void Field::showBin(){
    int x = generator;
    int y = 0;
    while(x!=0){
        y = x & 1;
        x = x >> 1;
        cout<<y;
    }
    
    //    cout<<x<<"\n";
    //}
    cout<<"generator = "<<generator<<"\n";
}