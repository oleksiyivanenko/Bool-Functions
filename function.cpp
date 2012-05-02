// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

Function::Function(){
	N = 1151;
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	field_elements = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
}

Function::Function(int funcDeg){
	N = funcDeg;
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	field_elements = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
}

Function::~Function(){
        if(vals != NULL)
        	delete[] vals;
        if(disbal != NULL)
        	delete[] disbal;
        if(walsh_coef != NULL)
        	for(int i = 0; i < el_number;i++)
        		delete[] walsh_coef[i];
        	delete[] walsh_coef;
}

void Function::countFunction(){
	vals = new int[el_number];
	cout<<"\n*** Function calculation ***\n";
	for(int i = 0; i < el_number; i++){
		vals[i] = FuncField.gornerPow(field_elements[i],N);
		cout<<i<<"\t";
		FuncField.showBin(field_elements[i]);
		cout<<"\t";
		FuncField.showBin(vals[i]);
		cout<<"\n";
	}
	cout<<"Table of truth calculated\n";
}

void Function::disbalance(){
	int x = 1;
	disbal = new int[deg];
	cout<<"\n*** Disbalance ***\n";
	for(int i = 0;i < deg;i++){
		disbal[i] = 0;
		for(int j = 0; j < el_number; j++){
			if((x & vals[j]) == 0){
				disbal[i]++;
			}
			else{
				disbal[i]--;
			}
		}
		x <<= 1;
		cout<<"Disbalance of "<<i<<" element is:"<<disbal[i]<<"\n";
	}
}

void Function::walsh(){
	cout<<"\n*** Walsh ***\n";
	walsh_coef = new int *[el_number];
	for(int i = 0; i < el_number;i++){
		walsh_coef[i] = new int[deg];
	}
	//for(int i = 0;i < el_number;i++){
	//	if(vals[i])
	//}
}