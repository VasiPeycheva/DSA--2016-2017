#ifndef __ZAD2__HEADER__INCLUDED__
#define __ZAD2__HEADER__INCLUDED__

#include "DynamicArray.h"
#include <vector>

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void serialization(const char *);
	void deserialization(const char *);

	void addElement(int key);
	int checkSubtree(int);

private:
	struct node
	{
		int key;
		int childrenCnt;
		node * rightChild;
		node * leftChild;
		node(int value, int childrens = 1, node * right = NULL, node * left = NULL)
			:key(value)
			, childrenCnt(childrens)
			, rightChild(right)
			, leftChild(left)
		{}
	};

private:
	BinarySearchTree(const BinarySearchTree &);
	BinarySearchTree& operator=(const BinarySearchTree &);

	void clean(node *&);
	void add(node *&, int);
	int getSubTreeCnt(node *&, int);

private:
	node * root;
	vector<int> buffer;
	bool isInserted;
};

#endif // !__ZAD2__HEADER__INCLUDED__
