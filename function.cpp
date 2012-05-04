// function.cpp: Oleksiy Ivanenko
// Description: Methods for analyze boolean functions

#include "function.h"

// Default constructor
Function::Function(){
	N = 1151;
}

// Constructor which gets function degree
Function::Function(int funcDeg){
	N = funcDeg;	
}

// Destructor
Function::~Function(){
        if(vals != NULL)
        	delete[] vals;
        if(disbal != NULL)
        	delete[] disbal;
        if(walsh_coef != NULL){
        	for(int i = 0; i < deg;i++)
        		delete[] walsh_coef[i];
        	delete[] walsh_coef;
        }
        if(err_coef != NULL){
        	for(int i = 0; i < deg;i++)
        		delete[] err_coef[i];
        	delete[] err_coef;
        }
        if(non_lin != NULL)
        	delete[] non_lin;
        if(imm != NULL)
        	delete[] imm;
}

// Alanyze function for all cryptography parameters
void Function::analyze(){
	el_number = FuncField.getElemNum();
	deg = FuncField.getDeg();
	field_elements = FuncField.getElem();
	countFunction();
	disbalance();
	walsh();
	nonlinearity();
	immunity();
	algDegree();
	errorCoef();
	avalancheEffect();
}

// Counts functions table of truth
void Function::countFunction(){
	vals = new int[el_number];
	cout<<"\n*** Truth Table ***\n";
	cout<<"-----------------------------------"<<endl;
	cout<<setw(9)<<"Desimal"<<setw(20)<<"Binary form"<<setw(16)<<"F(x)"<<endl;
	for(int i = 0; i < el_number; i++){
		vals[i] = FuncField.gornerPow(field_elements[i],N);
		cout<<setw(9)<<i;
		FuncField.showBin(field_elements[i]);
		cout<<"    ";
		FuncField.showBin(vals[i]);
		cout<<"\n";
	}
}

// Counts disbalance of function
void Function::disbalance(){
	int x = 1;
	disbal = new int[deg];
	cout<<"\n*** Disbalance ***\n";
	cout<<"--------------------"<<endl;
	cout<<setw(6)<<"f(x)"<<setw(10)<<"Disbalance"<<endl;
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
		disbal[i] = abs(disbal[i]);
		x <<= 1;
		cout<<setw(6)<<i<<setw(10)<<disbal[i]<<endl;
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
			(vals[j] & x) != 0 ? walsh_coef[i][j] = -1 : walsh_coef[i][j] = 1;
		}
		x <<= 1;
	} 
	for(int i = 0;i < deg;i++){
		for(int j = 0;j < deg;j++){
			for(int k = 0;k < el_number/2;k++){
				int u0 = insertBit(k,j,0);
				int u1 = insertBit(k,j,1);
				int tmp = walsh_coef[i][u0];
				walsh_coef[i][u0] = tmp + walsh_coef[i][u1];
				walsh_coef[i][u1] = tmp - walsh_coef[i][u1];
			}
			
		}	
	}
	cout<<"Walsh coefficients counted!"<<endl;
	// for(int i = 0; i < deg; i++){
	// 	for(int j = 0; j < el_number; j++){
	// 		cout<<walsh_coef[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

}

int Function::insertBit(int x,int pos,int i){
	return ((x >> pos) << (pos+1)) | ((i & 1) << pos) | (x & ((1<<pos)-1));
}

// Counts error spread coefficients of functions
void Function::errorCoef(){
	cout<<"\n*** Error spread coefficients ***";
	// Memory allocation
	err_coef = new int *[deg];
	for(int i = 0;i < deg;i++){
		err_coef[i] = new int[deg];
	}
	int x = 1;
	int y = 1;
	// For every coordinate function
	for(int i = 0;i < deg; i++){
		cout<<"\nError spread coefficients for f(x)"<<i<<endl;
		cout<<"-----------------------------------"<<endl;
		cout<<setw(10)<<"Bit"<<setw(15)<<"Error spread"<<setw(10)<<"Bias"<<endl;
		x = 1;
		// For every variable in function
		for(int k = 0;k < deg; k++){
			err_coef[i][k] = 0;
			// For every value of function
			for(int j = 0;j < el_number;j++){
				int tmp1, tmp2;
				(vals[j] & y) != 0 ? tmp1 = 1 : tmp1 = 0;
				(vals[j^x] & y) != 0 ? tmp2 = 1 : tmp2 = 0;
				err_coef[i][k] += (tmp1 ^ tmp2);
			}
			double bias;
			bias = fabs(100*((double)err_coef[i][k]-16384)/16384);
			x <<= 1;
			cout<<setw(10)<<k<<setw(15)<<err_coef[i][k]<<setw(8)<<bias<<setw(2)<<" %"<<endl;
		}
		y <<= 1;
	}
}

// Counts avalanche effect of functions
void Function::avalancheEffect(){
	cout<<"\n*** Avalanche Effect ***\n";
	cout<<"---------------------------\n";
	int k = 1 << (deg - 1);
	int x = 0;
	for(int i = 0;i < deg; i++){
		int y = 0;
		cout<<"\nAvalanche effect for f(x)"<<i<<endl;
		cout<<setw(6)<<"Bit"<<setw(6)<<"Strict"<<endl;
		for(int j = 0;j < deg; j++){
			cout<<setw(6)<<j;
			if(err_coef[i][j] == k){
				cout<<setw(6)<<"+"<<endl;
				y++;
			}
			else{
				cout<<setw(6)<<"-"<<endl;
			}
		}
		if(y == deg){
			cout<<"Function f(x)"<<i<<" has strict avalanche effect\n";
			x++;
		}
		else{
			cout<<"Function f(x)"<<i<<" has non strict avalanche effect\n";
		}
	}
	if(x == deg){
		cout<<"\nFunction F(x) has strict zero-order avalanche effect\n";
	}
	else{
		cout<<"\nFunctions F(x) has't strict zero-order avalanche effect\n";
	}
}

void Function::nonlinearity(){
	cout<<"\n*** Nonlinearity ***\n";
	cout<<"----------------------\n";
	cout<<setw(6)<<"f(x)"<<setw(12)<<"Nonlinearity"<<endl;
	non_lin = new int[deg];
	for(int i = 0;i < deg; i++){
		int max = 0;
		for(int j = 0;j < el_number;j++){
			if(abs(walsh_coef[i][j]) > max){
				max = walsh_coef[i][j];
			}
		}
		non_lin[i] = (1 << (deg - 1)) - max/2;
		cout<<setw(6)<<i<<setw(12)<<non_lin[i]<<endl;
	}
}

void Function::immunity(){
	cout<<"\n*** Correlation Immunity ***\n";
	cout<<"--------------------\n";
	cout<<setw(6)<<"f(x)"<<setw(5)<<"Order"<<endl;
	imm = new int[deg];
	// Counts weight of every input
	int *wtf;
	wtf = new int[el_number];
	for(int i = 0;i < el_number; i++){
		wtf[i] = weight(i);
	}

	bool flag = true;
	for(int i = 0;i < deg;i++){
		flag = true;
		for(int k = 0; k <= deg; k++){
			for(int j = 0;j < el_number;j++){
				if(k == wtf[j]){
					if(walsh_coef[i][j] != 0){
						flag = false;
						break;
					}
				}
			}
			if(!flag){
				imm[i] = k-1;
				break;
			}
		}
		cout<<setw(6)<<i<<setw(5)<<imm[i]<<endl;
	}
	delete[] wtf;
}

// Counts weight
int Function::weight(int a){
	int wt = 0;
	while(a != 0){
		if((a & 1) != 0 ){
			wt++;
		}
		a >>= 1;
	}
	return wt;
}

void Function::algDegree(){
	cout<<"\n*** Algebraic degree ***\n";
	for(int i = 0;i < deg; i++){
		int algDeg;
		if(disbal[i] == 0){
			algDeg = deg - imm[i] -1;
		}
		else{
			algDeg = deg - imm[i];
		}
		cout<<"Algebraic degree of "<<i<<" function is "<<algDeg<<"\n";
	}
}