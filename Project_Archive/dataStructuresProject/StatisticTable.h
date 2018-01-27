#ifndef __STATISTIC__TABLE__HEADER__INCLUDED__
#define __STATISTIC__TABLE__HEADER__INCLUDED__

static const int ASCII = 256;

class StatisticTable
{
public:
	StatisticTable();
	~StatisticTable();

	void createStatisticTable(const char * , unsigned int size);
	const unsigned int operator[](unsigned short index) const;

	int getTableSize() const;

private:
	unsigned int table[ASCII];

};

#endif // !__STATISTIC__TABLE__HEADER__INCLUDED__
