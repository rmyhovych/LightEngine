#include "FileData.h"

#include <fstream>


FileData::FileData(const char* path)
{
	std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);

	size = file.tellg();



	data = new uint8_t[size];

	file.seekg(0, file.beg);



	file.read((char*)data, size);

	file.close();
}

FileData::FileData(const uint8_t* data, unsigned size) :
	size(size)
{
	this->data = new uint8_t[size];

	for (int i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}
}

FileData::FileData(FileData& oldBuffer)
{
	data = new uint8_t[oldBuffer.size];
	size = oldBuffer.size;

	for (unsigned i = 0; i < size; i++)
	{
		data[i] = oldBuffer.data[i];
	}
}

FileData::~FileData()
{
	delete[] data;
	data = nullptr;
}


FileData& FileData::operator=(FileData& otherBuffer)
{
	if (&otherBuffer != this)
	{
		data = new uint8_t[otherBuffer.size];
		size = otherBuffer.size;

		for (unsigned i = 0; i < size; i++)
		{
			data[i] = otherBuffer.data[i];
		}
	}

	return *this;
}
