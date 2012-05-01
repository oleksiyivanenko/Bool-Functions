// function.h: Oleksiy Ivanenko
// Description: Header file for Function class

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "field.h"

class Function{
public:
	Function();
	~Function();

	void countFunction();
protected:
	int N, M, el_number;
	int *N_vals, *M_vals;
	Field FuncField; 
};
#endif