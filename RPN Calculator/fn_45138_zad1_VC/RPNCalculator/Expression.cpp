#include "Expression.h"
#include <iomanip>

const int initialSize = 3;

Expression::Expression()
	:expression(initialSize)
{}

Expression::~Expression()
{}

void Expression::includeOperators(const Operators & input)
{
	expressionOperators = input;
}

void Expression::loadExpressionFile(const char * file)
{
	char c;
	Box number, operation;
	ifstream in(file, ios::in);

	if (in.is_open())
	{
		while (!in.eof())
		{
			c = in.get();
			if (c == '\n')
				break;
			if (isDigit(c))
			{
				in.unget();
				in >> number.number;
				number.isNumber = true;
				expression.add(number);
			}
			else if (expressionOperators.isOperator(c) && in.peek() == ' ')
			{
				in.unget();
				in >> operation.oper;
				expression.add(operation);
			}
			else if (c == '-')
			{
				if (isDigit(in.peek()))
				{
					in.unget();
					in >> number.number;
					number.isNumber = true;
					expression.add(number);
				}
				else if (expressionOperators.isOperator(c) && in.peek() == ' ')
				{
					in.unget();
					in >> operation.oper;
					expression.add(operation);
				}
				else
				{
					in.close();
					throw "invalid expression";
				}
			}
			else
			{
				if (c != ' ')
				{
					in.close();
					throw "invalid expression";
				}

			}
		}
	}
}

void Expression::toRPN()
{
	validation();
	int size = expression.getSize();

	Stack<Box> operators;
	DynamicArray<Box> postfixExpresion(size);
	DynamicArray<bool> helpVector(size);
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		//is operator we only push it into the stack
		if (!expression[i].isNumber)
		{
			operators.push(expression[i]);
			helpVector[++index] = 0;
		}
		else
		{
			if (helpVector[index] == 1)
			{
				postfixExpresion.add(expression[i]);
				postfixExpresion.add(operators.peek());
				operators.pop();
				helpVector[index--] = 0;
				while ((helpVector[index] == 1))
				{
					postfixExpresion.add(operators.peek());
					operators.pop();
					helpVector[index--] = 0;
				}
				helpVector[index] = 1;
			}
			else
			{
				postfixExpresion.add(expression[i]);
				helpVector[index] = 1;
			}
		}
	}

	expression = postfixExpresion;
}

double Expression::calculateRPN()
{
	Stack<double> stack;
	int iter = expression.getSize() / 2; 
	double var1, var2;
	int j = 0;

	for (int i = 0; i <iter; i++)
	{
		while (expression[j].isNumber)
		{
			stack.push(expression[j].number);
			j++;
		}
		if (!expression[j].isNumber)
		{
			var2 = stack.peek();
			stack.pop();
			var1 = stack.peek();
			stack.pop();
			result = expressionOperators.doOperation(var1, expression[j].oper, var2);
			stack.push(result);
			j++;
		}
	}
	if (stack.getSize() != 1)
		throw "Invalid expression!";
	return result;
}

void Expression::print()
{
	int size = expression.getSize();
	for (int i = 0; i < size; i++)
	{
		if (expression[i].isNumber)
			cout << expression[i].number << " ";
		else
			cout << expression[i].oper << " ";
	}
	cout <<"\n" << fixed << setprecision(5) << result << "\n";
}

void Expression::validation()
{
	int numCnt = 0; 
	int operatorCnt = 0;
	int size = expression.getSize();
	if (expression[0].isNumber)
		throw "invalid expression";
	for (int i = 0; i <size; i++)
	{
		if (expression[i].isNumber)
			numCnt++;
		else
			operatorCnt++;
	}
	if (!(numCnt == operatorCnt + 1))
		throw "invalid expression";

	if(!expression[size - 2].isNumber || !expression[size - 1].isNumber)
		throw "invalid expression";

}


bool Expression::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

