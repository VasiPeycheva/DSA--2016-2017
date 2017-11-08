#pragma once
#ifndef __TEXT__PROCESSOR__HEADER__INCLUDED__
#define __TEXT__PROCESSOR__HEADER__INCLUDED__
#include "Dictionary.h"
class TextProcessor
{
public:
	TextProcessor();
	~TextProcessor();

private:
	TextProcessor(const TextProcessor &);
	TextProcessor& operator=(const TextProcessor &);

// interface
public:
	void createDictionary(const char *);
	void result(const char * fileName);

//help function
private:
	void evaluateText(const char * );
	void extractTextFromFile(const char *, char * &);
	void findCoeficient();
	void countWords(const char *);
	void clean();

private:
	unsigned int numOfWords;
	double evaluation;
	node * root;
};


#endif // !__TEXT__PROCESSOR__HEADER__INCLUDED__
