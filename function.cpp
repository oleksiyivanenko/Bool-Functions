// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

Function::Function(){
	N = (1<<10)+(1<<7)-1;
	M = (1<<7)+(1<<3)-1;
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	el = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
}

Function::~Function(){
        if(M_vals != NULL)
        	delete[] M_vals;
        if(N_vals != NULL)
        	delete[] N_vals;
        if(disb_N != NULL)
        	delete[] disb_N;
        if(disb_M != NULL)
        	delete[] disb_M;
}

void Function::countFunction(){
	N_vals = new int[el_number];
	M_vals = new int[el_number];
	cout<<"\n*** Functions calculation ***\n";
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
	cout<<"Tables of truth are calculated\n";
}

void Function::disbalance(){
	int x = 1 << (deg - 1);
	disb_M = new int[deg];
	disb_N = new int[deg];
	cout<<"\n*** Disbalance ***\n";
	for(int i = 0;i < deg;i++){
		disb_N[i] = 0;
		disb_M[i] = 0;
		for(int j = 0; j < el_number; j++){
			if((x & N_vals[j]) == 0){
				disb_N[i]++;
			}
			else{
				disb_N[i]--;
			}
			if((x & M_vals[j]) == 0){;
				disb_M[i]++;
			}
			else{
				disb_M[i]--;
			}
		}
		x >>= 1;
		cout<<"N disb "<<i<<" "<<disb_N[i]<<" M disb "<<i<<" "<<disb_M[i]<<"\n";
	}
}

void Function::walsh(){
	
}