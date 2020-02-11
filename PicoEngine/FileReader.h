#pragma once

#include <string>

#include "File/IFileReader.h"
#include "File/FileData.h"

class FileReader :
	public IFileReader
{
public:
	FileReader(const std::string& dataPath);

	virtual ~FileReader();

	virtual FileData read(const std::string& filename);

private:
	const std::string m_dataPath;
};
