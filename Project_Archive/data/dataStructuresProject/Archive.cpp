#include "Archive.h"

#include <fstream>

void Archive::pack(const char * path, const char * arc)
{
	FolderIO packFolder;
	std::ofstream output(arc, std::ios::binary);

	int lastSlash;
	int iteratePath = 0;
	const char * pathPtr = path;
	while (*pathPtr)
	{
		if (*pathPtr == '\\')
		{
			lastSlash = iteratePath + 1;
		}
		pathPtr++;
		iteratePath++;
	}
	unsigned int size = (strlen(path) - lastSlash);
	char * fileName = new char[size+1];
	char * ptrfileName = fileName;
	fileName[size] = '\0';

	while (path[lastSlash])
	{
		*ptrfileName = path[lastSlash];
		lastSlash++;
		ptrfileName++;
	}

	output.write((const char *)&size, sizeof(size));
	output.write(fileName, strlen(fileName));

	packFolder.writeFolder(path, output);
	delete[] fileName;
	output.close();
}

void Archive::unpack(const char * arc, const char * path)
{
	FolderIO unpackFolder;
	std::ifstream input(arc, std::ios::binary);
	unpackFolder.readFolder(path, input);
	input.close();
}

void Archive::list(const char *)
{
}


