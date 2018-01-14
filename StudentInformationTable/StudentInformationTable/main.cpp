/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2017/2018
*
* @author Vasilena Peycheva
* @idnumber 45139
* @task 2
* @compiler VC
*
*/

#include <iostream>
#include <fstream>
#include "Student.h"
#include "DynamicArray.h"
#include "StudentsTable.h"

int main(int argc, char *argv[])
{
	StudentsTable table(argv[1]);
	table.sortBy(argv[2], argv[3]);

	return 0;
}
