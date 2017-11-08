#pragma once
#ifndef __DICTIONARY__HEADER__INCLUDED__
#define __DICTIONARY__HEADER__INCLUDED__
#include <iostream>

//latin alphabet consists of 26 characters and the 27-th is for the space
static const short alphabetSize = 27;

struct node {
	node* children[alphabetSize];
	bool isWord;
	int wordValue;
	node()
		:isWord(false)
		, wordValue(0)
	{
		for (int i = 0; i < alphabetSize; i++)
			children[i] = NULL;
	}
};

//help functions for the trie tree
node* insert(node * root, char c);
node* search(node* root, char c);
void destroy(node* tree);

//help functions
bool isLetter(char c);
bool isBigger(char c);
bool isLower(char c);
void toLower(char &c);
short indexation(char c);




#endif // !__DICTIONARY__HEADER__INCLUDED__
