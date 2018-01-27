#ifndef __ZIP__FILE__HEADER__INCLUDED__
#define __ZIP__FILE__HEADER__INCLUDED__

#include <fstream>
#include <string>
#include "HuffmanTree.h"
#include "CodeSheet.h"

class ZipFile
{
public:
	ZipFile();
	~ZipFile();

	//bool is for the percent of done work
	bool archive(const char *, std::ofstream &);

	//functions for the saving
private:
	void saveFileName(const char *, std::ofstream &);
	void saveCodedFile(std::ofstream &);

	//functions for coding
private:
	void loadFile(const char *);
	void codeFile(const char *, unsigned int);
	void codeChar(char);

	void writeBit(bool);
	void checkBufferForLeftData();
	void checkBuffer();
	void syncBuffer();


private:
	HuffmanTree codeTree;
	CodeSheet symbolCodeSheet;
	std::vector<char> result;
	char * fileName;
	char buffer;
	unsigned short bitposition;
	unsigned int bitCnt;
};

#endif // !__ZIP__FILE__HEADER__INCLUDED__
