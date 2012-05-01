#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "field.h"

class Function{
public:
	Function();
	~Function();
	int* countFunction(int);
protected:
	int N, M;
	int *N_vals, *M_vals;
	Field FuncField; 
};
#endif