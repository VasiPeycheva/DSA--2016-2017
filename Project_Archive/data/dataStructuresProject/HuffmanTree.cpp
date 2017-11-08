#include "HuffmanTree.h"

HuffmanTree::HuffmanTree()
{}

HuffmanTree::~HuffmanTree()
{
	weightedNode destroyer = huffmanTree.popMin();
	cleanNode(destroyer.root);
}

void HuffmanTree::initialize(const StatisticTable & table)
{
	createForest(table);
	createHuffmanTree();
}

void HuffmanTree::writeTree(std::ofstream& output)
{
	HuffmanTreeOutput tree;
	tree.saveTree(getRoot(),output);
}

void HuffmanTree::readTree(std::ifstream & in)
{
	weightedNode createNode;
	unsigned int bitCnt;
	unsigned int byteCnt;
	char * input;

	HuffmanTreeInput extract;
	in.read((char*)&bitCnt, sizeof(bitCnt));
	byteCnt = (bitCnt / 8);
	if ((bitCnt % 8) != 0)
		byteCnt++;
	input = new char[byteCnt];
	in.read(input, byteCnt);

	extract.readTree(input, bitCnt);
	createNode.root = extract.getTree();
	huffmanTree.push(createNode);
	delete[] input;
}

const node * HuffmanTree::getRoot() const
{
	return huffmanTree.peakMin().root;
}


void HuffmanTree::createForest(const StatisticTable & table)
{
	int tableSize = table.getTableSize();
	
	for (size_t i = 0; i < tableSize; i++)
	{
		if (table[i])
		{
			weightedNode createNode;
			createNode.weight = table[i];
			createNode.root = new node((char)i);

			huffmanTree.push(createNode);
		}
	}
}

void HuffmanTree::createHuffmanTree()
{
	
	while (huffmanTree.getSize() > 1)
	{
		weightedNode firstMin = huffmanTree.popMin();
		weightedNode secondMin = huffmanTree.popMin();
		weightedNode unionNode;
		unionNode.weight = firstMin.weight + secondMin.weight;
		unionNode.root = new node();
		unionNode.root->left = firstMin.root;
		unionNode.root->right = secondMin.root;
		huffmanTree.push(unionNode);
	}

}


