#ifndef __MIN__HEAP__FUNCTIONS__HEADER__INCLUDED__
#define __MIN__HEAP__FUNCTIONS__HEADER__INCLUDED__

#include "MinHeap.h"

template<class TYPE>
inline void MinHeap<TYPE>::push(const TYPE & element)
{
	heap.push_back(element);
	siftUp();
}

template<class TYPE>
inline TYPE & MinHeap<TYPE>::popMin()
{
	TYPE element = heap[0];
	heap[0] = heap.back();
	heap.pop_back();
	siftDown();
	return element;
}

template<class TYPE>
inline const TYPE & MinHeap<TYPE>::peakMin() const
{
	return heap[0];
}

template<class TYPE>
inline int MinHeap<TYPE>::getSize() const
{
	return heap.size();
}

template<class TYPE>
inline void MinHeap<TYPE>::swap(TYPE & lhs, TYPE &rhs)
{
	TYPE temp = lhs;
	lhs = rhs;
	rhs = temp;
}

template<class TYPE>
inline void MinHeap<TYPE>::siftUp()
{
	int index = heap.size() - 1;
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (heap[parent] > heap[index]) // if the children is smaller we swap the two elements
		{
			swap(heap[parent], heap[index]);
			index = parent;
		}
		else
		{
			break;
		}
	}
}

template<class TYPE>
inline void MinHeap<TYPE>::siftDown()
{
	int index = 0;
	int size = heap.size() - 1;
	while (index < size)
	{
		int child = 2 * index + 1;
		if (child <= size)
		{
			if (child + 1 <= size) // if he has 2 childrens
			{
				if (heap[child] > heap[child + 1]) // we search for the smaller one
					child++;
			}
			if (heap[index] > heap[child]) // if the child is smaller we make it root
			{
				swap(heap[index], heap[child]);
				index = child;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}



#endif // !__MIN__HEAP__FUNCTIONS__HEADER__INCLUDED__
