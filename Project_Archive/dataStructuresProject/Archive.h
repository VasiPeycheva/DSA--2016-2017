#ifndef __ARCHIVE__HEADER__INCLUDED__
#define __ARCHIVE__HEADER__INCLUDED__

#include "FolderIO.h"

class Archive
{
public:
	void pack(const char *, const char *);
	void unpack(const char *,const char *);
	void list(const char *);
};

#endif // !__ARCHIVE__HEADER__INCLUDED__
