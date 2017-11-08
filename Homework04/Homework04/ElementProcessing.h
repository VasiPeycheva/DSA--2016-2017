#ifndef __ELEMENT__PROCESSING__HEADER__INCLUDED__
#define __ELEMENT__PROCESSING__HEADER__INCLUDED__
#include "BinarySearchTree.h"
#include "Element.h"
#include "DynamicArray.h"

class ElementProcessing
{
public:
	ElementProcessing() {}
	~ElementProcessing() {}

	void loadFile(const char *);
	void add(int, const char *);
	bool remove(int, const char *);
	bool search(int, const char *);
	int removeall(int);

private:
	ElementProcessing(const ElementProcessing &);
	ElementProcessing& operator=(const ElementProcessing &);

private:
	void buildTree(int,int);

private:
	BinarySearchTree<Element,int> binaryTree;
	DynamicArray<Element> buffer;
};

#endif // !__ELEMENT__PROCESSING__HEADER__INCLUDED__
