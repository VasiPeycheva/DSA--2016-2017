#ifndef __HUFFMAN__TREE__INPUT__OUTPUT__
#define __HUFFMAN__TREE__INPUT__OUTPUT__

#include "HuffmanTree.h"
#include <vector>

class HuffmanTreeOutput
{
public:
	HuffmanTreeOutput();
	~HuffmanTreeOutput() {}

	unsigned int getBitCnt() const;
	void saveTree(const node *, std::ofstream &);

private:
	void writeTree(const node *);
	void writeBit(bool);
	void writeSymbol(char);

	void syncBuffer();
	bool checkBuffer();
	void checkBufferForData();

private:
	std::vector<char> result;
	char buffer;
	char mask;
	unsigned short bitposition;
	unsigned int bitCnt;
};


class HuffmanTreeInput
{
public:
	HuffmanTreeInput();
	~HuffmanTreeInput() {}

	void readTree(const char *, unsigned int);
	node * getTree();

private:
	bool readBit();
	char readSymbol();

	void loadBuffer();
	void checkBuffer();

private:
	const char * codedTree;
	node * root;
	char buffer;
	char mask;
	unsigned short bitposition;
	unsigned int bitCnt;
	
};


#endif // !__HUFFMAN__TREE__INPUT__OUTPUT__
