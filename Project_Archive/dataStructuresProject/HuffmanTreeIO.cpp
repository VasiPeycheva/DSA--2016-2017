#include "HuffmanTreeIO.h"

/*
* 
* "writeTree" and "getTree" functions are created based on the book
* "Programming = ++Algorithms" by Preslav Nakov
*
*/

static const int FULL = 8;

HuffmanTreeOutput::HuffmanTreeOutput()
	:buffer(0)
	,mask(0)
	,bitposition(0)
	,bitCnt(0)
{}

unsigned int HuffmanTreeOutput::getBitCnt() const
{
	return bitCnt;
}

void HuffmanTreeOutput::writeTree(const node * root)
{
	if (root != NULL)
	{
		if (!root->left && !root->right)
		{
			writeBit(0);
			writeSymbol(root->symbol);
		}
		else
		{
			writeBit(1);
			writeTree(root->left);
			writeTree(root->right);
		}
	}
}

void HuffmanTreeOutput::writeBit(bool bit)
{
	checkBuffer();

	buffer |= bit;
	bitposition++;
	bitCnt++;

	if (checkBuffer())
		return;

	buffer <<= 1;
}

void HuffmanTreeOutput::writeSymbol(char symbol)
{
	checkBuffer();
	for (size_t i = 0; i < FULL; i++)
	{
		mask = (1 << 7);
		mask &= symbol;
		symbol <<= 1;
		
		if (mask == 0)
			writeBit(0);
		else
			writeBit(1);

	}
}

void HuffmanTreeOutput::syncBuffer()
{
	result.push_back(buffer);
	buffer = 0;
	bitposition = 0;
}

bool HuffmanTreeOutput::checkBuffer()
{
	if (bitposition >= FULL)
	{
		syncBuffer();
		return true;
	}
	return false;
}

void HuffmanTreeOutput::checkBufferForData()
{
	if (bitposition != FULL && bitposition != 0)
	{
		while (bitposition < FULL -1)
		{
			buffer <<= 1;
			bitposition++;
		}
		syncBuffer();
	}
}

void HuffmanTreeOutput::saveTree(const node * root, std::ofstream & output)
{
	writeTree(root);
	checkBufferForData();
	output.write((const char *)& bitCnt, sizeof(bitCnt));
	unsigned int size = result.size();
	output.write((const char *)&result[0], size);
}

HuffmanTreeInput::HuffmanTreeInput()
	:codedTree(NULL)
	, root(NULL)
	, buffer(0)
	, mask(0)
	,bitposition(8)
	, bitCnt(0)
{}

void HuffmanTreeInput::readTree(const char * tree, unsigned int cnt)
{
	codedTree = tree;
	bitCnt = cnt;
}

node * HuffmanTreeInput::getTree()
{
	node * root;
	node * left;
	node * right;
	if (readBit() && bitCnt) 
	{
		left = getTree();
		right = getTree();
		root = new node(' ', left, right);
		return root;
	}
	else
	{
		if (bitCnt)
		{
			root = new node(readSymbol());
			return root;
		}
	}
}

bool HuffmanTreeInput::readBit()
{
	checkBuffer();
	mask = (1 << 7);
	mask &= buffer;
	buffer <<= 1;	
	bitposition++; 
	bitCnt--;
	return mask;
}

char HuffmanTreeInput::readSymbol()
{
	checkBuffer();
	char symbol = 0;
	char symMask = 0;
	for (int i = 0 ; i < FULL; i++)
	{
		symMask = (readBit() << (7-i));
		symbol |= symMask;
	}
	return symbol;
}

void HuffmanTreeInput::loadBuffer()
{
	buffer = *codedTree;
	codedTree++;
	bitposition = 0;
}

void HuffmanTreeInput::checkBuffer()
{
	if (bitposition >= FULL)
		loadBuffer();
}
