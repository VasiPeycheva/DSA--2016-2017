/**********************************************
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2016/2017
*
* @author Vasilena Peycheva
* @idnumber 45139
* @task 1
* @compiler VC
*
*/
#include <iostream>
#include "Expression.h"

using namespace std;

int main(int argc, char ** argv)
{

	try
	{
		Operators load;
		load.LoadOperatorsFromFile(argv[2]);
		Expression s;
		s.includeOperators(load);
		s.loadExpressionFile(argv[1]);
		s.toRPN();
		s.calculateRPN();
		s.print();
	}
	catch (...)
	{
		cout << "Error \n";
	}
	return 0;
}