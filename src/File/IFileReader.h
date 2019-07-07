#pragma once

#include "FileData.h"
#include <string>

class IFileReader
{
public:
	IFileReader();
	virtual ~IFileReader();

	virtual FileData read(const std::string& filename) = 0;
};

