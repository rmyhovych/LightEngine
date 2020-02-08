#include "FileReaderHandler.h"


FileReaderHandler FileReaderHandler::handler;


FileReaderHandler::FileReaderHandler() :
	m_fileReader(nullptr)
{
}


FileReaderHandler::~FileReaderHandler()
{
	if (m_fileReader != nullptr)
	{
		delete m_fileReader;
		m_fileReader = nullptr;
	}
}


void FileReaderHandler::setFileReader(IFileReader* fileReader)
{
	handler.m_fileReader = fileReader;
}

IFileReader* FileReaderHandler::getFileReader()
{
	return handler.m_fileReader;
}
