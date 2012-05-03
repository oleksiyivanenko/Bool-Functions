// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

// Default constructor
Function::Function(){
	N = 1151;
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	field_elements = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
	errorCoef();
	avalancheEffect();
}

// Constructor which gets function degree
Function::Function(int funcDeg){
	N = funcDeg;
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	field_elements = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
	errorCoef();
	avalancheEffect();
}

// Destructor
Function::~Function(){
        if(vals != NULL)
        	delete[] vals;
        if(disbal != NULL)
        	delete[] disbal;
        if(walsh_coef != NULL)
        	for(int i = 0; i < deg;i++)
        		delete[] walsh_coef[i];
        	delete[] walsh_coef;
        if(err_coef != NULL)
        	delete[] err_coef;
}

// Counts functions table of truth
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

// Counts disbalance of function
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

// Counts Walsh coefficients
void Function::walsh(){
	cout<<"\n*** Walsh ***\n";
	walsh_coef = new int *[deg];
	for(int i = 0; i < deg;i++){
		walsh_coef[i] = new int[el_number];
	}
	int x = 1;
	for(int i = 0; i < deg; i++){
		for(int j = 0; j < el_number; j++){
			// walsh_coef[i][j] = 1;
			(vals[j] & x) != 0 ? walsh_coef[i][j] = -1 : walsh_coef[i][j] = 1;
		}
		x <<= 1;
	}
	x >>= 1; 
	for(int i = 0;i < deg;i++){
		for(int j = 0;j < el_number;j++){
			int u0 = field_elements[j];
			int u1 = u0 ^ x;
			if((u1 & x) == 0){
				int temp = u0;
				u0 = u1;
				u1 = temp;
			}
			// for(int k = 0;k < deg;k++){
				int tmp = walsh_coef[i][u0];
				walsh_coef[i][u0] = tmp + walsh_coef[i][u1];
				walsh_coef[i][u1] = tmp - walsh_coef[i][u1];
			// }
		}
		x >>= 1;
	}
	for(int i = 0; i < deg; i++){
		for(int j = 0; j < el_number; j++){
			cout<<walsh_coef[i][j]<<" ";
		}
		cout<<"\n";
	}

}

// Counts error spread coefficients of functions
void Function::errorCoef(){
	cout<<"\n*** Error spread coefficient ***\n";
	int x = 1;
	err_coef = new int[deg];
	for(int i = 0;i < deg; i++){
		err_coef[i] = 0;
		for(int j = 0;j < el_number;j++){
			int temp = field_elements[j]^x;
			int tmp1, tmp2;
			(vals[j] & x) != 0 ? tmp1 = 1 : tmp1 = 0;
			(FuncField.gornerPow(temp,N) & x) != 0 ? tmp2 = 1 : tmp2 = 0;
			err_coef[i] += (tmp1 ^ tmp2);
		}
		cout<<"Error spread coefficient "<<i<<": "<<err_coef[i]<<"\n";
		x <<= 1;
	}
}

// Counts avalanche effect of functions
void Function::avalancheEffect(){
	cout<<"\n*** Lav Effect ***\n";
	int k = 1 << (deg - 1);
	int top = k + 350;
	int bottom = k - 350;
	int x = 0;
	for(int i = 0;i < deg; i++){
		if(err_coef[i] >= bottom && err_coef[i] <= top){
			cout<<"Function "<<i<<" has strict avalanche effect\n";
			x++;
		}
	}
	if(x == deg){
		cout<<"Function has strict zero-order avalanche effect\n";
	}
}