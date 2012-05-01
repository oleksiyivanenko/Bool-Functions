#include "function.h"

Function::Function(){
	N = (1<<10)+(1<<7)-1;
	M = (1<<7)+(1<<3)-1;
	M_vals = new int[FuncField.getElemNum()];
	M_vals = countFunction(M);
}

Function::~Function(){
	if(M_vals != NULL) {
        delete [] M_vals;
    }
    if(N_vals != NULL) {
        delete [] N_vals;
    }
}

int* Function::countFunction(int a){
	int elements_number = FuncField.getElemNum();
	int *values;
	int *elements;
	elements = FuncField.getElem();
	values = new int[elements_number];
	for(int i = 0;i < elements_number;i++){
		values[i] = FuncField.gornerPow(elements[i],a);
		cout<<i<<"\t";
		FuncField.showBin(elements[i]);
		cout<<"\t";
		FuncField.showBin(values[i]);
		cout<<"\n";
	}
	return values;
}