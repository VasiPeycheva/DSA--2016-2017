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
#include <iostream>
#include "BinarySearchTree.h"
#include "ElementProcessing.h"

static const int maxLenBuffer = 1024;
static const int maxLenCommand = 16;

using std::cin;
using std::cout;
int main(int argc, char** argv)
{

	ElementProcessing processData;
	processData.loadFile(argv[1]);
	int key;
	char * data;
	char buffer[maxLenBuffer];
	char command[maxLenCommand];
	while (true)
	{
		cin >> command;

		if (stricmp("add", command) == 0)
		{
			cin >> key;
			cin.getline(buffer, maxLenBuffer);
			data = new char[strlen(buffer) + 1];
			strcpy(data, buffer);
			processData.add(key, data);
			delete[] data;

		}
		else if (stricmp("remove", command) == 0)
		{
			cin >> key;
			cin.getline(buffer, maxLenBuffer);
			data = new char[strlen(buffer) + 1];
			strcpy(data, buffer);
			cout << processData.remove(key, data) << '\n';
			delete[] data;
		}
		else if (stricmp("removeall", command) == 0)
		{
			cin >> key;
			cout << processData.removeall(key) << '\n';
		}
		else if (stricmp("search", command) == 0)
		{
			cin >> key;
			cin.getline(buffer, maxLenBuffer);
			data = new char[strlen(buffer) + 1];
			strcpy(data, buffer);
			cout << processData.search(key, data) << '\n';
			delete[] data;
		}
		else
		{
			break;
		}
	}

	
	return 0;
}
