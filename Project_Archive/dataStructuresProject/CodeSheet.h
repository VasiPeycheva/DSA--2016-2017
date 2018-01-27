#ifndef __CODE__SHEET__HEADER__INCLUDED__
#define __CODE__SHEET__HEADER__INCLUDED__

#include <vector>
#include "HuffmanTree.h"

//static const int ASCII = 256;

struct Bitcode
{
	std::vector<bool> bitRepresentation;
};

class CodeSheet
{
public:
	CodeSheet();
	~CodeSheet() {}

	void initialize(const HuffmanTree &);
	Bitcode operator[](unsigned char);

private:
	void createCodeSheet(const node *&, Bitcode);

private:
	Bitcode sheet[ASCII];
};



#endif // !__CODE__SHEET__HEADER__INCLUDED__
