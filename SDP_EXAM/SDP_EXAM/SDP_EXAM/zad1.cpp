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

struct node
{
	int key;
	node * pNext;
	node(int element, node * nextNode = NULL)
		:key(element)
		,pNext(nextNode)
	{}
};

void addNode(node *& pHead, int key)
{
	if (!pHead)
	{
		pHead = new node(key);
	}
	else
	{
		node * iter = pHead;
		while (iter->pNext)
			iter = iter->pNext;
		iter->pNext = new node(key);
	}
}

void clean(node *& pHead)
{
	if (!pHead)
		return;

	node * destroyer = pHead;
	while (pHead)
	{
		pHead = pHead->pNext;
		delete destroyer;
		destroyer = pHead;
	}
}

void insertKey(node *& pHead, int key)
{
	node * insert = new node(key);

	//insert in empty list
	if (!pHead)
	{
		pHead = insert;
		return;
	}

	//push front
	if (pHead->key >= key)
	{
		insert->pNext = pHead;
		pHead = insert;
	}
	else
	{
		node * iter = pHead->pNext;
		node * connector = pHead;
		
		//if we have only one node (push back)
		if (!iter)
		{
			connector->pNext = insert;
			return;
		}

		while (iter->key < key && iter->pNext)
		{
			iter = iter->pNext;
			connector = connector->pNext;
		}

		//push back
		if (!iter->pNext)
		{
			iter->pNext = insert;
		}
		//insert between two nodes
		else       
		{
			connector->pNext = insert;
			insert->pNext = iter;
		}
	}

}

int getSize(node *& pHead)
{
	node * iter = pHead;
	int size = 0;
	while (iter)
	{
		iter = iter->pNext;
		size++;
	}
	return size;
}

void makeSection(node *& lhs, node*& rhs, node *& result)
{
	node * iterLhs = lhs;
	node * iterRhs = rhs;
	while (iterLhs)
	{
		while (iterRhs)
		{
			if (iterLhs->key == iterRhs->key)
			{
				insertKey(result, iterRhs->key);
				break;
			}
			iterRhs = iterRhs->pNext;
		}
		iterLhs = iterLhs->pNext;
		iterRhs = rhs;
	}
}

node * intersection(node *& lhs, node*& rhs)
{
	node * section1 = NULL;
	node * section2 = NULL;

	//the intersection with the empty set is the empty set
	if (!lhs || !rhs)
	{
		return NULL;
	}

	//we make two intersections and choose the smallest so we could avoid repetitions
	makeSection(lhs, rhs, section1);
	makeSection(rhs, lhs, section2);
	if (getSize(section1) <= getSize(section2))
	{
		clean(section2);
		return section1;
	}
	else
	{
		clean(section1);
		return section2;
	}
}

//int main()
//{
//	node * linkedList1 = NULL;
//	addNode(linkedList1, 2);
//	addNode(linkedList1, 2);
//	addNode(linkedList1, 5);
//	addNode(linkedList1, 4);
//
//	node * linkedList2 = NULL;
//	addNode(linkedList2, 2);
//	addNode(linkedList2, 2);
//	addNode(linkedList2, 3);
//
//	node * result = intersection(linkedList1, linkedList2);
//
//	clean(linkedList1);
//	clean(linkedList2);
//	clean(result);
//}