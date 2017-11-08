#include <iostream>
#include "Element.h"

Element::Element()
	:key(0)
	,data(NULL)
{}

Element::Element(int inputKey,const char * inputdata)
	: key(inputKey)
	, data(NULL)
{
	data = new char[strlen(inputdata) + 1];
	strcpy(data, inputdata);
}

Element::~Element()
{
	delete[] data;
	data = NULL;
}

Element::Element(const Element & input)
{
	copy(input);
}

Element & Element::operator=(const Element & input)
{
	if (this != &input)
	{
		delete[] data;
		copy(input);
	}
	return *this;
}

int Element::getKey() const
{
	return key;
}

char * Element::getData() const
{
	return data;
}

void Element::copy(const Element & input)
{
	key = input.key;
	data = new char[strlen(input.data) + 1];
	strcpy(data, input.data);
}

bool operator<(const Element & lhs, const Element & rhs)
{
	return (lhs.getKey() < rhs.getKey());
}

bool operator>(const Element & lhs, const Element & rhs)
{
	return (lhs.getKey() > rhs.getKey());
}

bool operator==(const Element & lhs, const Element & rhs)
{
	if (lhs.getKey() == rhs.getKey())
	{
		if (strcmp(lhs.getData(), rhs.getData()) == 0)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool operator<=(const Element & lhs, const Element & rhs)
{
	return (lhs < rhs || (lhs.getKey() == rhs.getKey()));
}

bool operator>=(const Element & lhs, const Element & rhs)
{
	return (rhs<=lhs);
}

bool operator<(const Element & lhs , int rhs)
{
	return (lhs.getKey() < rhs);
}

bool operator>(const Element & lhs, int rhs)
{
	return (lhs.getKey() > rhs);
}
