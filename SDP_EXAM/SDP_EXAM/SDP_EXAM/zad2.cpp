#include <fstream>
#include <vector>
#include "zad2.h"

BinarySearchTree::BinarySearchTree()
	:root(NULL)
	, buffer(NULL)
	, isInserted(false)
{}

BinarySearchTree::~BinarySearchTree()
{
	clean(root);
}

void BinarySearchTree::serialization(const char * fileName)
{
	std::ofstream out(fileName, std::ios::trunc);
	int size = buffer.size() - 1;
	for (size_t i = 0; i < size; i++)
	{
		out << buffer[i] << " ";
	}
	out.close();
}

void BinarySearchTree::deserialization(const char * fileName)
{
	int element;
	std::ifstream in(fileName);
	while (!in.eof())
	{
		in >> element;
		buffer.push_back(element);
		addElement(element);
	}
	in.close();
}

int BinarySearchTree::checkSubtree(int n)
{
	return getSubTreeCnt(root, n);
}

void BinarySearchTree::addElement(int key)
{
	add(root, key);
}

void BinarySearchTree::add(node *& root, int key)
{
	isInserted = false;

	if (!root)
	{
		root = new node(key);
		isInserted = true;
	}
	else if (key < root->key)
	{
		add(root->leftChild,key);
		if(isInserted)
			root->childrenCnt++;
	}
	else if (key > root->key)
	{
		add(root->rightChild, key);
		if (isInserted)
			root->childrenCnt++;
	}
	else
	{
		return;
	}
}

void BinarySearchTree::clean(node *& root)
{
	if (root)
	{
		clean(root->leftChild);
		clean(root->rightChild);
		delete root;
	}
}

int BinarySearchTree::getSubTreeCnt(node *& root, int n)
{
	if (root->childrenCnt > n)
	{
		return (getSubTreeCnt(root->leftChild, n) + getSubTreeCnt(root->rightChild, n));
	}
	else if (root->childrenCnt == n)
		return 1;
	else
		return 0;
}


