#ifndef __HUFFMAN__TREE__HEADER__INCLUDED__
#define __HUFFMAN__TREE__HEADER__INCLUDED__

#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "StatisticTable.h"
#include "Nodes.h"
#include "HuffmanTreeIO.h"

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree();

	void initialize(const StatisticTable &);
	void writeTree(std::ofstream & out);
	void readTree(std::ifstream & in); 

	const node * getRoot() const;

private:
	void createForest(const StatisticTable &);
	void createHuffmanTree();

private:

	MinHeap<weightedNode> huffmanTree;
};

#endif // !__HUFFMAN__TREE__HEADER__INCLUDED__
