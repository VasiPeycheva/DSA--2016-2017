#ifndef __EXPRESSION__HEADER__INCLUDED__
#define __EXPRESSION__HEADER__INCLUDED__
#include "Operators.h"
#include "Stack.h"

struct Box
{
	char oper;
	double number;
	bool isNumber = false;
};

class Expression {
public:
	Expression();
	~Expression();

	void loadExpressionFile(const char *);
	void includeOperators(const Operators &);
	void print();

	void toRPN();
	double calculateRPN();

private:
	bool isDigit(char c);
	void validation();

private:
	DynamicArray<Box> expression = DynamicArray<Box>();
	Operators expressionOperators;
	double result;
};

#endif // !__EXPRESSION__HEADER__INCLUDED__

