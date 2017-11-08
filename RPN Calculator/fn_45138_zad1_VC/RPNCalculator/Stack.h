#ifndef __STACK__
#define __STACK__
#include <assert.h>

static const int initialCapacity = 2;

template<class TYPE>
class Stack
{
public:
	Stack();
	~Stack();
	Stack(const Stack &);
	Stack& operator=(const Stack &);

	void push(const TYPE &);
	bool pop();
	TYPE& peek();
	int getSize() const { return stackFrame; }

private:
	bool isEmpty() const;
	bool isFull() const;

private:
	void clean();
	void copy(const Stack &);
	void resize();

private:
	TYPE* data;
	int stackFrame;
	int capacity;
};


template<class TYPE>
inline Stack<TYPE>::Stack()
	:data(NULL)
	, stackFrame(0)
	, capacity(initialCapacity)
{
	data = new TYPE [capacity];
}

template<class TYPE>
inline Stack<TYPE>::~Stack()
{
	clean();
}

template<class TYPE>
inline Stack<TYPE>::Stack(const Stack<TYPE> & input)
{
	copy(input)
}

template<class TYPE>
inline Stack<TYPE>& Stack<TYPE>::operator=(const Stack<TYPE> & input)
{
	if (this != &input)
	{
		clean();
		copy(input);

	}
	return *this;
}

template<class TYPE>
inline void Stack<TYPE>::push(const TYPE & element)
{
	if (isFull())
		resize();

	data[stackFrame] = element;
	stackFrame++;
}

template<class TYPE>
inline bool Stack<TYPE>::pop()
{
	if (isEmpty())
		return false;
	else
	{		
		stackFrame--;
		return true;
	}
}

template<class TYPE>
inline TYPE& Stack<TYPE>::peek()
{
	assert(!isEmpty());

	return data[stackFrame - 1];
}

template<class TYPE>
inline bool Stack<TYPE>::isEmpty() const
{
	return stackFrame == 0;
}

template<class TYPE>
inline bool Stack<TYPE>::isFull() const
{
	return stackFrame == capacity;
}

template<class TYPE>
inline void Stack<TYPE>::clean()
{
	delete[] data;
	data = NULL;
}

template<class TYPE>
inline void Stack<TYPE>::copy(const Stack<TYPE> & input)
{
	stackFrame = input.stackFrame;
	capacity = input.capacity;
	data = new TYPE[capacity];

	for (size_t i = 0; i < stackFrame; i++)
	{
		data[i] = input.data[i];
	}
}

template<class TYPE>
inline void Stack<TYPE>::resize()
{
	int newCapacity = capacity * 2;
	TYPE * newData;
	do
	{
		try
		{
			newData = new TYPE[newCapacity];
		}
		catch (bad_alloc & e)
		{
			newCapacity--;
			cerr << e.what();
		}
	} while (!newData && newCapacity > capacity);

	if (newData)
	{
		for (size_t i = 0; i < stackFrame; i++)
		{
			newData[i] = data[i];
		}
		clean();
		data = newData;
		capacity = newCapacity;
	}
}


#endif // !__STATIC__STACK__

