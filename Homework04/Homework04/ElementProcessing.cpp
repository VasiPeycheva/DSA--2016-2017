#include "ElementProcessing.h"
#include <fstream>

void ElementProcessing::loadFile(const char * fileName)
{
	int key;
	int size;
	char * data;
	std::ifstream in(fileName, std::ios::binary);
	while (true)
	{
		in.read((char*)&key, sizeof(key));
		if (in.eof())
		{
			break;
		}
		in.read((char*)&size, sizeof(size));
		data = new char[size + 1];
		in.read(data, size);
		data[size] = '\0';
		buffer.add(Element(key, data));
		delete[] data;
	}

	in.close();

	buffer.selectionSort();
	int end = buffer.getSize() - 1;
	buildTree(0, end);	
}

void ElementProcessing::add(int key, const char * data)
{
	binaryTree.add(Element(key, data));
}

bool ElementProcessing::remove(int key, const char * data)
{
	return binaryTree.remove(Element(key, data));
}

bool ElementProcessing::search(int key, const char * data)
{
	return binaryTree.search(Element(key, data));
}

int ElementProcessing::removeall(int key)
{
	return binaryTree.removeAll(key);
}

void ElementProcessing::buildTree(int start, int end)
{
	int middle = (start + end) / 2;
	bool isInserted = false;
	if (start == end)
	{
		binaryTree.add(buffer[middle]);
		return;
	}
	else
	{
		if (start < middle)
		{
			binaryTree.add(buffer[middle]);
			isInserted = true;

			buildTree(start, middle - 1);
		}
		if (middle < end)
		{
			if(!isInserted)
			binaryTree.add(buffer[middle]);

			buildTree(middle + 1, end);
		}
	}
}



