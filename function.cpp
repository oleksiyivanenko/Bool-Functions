// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

Function::Function(){
	N = (1<<10)+(1<<7)-1;
	M = (1<<7)+(1<<3)-1;
	el_number = FuncField.getElemNum();
	N_vals = new int[el_number];
	M_vals = new int[el_number];
	countFunction();
}

Function::~Function(){
        if(M_vals != NULL)
        	delete [] M_vals;
        if(N_vals != NULL)
        	delete [] N_vals;
}

void Function::countFunction(){
	int *el;
	el = FuncField.getElem();
	for(int i = 0;i < el_number;i++){
		N_vals[i] = FuncField.gornerPow(el[i],N);
		M_vals[i] = FuncField.gornerPow(el[i],M);
	}
	delete[] el;
}