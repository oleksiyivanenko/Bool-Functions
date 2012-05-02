// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

Function::Function(){
	N = (1<<10)+(1<<7)-1;
	M = (1<<7)+(1<<3)-1;
	el_number = FuncField.getElemNum();
	el = FuncField.getElem();
	countFunction();
}

Function::~Function(){
        if(M_vals != NULL)
        	delete[] M_vals;
        if(N_vals != NULL)
        	delete[] N_vals;
}

void Function::countFunction(){
	N_vals = new int[el_number];
	M_vals = new int[el_number];
	ofstream N_func;
	N_func.open("N_func.txt");
	for(int i = 0; i < el_number; i++){
		N_vals[i] = FuncField.gornerPow(el[i],N);
		N_func << el[i]<<"\t"<<N_vals[i]<<"\n";
	}
	N_func.close();
	ofstream M_func;
	M_func.open("M_func.txt");
	for(int i = 0; i < el_number; i++){
		M_vals[i] = FuncField.gornerPow(el[i],M);
		M_func << el[i]<<"\t"<<M_vals[i]<<"\n";
	}
	M_func.close();
}