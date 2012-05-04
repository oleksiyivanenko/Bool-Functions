// function.h: Oleksiy Ivanenko
// Description: Header file for Function class

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "field.h"
#include <iomanip>
#include <stdlib.h>

class Function{
public:
	Function();
	Function(int);
	~Function();

	void analyze();
	void countFunction();
	void disbalance();
	void walsh();
	void errorCoef();
	void avalancheEffect();
	void nonlinearity();
	void immunity();
	int weight(int);
	void algDegree();
	int insertBit(int,int,int);
protected:
	int N, el_number, deg;
	int *vals, *field_elements, *disbal, *err_coef, *non_lin, *imm;
	int **walsh_coef;
	Field FuncField;
};
#endif