#include "FolderIO.h"
#include <dirent.h>
#include <direct.h>
#include <sys/stat.h>

FolderIO::FolderIO()
	:completedFiles(0)
{}

FolderIO::~FolderIO()
{}

void FolderIO::readFolder(const char * path, std::ifstream & in)
{
	int len;
	char * folderName = NULL;
	in.read((char*)&len, sizeof(len));
	folderName = new char[len + 1];
	in.read(folderName, len);
	folderName[len] = '\0';

	char * newFolder = NULL;
	newFolder = new char[strlen(path) + strlen(folderName) + 2];
	strcpy(newFolder, path);
	strcat(newFolder, "\\");
	strcat(newFolder, folderName);
	createFolder(newFolder);
	
	char flag;
	while (true)
	{
		in.read((char *)&flag, sizeof(flag));
		if (in.eof())
			break;

		if(flag == 0)
		{
			readFolder(newFolder, in);
		}
		else if(flag == 1)
		{
			UnzipFile unzipper;
			if(unzipper.unzip(newFolder,in));
			{
				completedFiles++;
				std::cout << completedFiles << '\n';
			}
		}
		else
		{
			break;
		}
	}

	delete[] folderName;
	delete[] newFolder;
}

void FolderIO::writeFolder(const char * path, std::ofstream & output)
{

	DIR * dir = NULL;
	struct dirent *entry = NULL;
	struct stat info;

	char flag;
	char * openFolder = NULL;
	dir = opendir(path);
	if (!dir)
	{
		std::cout << "Directory: " << path << "doesn`t exist! \n";
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if((strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..")))
		{
			openFolder = new char[strlen(path) + strlen(entry->d_name) + 3];
			strcpy(openFolder, path);
			strcat(openFolder, "\\");
			strcat(openFolder, entry->d_name);
			stat(openFolder, &info);
			if (S_ISDIR(info.st_mode))
			{
				flag = 0; // is a folder
				unsigned int size = strlen(entry->d_name);
				output.write((const char *)&flag, sizeof(flag));
				output.write((const char *)&size, sizeof(size));
				output.write(entry->d_name, strlen(entry->d_name));
				writeFolder(openFolder, output);
				flag = 2; //close current folder
				output.write((const char *)&flag, sizeof(flag));
			}
			else
			{
				flag = 1; // is a file
				output.write((const char *)&flag, sizeof(flag));
				ZipFile pack;
				if (pack.archive(openFolder, output))
				{
					completedFiles++;
					std::cout << completedFiles << '\n';
				}
			}
		}
	}
    delete[] openFolder;
    closedir(dir);
}

void FolderIO::createFolder(const char * folderName)
{
	mkdir(folderName);
}
