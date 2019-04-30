#pragma once

#include "FileData.h"
#include <string>

class FileReaderAbs
{
public:
	FileReaderAbs();
	virtual ~FileReaderAbs();

	virtual FileData read(const std::string& filename) = 0;
};

