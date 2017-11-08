#include "UnzipFile.h"

static const unsigned short FULL = 8;

UnzipFile::UnzipFile()
	:buffer(0)
	,bitposition(0)
	,bitCnt(0)
	,data(NULL)
	,fileName(NULL)
{}

UnzipFile::~UnzipFile()
{
	delete[] fileName;
}

bool UnzipFile::unzip(const char * path, std::ifstream & input)
{
	readFileName(input);
	readFile(input);
	createFile(path);
	return true;
}

const char * UnzipFile::getFileName()
{
	return fileName;
}

void UnzipFile::readFileName(std::ifstream & input)
{
	unsigned int size;
	input.read((char*)&size, sizeof(size));
	fileName = new char[size + 1];
	input.read(fileName, size);
	fileName[size] = '\0';
}

void UnzipFile::readFile(std::ifstream & input)
{
	codeTree.readTree(input);
	input.read((char*)&bitCnt, sizeof(bitCnt));
	unsigned int byteCnt = (bitCnt / 8);
	if ((bitCnt % 8) != 0)
		byteCnt++;
	char * arcData = new char[byteCnt];
	input.read(arcData, byteCnt);
	data = arcData;

	decodeFile();

	delete[] arcData;
}

void UnzipFile::createFile(const char * path)
{
	int size = strlen(path) + strlen(fileName) + 2;
	char * filePath = new char[size];
	strcpy(filePath, path);
	strcat(filePath, "\\");
	strcat(filePath, fileName);
	filePath[size - 1] = '\0';

	std::ofstream output(filePath, std::ios::binary);
	output.write((char*)&result[0], result.size());
	output.close();

	delete[] filePath;
}

void UnzipFile::decodeFile()
{
	loadBuffer();

	while (bitCnt)
	{
		const node * root = codeTree.getRoot();
		char symbol = getChar(root);
		syncResult(symbol);
	}
}

void UnzipFile::checkBuffer()
{
	if (bitposition >= FULL)
		loadBuffer();
}

void UnzipFile::loadBuffer()
{
	buffer = *data;
	data++;
	bitposition = 0;
}

void UnzipFile::syncResult(char symbol)
{
	result.push_back(symbol);
}

char UnzipFile::getChar(const node *&root)
{
	if (!root->left && !root->right)
	{
		return root->symbol;
	}
	else
	{
		if (readBit())
		{
			const node * rightChild = root->right;
			getChar(rightChild);
		}
		else
		{
			const node * leftChild = root->left;
			getChar(leftChild);
		}
	}
}

bool UnzipFile::readBit()
{
	char mask = (1 << 7);
	mask &= buffer;
	buffer <<= 1;
	bitposition++;
	bitCnt--;
	checkBuffer();
	return mask;
}

