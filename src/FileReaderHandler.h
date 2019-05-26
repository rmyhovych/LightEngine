#pragma once
#include "IFileReader.h"


class FileReaderHandler
{
public:
	~FileReaderHandler();

	static void setFileReader(IFileReader* fileReader);
	static IFileReader* getFileReader();

private:

	FileReaderHandler();
	FileReaderHandler(const FileReaderHandler const&) = delete;
	FileReaderHandler& operator=(const FileReaderHandler const&) = delete;

	static FileReaderHandler handler;
	IFileReader* m_fileReader;
};

