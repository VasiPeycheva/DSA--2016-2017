#include "Dictionary.h"


node* insert(node* root, char c)
{
	node* create = root;
	short index = indexation(c);
	if (index == -1)
		throw "invalid expression!";
	if (!create->children[index])
		create->children[index] = new node();
	return create->children[index];
}

node* search(node* root, char c)
{
	node* seek = root;
	short index = indexation(c);
	if (index == -1 || !seek->children[index])
		return NULL;
	else
		return seek->children[index];
}

void destroy(node* root)
{
	node* destroyer = root;
	for (int i = 0; i < alphabetSize; i++)
	{
		if (destroyer->children[i] != nullptr)
			destroy(destroyer->children[i]);
	}
	delete destroyer;
	return;
}

bool isLetter(char c)
{
	return isBigger(c) || isLower(c);
}

bool isBigger(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool isLower(char c)
{
	return c >= 'a' && c <= 'z';
}

void toLower(char &c)
{
	c += 'a' - 'A';
	return;
}

short indexation(char c)
{
	if (isLetter(c))
		return (short)c - (short)'a';
	else if(c == '\t' || c == '\n' || c == ' ')
		return 26;
	else
		return -1; // space
}