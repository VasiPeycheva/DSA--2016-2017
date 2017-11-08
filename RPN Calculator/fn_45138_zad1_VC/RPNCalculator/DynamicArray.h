#ifndef __DYNAMIC__ARRAY__
#define __DYNAMIC__ARRAY__
#include <iostream>
using namespace std;

template<class TYPE>
class DynamicArray
{
public:
	// Г4
	DynamicArray();
	DynamicArray(int);
	~DynamicArray();
	DynamicArray(const DynamicArray &);
	DynamicArray& operator=(const DynamicArray &);

public:
	const void print();
	void selectionSort();
	int search(const TYPE &);
	int getSize();
	int getCapacity();

	void add(const TYPE &);
	bool remove(int);

	const TYPE operator[](int) const;
	TYPE& operator[](int);

private:
	void clean();
	void copy(const DynamicArray<TYPE> &);
	void resize(int);
	int binarySearch(const TYPE &);
	int linearSearch(const TYPE &);
	
private:
	TYPE* data;
	int capacity;
	int size;
	bool isSorted;
};

#include "DynamicArrayFunctions.h"

#endif // !__DYNAMIC__ARRAY__
