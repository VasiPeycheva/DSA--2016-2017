#ifndef __NODES__HEADER__INCLUDED__
#define __NODES__HEADER__INCLUDED__

#include <iostream>

struct node
{
	char symbol;
	node * left;
	node * right;

	node(char symb = ' ', node * leftChild = NULL, node * rightChild = NULL)
		:symbol(symb)
		, left(leftChild)
		, right(rightChild)
	{}
	
};

void cleanNode(node *& root);

struct weightedNode
{
	node * root;
	unsigned int weight;
	weightedNode(unsigned int value = 0, node * ptr = NULL)
		:root(ptr)
		, weight(value)
	{}
};

bool operator<(const weightedNode& lhs, const weightedNode rhs);

bool operator>(const weightedNode& lhs, const weightedNode rhs);


#endif // !__NODES__HEADER__INCLUDED__
