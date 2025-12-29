#include "AGEpch.hpp"
#include "Serializers/Public/DataWriter.h"
#include "Core/Public/Buffer.h"

namespace AGE
{
	FileStreamWriter::FileStreamWriter(const std::filesystem::path& Path)
		:m_Path(Path)
	{
		m_Stream = std::ofstream(Path, std::ofstream::out | std::ofstream::binary);
	}
	FileStreamWriter::~FileStreamWriter()
	{
		m_Stream.close();
	}
	bool FileStreamWriter::WriteData(const char* Data, size_t Size)
	{
		m_Stream.write(Data, Size);
		return true;
	}
	void DataWriter::WriteBuffer(Buffer buffer, bool WriteSize)
	{
		if (WriteSize)
		{
			WriteData((char*)&buffer.Size, sizeof(uint64_t));
		}

		WriteData((char*)buffer.Data, buffer.Size);
	}
	void DataWriter::WriteZero(uint64_t Size)
	{
		char Zero = 0;
		for (uint64_t i = 0; i < Size; i++)
		{
			WriteData(&Zero, 1);
		}
	}
	void DataWriter::WriteString(const std::string& String)
	{
		//Lol this isn't how it works
		size_t Size = String.length();
		WriteData((char*)&Size, sizeof(size_t));
		WriteData((char*)String.data(), sizeof(char) * Size); //This should probably be String.length() as we should be multiplying the size of a char (1 byte) by the number of chars in the string
	}
	MemoryStreamWriter::MemoryStreamWriter(void* Addr)
		:m_Addr(Addr)
	{
		m_Stream = std::stringstream(std::stringstream::out | std::stringstream::binary);
	}
	MemoryStreamWriter::~MemoryStreamWriter()
	{
		m_Stream.clear();
	}
	bool MemoryStreamWriter::WriteData(const char* Data, size_t Size)
	{
		m_Stream.write(Data, Size);
		return true;
	}
}