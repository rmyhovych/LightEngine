#pragma once


typedef unsigned char uint8_t;

class FileData
{
public:
	FileData(const char* path);
	FileData(const uint8_t* data, unsigned size);

	FileData(FileData& oldBuffer);


	~FileData();


	FileData& operator=(FileData& otherBuffer);


	uint8_t* data;
	unsigned size;

};

