#include <fstream>
#include "TextProcessor.h"

using namespace std;

TextProcessor::TextProcessor()
	:numOfWords(0)
	,evaluation(0)
{
	root = new node();
}

TextProcessor::~TextProcessor()
{
	destroy(root);
}

void TextProcessor::createDictionary(const char * fileName)
{
	char buff = '\0';
	ifstream in(fileName, ios::in);
	if (!in.is_open())
	{
		throw "file cannot be open";
		in.close();
	}
	while (!in.eof())
	{
		node* tree = root;
		buff = in.get();
		while (!in.eof() && buff != '\n')
		{
			if (isLower(buff))
			{
				while (isLower(buff) || buff == ' ') //if the word is valid, we insert it in the tree
				{
					if (!isLower(in.peek()) && buff == ' ') break;
					tree = insert(tree, buff);
					buff = in.get();
				}
				tree->isWord = true;
				in >> tree->wordValue;
				buff = in.get();
			}
			else if (isBigger(buff)) //if not, we skip the whole line
			{
				while (!in.eof() && buff != '\n')
					buff = in.get();
			}
			else //if we have space, new line or tabulation
				buff = in.get();
		}
	}
	in.close();
}

void TextProcessor::extractTextFromFile(const char * fileName, char *& buffer)
{
	ifstream in(fileName, ios::in);
	if (!in.is_open())
		throw;
	in.seekg(0, in.end);
	int lenght = in.tellg();
	in.seekg(0, in.beg);
	buffer = new char[lenght + 1];
	in.read(buffer, lenght);
	buffer[lenght] = '\0';
	in.close();
}

void TextProcessor::evaluateText(const char* fileName)
{
	//extract the text from the file
	char * extractBuffer;
	extractTextFromFile(fileName, extractBuffer);

	//start searching
	char * matchPtr = extractBuffer;
	char * movePtr = extractBuffer;

	while (*movePtr)
	{
		bool hasSubWord = false;
		int subWordValue = 0;
		node * check = root;
		check = search(check, *movePtr);
		char * checkPtr = movePtr;
		checkPtr++;


		if (isBigger(*movePtr)) // convert the word to lower case so we could recognize it
			toLower(*movePtr);
		if (check && *movePtr) // if the first letter from the word is in the dictionary, 
			                        // we continue to search, until we reach a nullptr or isWord
		{   
			while (check && *movePtr)
			{
				if (check->isWord && (*checkPtr == ' ' || *checkPtr == '\t' || *checkPtr == '\n')) //save the longest word that is in the 
																								  //dictionary until now and we have more text to read
				{
					matchPtr = checkPtr;
					hasSubWord = true;
					subWordValue = check->wordValue;
				}
				if (check->isWord && *checkPtr == '\0') //save the longest word that is in the 
													   //dictionary until now and we DON`T have more text to read
				{
					matchPtr = checkPtr;
					hasSubWord = true;
					subWordValue = check->wordValue;
					break;
				}
				movePtr++;
				checkPtr++;
				check = search(check, *movePtr);
			}
			if (hasSubWord) //we have a match with the dictionary - we save the match value
			{
				movePtr = matchPtr;
				evaluation += subWordValue;
			}
			else //we get back, miss one word, and start searching again for a match
			{
				while (!isLetter(*matchPtr))
					matchPtr++;
				while (isLetter(*matchPtr))
					matchPtr++;
				movePtr = matchPtr;
			}
		}
		else
		{
			if (isLetter(*movePtr)) // read the whole word that is NOT in the dictionary
			{
				while (isLetter(*movePtr))
					movePtr++;
			}
			else
			{
				movePtr++;
			}
		}
	}
	countWords(extractBuffer);
	delete[] extractBuffer;
}

void TextProcessor::findCoeficient()
{
	if (!numOfWords) //we are not Chuck Norris and we can`t divide to 0
	{
		evaluation = 0;
		return;
	}

	evaluation /= numOfWords;
	return;
}

void TextProcessor::clean()
{
	numOfWords = 0;
	evaluation = 0;
}

void TextProcessor::countWords(const char * text)
{
	while (*text)
	{
		if (isLetter(*text))
		{
			while (isLetter(*text))
				text++;
			numOfWords++;
		}
		else
			text++;
	}

}

void TextProcessor::result(const char * fileName)
{
	cout << fileName << "\t" ;
	evaluateText(fileName);
	findCoeficient();
	cout << evaluation << endl;
	clean();
}
