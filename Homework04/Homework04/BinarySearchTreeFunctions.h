#ifndef __BINARY__SEARCH__TREE__FUNCTIONS__HEADER__INCLUDED__
#define __BINARY__SEARCH__TREE__FUNCTIONS__HEADER__INCLUDED__

#include <iostream>
#include "BinarySearchTree.h"

template <class TYPE, class OTHERTYPE>
inline BinarySearchTree<TYPE,OTHERTYPE>::BinarySearchTree()
	:root(NULL)
{}

template <class TYPE, class OTHERTYPE>
inline BinarySearchTree<TYPE,OTHERTYPE>::~BinarySearchTree()
{
	clean(root);
}

template <class TYPE, class OTHERTYPE>
inline void BinarySearchTree<TYPE,OTHERTYPE>::add(const TYPE & key)
{
	addHelper(root, key);
}

template <class TYPE, class OTHERTYPE>
inline bool BinarySearchTree<TYPE,OTHERTYPE>::remove(const TYPE & key)
{
	if (search(key))
	{
		removeHelper(root, key);
		return true;
	}
	else
		return false;
}

template <class TYPE, class OTHERTYPE>
inline bool BinarySearchTree<TYPE,OTHERTYPE>::search(const TYPE & key)
{
	return searchHelper(root, key);
}

template<class TYPE, class OTHERTYPE>
inline int BinarySearchTree<TYPE, OTHERTYPE>::removeAll(const OTHERTYPE & key)
{
	int cnt = 0;
	while (searchKey(root,key))
	{
		TYPE destroyer = getNode(root,2);
		remove(destroyer);
		cnt++;
	}
	return cnt;
}

template <class TYPE, class OTHERTYPE>
inline void BinarySearchTree<TYPE,OTHERTYPE>::addHelper(node *& root, const TYPE & key)
{
	if (!root)
	{
		root = new node(key);
	}
	else if (key <= root->key)
	{
		addHelper(root->leftChild, key);
	}
	else //(key > root->key)
	{
		addHelper(root->rightChild, key);
	}
}

template <class TYPE, class OTHERTYPE>
inline void BinarySearchTree<TYPE,OTHERTYPE>::removeHelper(node *& root, const TYPE & key)
{
	if (root->key < key)
		removeHelper(root->rightChild, key);
	else if (root->key > key)
		removeHelper(root->leftChild, key);
	else
	{
		if (root->leftChild && root->rightChild)
		{
			node * replace = minKey(root->rightChild);
			root->key = replace->key;
			removeHelper(root->rightChild, replace->key);
		}
		else
		{
			node * destroyer = root;
			if (root->leftChild)
				root = root->leftChild;
			else
				root = root->rightChild;
			delete destroyer;
		}
	}
}

template <class TYPE, class OTHERTYPE>
inline bool BinarySearchTree<TYPE,OTHERTYPE>::searchHelper(node *& root, const TYPE & key)
{
	if (!root)
		return false;
	else if (root->key > key)
		searchHelper(root->leftChild, key);
	else if (root->key < key)
		searchHelper(root->rightChild, key);
	else
		return true;
}

template<class TYPE, class OTHERTYPE>
inline bool BinarySearchTree<TYPE, OTHERTYPE>::searchKey(node *& root, const OTHERTYPE & key)
{
	if (!root)
		return false;
	else if (root->key > key)
		searchKey(root->leftChild, key);
	else if (root->key < key)
		searchKey(root->rightChild, key);
	else
		return true;
}

template<class TYPE, class OTHERTYPE>
inline TYPE & BinarySearchTree<TYPE, OTHERTYPE>::getNode(node *& root, const OTHERTYPE & key)
{
	if (root->key > key)
		getNode(root->leftChild, key);
	else if (root->key < key)
		getNode(root->rightChild, key);
	else
		return root->key;
}

template <class TYPE, class OTHERTYPE>
inline void BinarySearchTree<TYPE,OTHERTYPE>::clean(node *& root)
{
	if (root)
	{
		clean(root->leftChild);
		clean(root->rightChild);
		delete root;
	}
}

#endif // !__BINARY__SEARCH__TREE__FUNCTIONS__HEADER__INCLUDED__
