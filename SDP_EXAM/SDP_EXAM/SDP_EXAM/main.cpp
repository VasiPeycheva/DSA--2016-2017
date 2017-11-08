/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Vasilena Peycheva
* @idnumber 45139
* @task 2
* @compiler VC
*
*/

#include "zad2.h"


int main(int argc, char**argv)
{
	BinarySearchTree tree;
	int N = 0;
	tree.deserialization("argv[1]");
	std::cin >> N;
	std::cout << tree.checkSubtree(N);
	tree.serialization("argv[1]");
	return 0;
}