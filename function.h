// function.h: Oleksiy Ivanenko
// Description: Header file for Function class

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <fstream>
#include "field.h"

class Function{
public:
	Function();
	~Function();

	void countFunction();
	void disbalance();
protected:
	int N, M, el_number, deg;
	int *N_vals, *M_vals, *el, *disb_N, *disb_M;
	Field FuncField;
};
#endif