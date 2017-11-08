#ifndef __BINARY__SEARCH__TREE__HEADER__INCLUDED__
#define __BINARY__SEARCH__TREE__HEADER__INCLUDED__
#include <stddef.h>

template <class TYPE, class OTHERTYPE>
class BinarySearchTree;

template <class TYPE, class OTHERTYPE>
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void add(const TYPE &);
	bool remove(const TYPE &);
	bool search(const TYPE &);
	int removeAll(const OTHERTYPE &);

private:
	BinarySearchTree(const BinarySearchTree &);
	BinarySearchTree& operator=(const BinarySearchTree &);

private:

	struct node
	{
		TYPE key;
		node * leftChild;
		node * rightChild;

		node(const TYPE & input, node * left = NULL, node * right = NULL)
			:key(input)
			, leftChild(left)
			, rightChild(right)
		{}
		
	};
		node * minKey(node * root)
		{
			while (root->leftChild)
				root = root->leftChild;
			return root;
		}

private:
	void addHelper(node *&, const TYPE &);
	void removeHelper(node *&, const TYPE &);
	bool searchHelper(node *&, const TYPE &);

	bool searchKey(node *&, const OTHERTYPE &);
	TYPE& getNode(node*&, const OTHERTYPE &);

	void clean(node *&);

private:
	node * root;
};

#include "BinarySearchTreeFunctions.h"

#endif // !__BINARY__SEARCH__TREE__HEADER__INCLUDED__
