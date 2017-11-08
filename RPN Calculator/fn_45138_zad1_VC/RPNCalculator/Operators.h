#ifndef __OPERATORS__HEADER__INCLUDED__
#define	__OPERATORS__HEADER__INCLUDED__
#include "DynamicArray.h"
#include <fstream>
#include <iostream>

static const int maxOperators = 8;

struct Operator
{
	char symbol;
	char oper;
	short associativity;
};

class Operators
{
public:
	Operators() {}
	~Operators() {}
	void LoadOperatorsFromFile(char * file);
	double doOperation(double, char, double);
	bool isOperator(char c);
private:
	DynamicArray<Operator> operators = DynamicArray<Operator>(maxOperators);
};

inline bool Operators::isOperator(char op)
{
	int operatorsCnt = operators.getSize();
	for (int i = 0; i < operatorsCnt; i++)
		if (op == operators[i].symbol)
			return true;
	return false;
}

inline double Operators::doOperation(double a, char op, double b)
{
	double result;
	int operatorsCnt = operators.getSize();
	for (int i = 0; i <operatorsCnt; i++)
	{
		if (op == operators[i].symbol)
		{
			switch (operators[i].oper)
			{
			case'+': result = a + b; return result;
			case'-': result = a - b; return result;
			case'*': result = a * b; return result;
			case'/': if (b == 0) throw "invalid expression"; result = a / b; return result;
			}
		}

	}
}

inline void Operators::LoadOperatorsFromFile(char * file)
{
	fstream in(file, ios::in);
	if (!in.is_open())
	{
		std::cerr << "Error opening the file! \n";
	}
	while (!in.eof())
	{
		Operator p;
		in >> p.symbol >> p.oper >> p.associativity;
		operators.add(p);
	}
	in.close();
}


#endif // !__OPERATORS__HEADER__INCLUDED__
