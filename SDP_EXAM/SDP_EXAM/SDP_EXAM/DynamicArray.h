#ifndef __DYNAMIC__ARRAY__
#define __DYNAMIC__ARRAY__
#include <iostream>
using namespace std;

template<class TYPE>
class DynamicArray
{
public:
	// Г4
	DynamicArray(int);
	~DynamicArray();
	DynamicArray(const DynamicArray &);
	DynamicArray& operator=(const DynamicArray &);
public:
	int binarySearch(const TYPE &);
	void selectionSort();
	bool isSorted() const;
	void print() const;
	int getSize() const {return size;}

	void add(const TYPE &);
	bool remove(int);

	const TYPE& operator[](int) const;
	TYPE& operator[](int);
private:
	void clean();
	void copy(const DynamicArray<TYPE> &);
	void resize();
private:
	TYPE* data;
	int capacity;
	int size;
};

#include "DynamicArrayFunctions.h"

#endif // !__DYNAMIC__ARRAY__
