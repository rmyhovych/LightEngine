#include "FileReader.h"
#include <fstream>
#include <filesystem>

FileReader::FileReader(const std::string& dataPath) :
	m_dataPath(dataPath)
{
}


FileReader::~FileReader()
{
}

FileData FileReader::read(const std::string& filename)
{
	std::string filePath = m_dataPath + filename;
	std::ifstream file(filePath, std::ifstream::ate);
	
	file.seekg(0, file.end);
	int filesize = file.tellg();
	file.seekg(file.beg);

	std::string str;
	str.reserve(filesize);
	str.assign((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	file.close();

	return FileData((uint8_t*) str.c_str(), str.size());
}