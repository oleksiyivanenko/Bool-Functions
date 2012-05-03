// function.h: Oleksiy Ivanenko
// Description: Header file for Function class

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "field.h"

class Function{
public:
	Function();
	Function(int);
	~Function();

	void countFunction();
	void disbalance();
	void walsh();
	void errorCoef();
	void avalancheEffect();
protected:
	int N, el_number, deg;
	int *vals, *field_elements, *disbal, *err_coef;
	int **walsh_coef;
	Field FuncField;
};
#endif