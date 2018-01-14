#ifndef __STUDENTS__TABLE__HEADER__INCLUDED__
#define __STUDENTS__TABLE__HEADER__INCLUDED__

#include "Student.h"
#include "DynamicArray.h"

typedef int(*comparator) (const Student &, const Student &);

class StudentsTable
{
public:
	StudentsTable(string fileName);
	~StudentsTable() {}

	void sortBy(string criterion, string order);

private:
	bool validateData(const Student & check);

	void sortByAge();
	void sortByGrade();

	void siftDown(int size, int parent,comparator function);
	void HeapSort(comparator function);

	void merge(int left, int medium, int right, comparator function);
	void mergeSortRec(int left, int right, comparator function);
	void mergeSort(comparator function);


private:
	DynamicArray<Student> table;
	unsigned int tableSize;
};

#endif // !__STUDENTS__TABLE__HEADER__INCLUDED__
