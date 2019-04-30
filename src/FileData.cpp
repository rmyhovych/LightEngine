#include "FileData.h"

#include <fstream>



FileData::FileData(const uint8_t* data, unsigned size) :
	m_size(size)
{
	this->m_data = new uint8_t[size];

	for (int i = 0; i < size; i++)
	{
		this->m_data[i] = data[i];
	}
}

FileData::FileData(FileData&& oldBuffer)
{
	m_data = oldBuffer.m_data;
	m_size = oldBuffer.m_size;

	oldBuffer.m_data = nullptr;
	oldBuffer.m_size = 0;
}

FileData::~FileData()
{
	if (m_data == nullptr)
	{
		delete[] m_data;
		m_data = nullptr;
	}
}

FileData& FileData::operator=(FileData&& oldBuffer)
{
	m_data = oldBuffer.m_data;
	m_size = oldBuffer.m_size;

	oldBuffer.m_data = nullptr;
	oldBuffer.m_size = 0;

	return *this;
}

uint8_t* FileData::getData()
{
	return m_data;
}

unsigned FileData::size()
{
	return m_size;
}
