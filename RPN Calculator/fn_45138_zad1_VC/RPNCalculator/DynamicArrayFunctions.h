#ifndef __DYNAMIC__ARRAY__FUNCTIONS__
#define __DYNAMIC__ARRAY__FUNCTIONS__

const int resize_with = 10;

template <class TYPE>
inline DynamicArray<TYPE>::DynamicArray()
	: data(NULL)
	, size(0)
	, capacity(0)
	, isSorted(false)
{}

template <class TYPE>
inline DynamicArray<TYPE>::DynamicArray(int n)
	: data(NULL)
	, size(0)
	, capacity(n)
	, isSorted(false)
{
	if (capacity > 0)
	{
		try
		{
			data = new TYPE[capacity];
		}
		catch (bad_alloc & e)
		{
			cout << "Not enough memory!" << e.what() << endl;
		}
	}
}

template<class TYPE>
inline DynamicArray<TYPE>::DynamicArray(const DynamicArray<TYPE> & other)
{
	copy(other);
}

template<class TYPE>
inline DynamicArray<TYPE>& DynamicArray<TYPE>::operator=(const DynamicArray<TYPE> & other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

template <class TYPE>
inline DynamicArray<TYPE>::~DynamicArray()
{
	delete[] data;
}

template <class TYPE>
inline const TYPE DynamicArray<TYPE>::operator[](int index) const
{
	if (index < size || index >= 0)
		return data[index];

	throw "invalid index";
}

template <class TYPE>
inline TYPE& DynamicArray<TYPE>::operator[](int index)
{
	if (index < size || index >= 0)
		return data[index];

	throw "invalid index";
}

template<class TYPE>
inline void DynamicArray<TYPE>::selectionSort()
{
	TYPE temp;
	int minIndex;
	for (int i = 0; i <= size - 2; i++)
	{
		minIndex = i;
		for (int j = i + 1 ; j <= size - 1; j++)
		{
			if (data[minIndex] > data[j])
				minIndex = j;
		}
		if (minIndex != i)
		{
			//swap
			temp = data[i];
			data[i] = data[minIndex];
			data[minIndex] = temp;
		}
	}
	isSorted = true;
}



template<class TYPE>
inline const void DynamicArray<TYPE>::print()
{
	for (int i = 0; i < size; i++)
		cout << data[i] << " ";
}


template<class TYPE>
inline int DynamicArray<TYPE>::search(const TYPE & element)
{
	if (isSorted)
		return binarySearch(element);
	else
		return linearSearch(element);

}

template<class TYPE>
inline int DynamicArray<TYPE>::getSize()
{
	return size;
}

template<class TYPE>
inline int DynamicArray<TYPE>::getCapacity()
{
	return capacity;
}

template<class TYPE>
inline void DynamicArray<TYPE>::add(const TYPE & input)
{
	if (size >= capacity)
	{
		capacity += resize_with;
		resize(capacity);
	}

	data[size] = input;
	size++;
	isSorted = false;
}

template<class TYPE>
inline bool DynamicArray<TYPE>::remove(int index)
{
	if (index >= size || index < 0)
		return false; /*or ? throw "invalid index" */
	for (int i = index; i < size - 1; i++)
		data[i] = data[i + 1];
	size--;
	return true;
}


template <class TYPE>
inline void DynamicArray<TYPE>::clean()
{
	delete[] data;
	data = NULL;
}

template <class TYPE>
inline void DynamicArray<TYPE>::resize(int with)
{
	capacity += with;
	TYPE * bigger_data = new TYPE[capacity];
	for (int i = 0; i < size; i++)
		bigger_data[i] = data[i];
	clean();
	data = bigger_data;
}

template <class TYPE>
inline void DynamicArray<TYPE>::copy(const DynamicArray<TYPE> & other)
{
	data = new(nothrow)TYPE[other.capacity];
	if (!data)
	{
		//ask
		cout << "Not enough memory!" << endl;
	}
	size = other.size;
	capacity = other.capacity;
	isSorted = other.isSorted;
	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}



template<class TYPE>
inline int DynamicArray<TYPE>::binarySearch(const TYPE & element)
{
	int beg = 0;
	int end = size - 1;
	int med = (beg + end) / 2;
	while (beg <= end)
	{
		if (data[med] == element)
			return med;
		else if (data[med] > element)
		{
			end = med - 1;
			med = (beg + end) / 2;
		}
		else
		{
			beg = med + 1;
			med = (beg + end) / 2;
		}
	}
	cout << "Element not found" << endl;
// ask
	return -1;
}

template<class TYPE>
inline int DynamicArray<TYPE>::linearSearch(const TYPE & element)
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == element)
			return i;
	}
	cout << "Element not found" << endl;
	return -1;
}


#endif // !__DYNAMIC__ARRAY__FUNCTIONS__
