#pragma once


typedef unsigned char uint8_t;

class FileData
{
public:
	FileData(const uint8_t* data = nullptr, unsigned size = 0);
	FileData(FileData&& oldBuffer);

	~FileData();

	FileData& operator=(FileData&& oldBuffer);


	uint8_t* getData();
	unsigned size();

private:

	uint8_t* m_data;
	unsigned m_size;
};

