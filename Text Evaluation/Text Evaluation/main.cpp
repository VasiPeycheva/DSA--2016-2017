/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Vasilena Peycheva
* @idnumber 45139
* @task 1
* @compiler VC
*
*/

#include "Dictionary.h"
#include "TextProcessor.h"

int main(int argc, char**argv)
{
	TextProcessor proc;
	proc.createDictionary(argv[1]);
	for (size_t i = 2; i < argc; i++)
	{
		try 
		{
			proc.result(argv[i]);
		}
		catch (...)
		{
			std::cerr << "Error";
		}
	}
	return 0;
}
