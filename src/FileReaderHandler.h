#pragma once
#include "FileReaderAbs.h"


class FileReaderHandler
{
public:
	~FileReaderHandler();

	static void setFileReader(FileReaderAbs* fileReader);
	static FileReaderAbs* getFileReader();

private:

	FileReaderHandler();
	FileReaderHandler(const FileReaderHandler const&) = delete;
	FileReaderHandler& operator=(const FileReaderHandler const&) = delete;

	static FileReaderHandler handler;
	FileReaderAbs* m_fileReader;
};

