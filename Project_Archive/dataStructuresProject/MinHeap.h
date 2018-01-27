#ifndef __MIN__HEAP__HEADER__INCLUDED__
#define __MIN__HEAP__HEADER__INCLUDED__
#include <vector>

template <class TYPE>
class MinHeap
{
public:
	MinHeap() {}
	~MinHeap() {}
	MinHeap(const MinHeap &) {}
	MinHeap& operator=(const MinHeap &) {}

	void push(const TYPE&);
	TYPE& popMin();
	const TYPE& peakMin() const;

	int getSize() const;

private:
	void swap(TYPE&, TYPE&);
	void siftUp();
	void siftDown();

private:
	std::vector <TYPE> heap;

};

#include "MinHeapFunctions.h"

#endif // !__MIN__HEAP__HEADER__INCLUDED__

