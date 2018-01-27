#include "StatisticTable.h"
#include <iostream>
StatisticTable::StatisticTable()
{
	for (size_t i = 0; i < ASCII; i++)
	{
		table[i] = 0;
	}
}

StatisticTable::~StatisticTable()
{}

void StatisticTable::createStatisticTable(const char * data, unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		table[(unsigned char)*data]++;
		data++;
	}
}

const unsigned int StatisticTable::operator[](unsigned short index) const
{
	if (index < 0 || index > ASCII)
		throw "invalid index";

	return table[index];
}

int StatisticTable::getTableSize() const
{
	return ASCII;
}

