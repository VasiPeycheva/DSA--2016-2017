#include "CodeSheet.h"

CodeSheet::CodeSheet()
{}

void CodeSheet::initialize(const HuffmanTree & tree)
{
	Bitcode helpVector;
	const node * root = tree.getRoot();
	createCodeSheet(root, helpVector);
}

Bitcode CodeSheet::operator[](unsigned char index)
{
	if (index < 0 || index > ASCII)
		throw "invalid index";

	return sheet[index];
}

void CodeSheet::createCodeSheet(const node *& root, Bitcode helpVector)
{
	if(!root->left && !root->right)
	{
		sheet[(unsigned char)root->symbol] = helpVector;
		return;
	}
	else
	{
		helpVector.bitRepresentation.push_back(0);
		const node * leftRoot = root->left;
		createCodeSheet(leftRoot, helpVector);
		helpVector.bitRepresentation.pop_back();

		helpVector.bitRepresentation.push_back(1);
		const node * rightRoot = root->right;
		createCodeSheet(rightRoot, helpVector);
		helpVector.bitRepresentation.pop_back();
	}
}
