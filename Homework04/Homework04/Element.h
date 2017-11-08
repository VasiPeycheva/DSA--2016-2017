#ifndef __ELEMENT__HEADER__INCLUDED__
#define __ELEMENT__HEADER__INCLUDED__
#include <fstream>

class Element
{
public:
	Element();
	Element(int,const char *);
	~Element();
	Element(const Element &);
	Element& operator=(const Element &);

	int getKey() const;
	char * getData() const;

private:
	void copy(const Element &);

private:
	int key;
	char * data;

};
bool operator<(const Element &, const Element &);
bool operator>(const Element &, const Element &);
bool operator==(const Element &, const Element &);
bool operator<=(const Element &, const Element &);
bool operator>=(const Element &, const Element &);
bool operator<(const Element&, int);
bool operator>(const Element&, int);


#endif // !__ELEMENT__HEADER__INCLUDED__
