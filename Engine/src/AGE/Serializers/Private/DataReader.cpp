#include "AGEpch.hpp"
#include "Serializers/Public/DataReader.h"
#include "Core/Public/Buffer.h"
#include "Parser/Public/JsonParser.h"

namespace AGE
{

	FileStreamReader::FileStreamReader(const std::filesystem::path& Path)
		:m_Path(Path)
	{
		m_Stream = std::ifstream(Path, std::ifstream::in | std::ifstream::binary);

	}
	FileStreamReader::~FileStreamReader()
	{
		m_Stream.close();
	}
	bool FileStreamReader::ReadData(char* Data, size_t Size)
	{
		m_Stream.read(Data, Size);
		return true;
	}

	bool FileStreamReader::ReadBytes(std::vector<std::byte>& Data, size_t Size)
	{
		m_Stream.read(reinterpret_cast<char*>(Data.data()), Size);
		return true;
	}

	bool FileStreamReader::ReadBytes(uint8_t* Data, size_t Size)
	{
		m_Stream.read(reinterpret_cast<char*>(Data), Size);
		return true;
	}

	MemoryStreamReader::MemoryStreamReader(void* Addr, size_t Size)
		:m_Addr(Addr)
	{
		std::string s((char*)m_Addr, Size);
		m_Stream = std::istringstream(s);
	}
	MemoryStreamReader::~MemoryStreamReader()
	{
		m_Stream.clear();
	}
	bool MemoryStreamReader::ReadData(char* Data, size_t Size)
	{
		m_Stream.read(Data, Size);
		return true;
	}

	bool MemoryStreamReader::ReadBytes(std::vector<std::byte>& Data, size_t Size)
	{
		m_Stream.read(reinterpret_cast<char*>(Data.data()), Size);
		return true;
	}

	bool MemoryStreamReader::ReadBytes(uint8_t* Data, size_t Size)
	{
		m_Stream.read(reinterpret_cast<char*>(Data), Size);
		return true;
	}

	bool MemoryStreamReader::ReadJson(std::string& String)
	{
		return false;
	}

	void DataReader::ReadBuffer(char* Data, size_t Size)
	{
		uint32_t size = 0;
		if (Size == 0)
		{
			ReadRaw<uint32_t>(size);
			ReadData(Data, (size_t)size);
			return;
		}
			ReadData(Data, Size);
	}
	void DataReader::ReadString(std::string& String)
	{
		size_t Sizet = 0;
		std::string In;
		ReadData((char*)&Sizet, sizeof(size_t));
		In.resize(Sizet);
		ReadData(&In[0], Sizet);
		//ReadData(&String[0], Size);

		String = In.data();

	}
	bool FileStreamReader::ReadJson(std::string& String)
	{
		size_t Sizet = 0;
		std::string In;
		ReadData((char*)&Sizet, sizeof(size_t));
		In.resize(Sizet);
		std::fill(&In[0], &In[Sizet-1], 0);

		m_Stream.read(&In[0], Sizet);
		String = In.data();

		return true;
	}
}