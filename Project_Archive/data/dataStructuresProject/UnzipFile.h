#ifndef __UNZIP__FILE__HEADER__INCLUDED__
#define __UNZIP__FILE__HEADER__INCLUDED__

#include<fstream>
#include <string>
#include "HuffmanTree.h"

class UnzipFile
{
public:
	UnzipFile();
	~UnzipFile();

	bool unzip(const char *, std::ifstream&);
	const char * getFileName();

//functions for the reading
private:
	void readFileName(std::ifstream&);
	void readFile(std::ifstream&);
	void createFile(const char *);

// functions for decoding
private:
	void decodeFile();
	void checkBuffer();
	void loadBuffer();
	void syncResult(char);
	char getChar(const node *&);
	bool readBit();

private:
	HuffmanTree codeTree;
	std::vector<char> result;
	char * fileName;
	char * data;
	char buffer;
	unsigned short bitposition;
	unsigned int bitCnt;
};

#endif // !__UNZIP__FILE__HEADER__INCLUDED__
