/**********************************************
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Summer semester 2016/2017
*
* @author Vasilena Peycheva
* @idnumber 45139
* @task project
* @compiler VC
*
*/

#include <iostream>
#include "Archive.h"


int main(int argc, char** argv)
{
	if (stricmp(argv[1], "-Pack") == 0)
	{
		Archive folder;
		folder.pack(argv[2], argv[3]);
	}
	else if(stricmp(argv[1], "-Unpack") == 0)
	{
		Archive folder;
		folder.unpack(argv[2], argv[3]);
	}
	else
	{
		std::cout << "Not completed function";
	}

	return 0;
}