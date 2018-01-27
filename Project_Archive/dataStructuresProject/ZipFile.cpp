#include "ZipFile.h"
#include "StatisticTable.h"

static const int FULL = 8;

ZipFile::ZipFile()
	:buffer(0)
	, bitCnt(0)
	, bitposition(0)
	,fileName(NULL)
{}

ZipFile::~ZipFile()
{
	delete[] fileName;
}

bool ZipFile::archive(const char * filePath, std::ofstream & output)
{
	loadFile(filePath);
	saveFileName(filePath, output);
	codeTree.writeTree(output);
	saveCodedFile(output);
	return true;
}

void ZipFile::saveFileName(const char * filePath, std::ofstream & output)
{
	int getPos;
	int it = 0;
	const char * pathIt = filePath;
	while(*pathIt)
	{
		if (*pathIt == '\\')
		{
			getPos = it + 1;
		}
		pathIt++;
		it++;
	}
	int size = strlen(filePath) - getPos;
	fileName = new char[size + 1];
	fileName[size] = '\0';
	
	char * putPtr = fileName;

	while (filePath[getPos])
	{
		*putPtr = filePath[getPos];
		getPos++;
		putPtr++;
	}

	output.write((const char *)&size, sizeof(size));
	output.write(fileName, size);
}

void ZipFile::saveCodedFile(std::ofstream & output)
{
	output.write((const char *)&bitCnt, sizeof(bitCnt));
	
	unsigned int size = result.size();
	output.write((const char *)&result[0], size);
}

void ZipFile::loadFile(const char * fileName)
{
	std::ifstream input(fileName, std::ios::binary);

	//get file size
	input.seekg(0, std::ios::end);
	int size = input.tellg();
	input.seekg(0, std::ios::beg);

	//extract file
	char * data = new char[size];
	input.read(data, size);
	input.close();

	codeFile(data, size);

	delete[] data;
}

void ZipFile::codeFile(const char * data, unsigned int size)
{
	StatisticTable table;
	table.createStatisticTable(data,size);
	codeTree.initialize(table);
	symbolCodeSheet.initialize(codeTree);

	for (size_t i = 0; i < size; i++)
	{
		codeChar(*data);
		data++;
	}

	checkBufferForLeftData();
}

void ZipFile::codeChar(char symbol)
{
	Bitcode symbolBitCode = symbolCodeSheet[(unsigned char)symbol];
	unsigned int size = symbolBitCode.bitRepresentation.size();
	for (size_t i = 0; i < size; i++)
	{
		writeBit(symbolBitCode.bitRepresentation[i]);
	}
}

void ZipFile::writeBit(bool bit)
{
	buffer |= bit;
	bitposition++;
	bitCnt++;
	checkBuffer();
	buffer <<= 1;
}

void ZipFile::checkBufferForLeftData()
{
	if (bitposition != 0)
	{
		while (bitposition < FULL - 1)
		{
			buffer <<= 1;
			bitposition++;
		}
		syncBuffer();
	}
}

void ZipFile::checkBuffer()
{
	if (bitposition >= FULL)
		syncBuffer();
}

void ZipFile::syncBuffer()
{
	result.push_back(buffer);
	buffer = 0;
	bitposition = 0;
}
