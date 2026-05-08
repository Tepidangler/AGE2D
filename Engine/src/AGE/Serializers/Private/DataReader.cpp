#include "AGEpch.hpp"
#include "Serializers/Public/DataReader.h"
#include "Core/Public/Buffer.h"
#include "Parser/Public/JsonParser.h"

namespace AGE
{

	/**
 * @brief Constructs a FileStreamReader object with the given file path.
 * 
 * This constructor opens an ifstream in binary mode for reading from the provided file path.
 * The opened stream is stored in m_Stream member variable.
 * 
 * @param Path The file path to open as a stream.
 */
FileStreamReader::FileStreamReader(const std::filesystem::path& Path)
		:m_Path(Path)
	{
		m_Stream = std::ifstream(Path, std::ifstream::in | std::ifstream::binary);

	}
	/**
 * @brief Destructor for the FileStreamReader class. Closes the file stream if it is open.
 */
FileStreamReader::~FileStreamReader()
	{
		m_Stream.close();
	}
	/**
 * @brief Reads data from the stream into a buffer.
 *
 * This function reads 'Size' bytes of data from the file stream into the character array pointed to by 'Data'. 
 * The read operation is performed using the standard library method std::basic_istream<char>::read().
 * If successful, it returns true; otherwise, false.
 *
 * @param Data Pointer to a buffer where the data will be stored.
 * @param Size Number of bytes to read from the stream.
 * @return True if the operation was successful, false otherwise.
 */
bool FileStreamReader::ReadData(char* Data, size_t Size)
	{
#if __clang__
		m_Stream.read(Data, (long)Size);
#else
		m_Stream.read(Data, Size);
#endif
		return true;
	}

	/**
 * @brief Reads a specified number of bytes from the stream into a vector.
 * 
 * This function reads 'Size' bytes from the underlying stream and stores them in the provided vector, 'Data'. The data is read as raw byte values (std::byte), so it can be used with any type that requires byte-level access.
 * 
 * @param Data A reference to a std::vector of std::bytes where the read bytes will be stored.
 * @param Size The number of bytes to read from the stream.
 * @return bool Returns true if the operation was successful, false otherwise (e.g., end-of-file or error).
 */
bool FileStreamReader::ReadBytes(std::vector<std::byte>& Data, size_t Size)
	{
#if __clang__
		m_Stream.read(reinterpret_cast<char*>(Data.data()), (long)Size);
#else
		m_Stream.read(reinterpret_cast<char*>(Data.data()), Size);
#endif
		return true;
	}

	/**
 * @brief Reads a specified number of bytes from the stream into a buffer.
 * 
 * This function reads a specified number of bytes from the underlying input stream into a provided buffer. The size of the data read is determined by the 'Size' parameter.
 * 
 * @param Data A pointer to the buffer where the read data will be stored.
 * @param Size The number of bytes to read from the stream.
 * @return Returns true if the operation was successful, false otherwise. In this case, it always returns true as there is no way for an error to occur in this function.
 */
bool FileStreamReader::ReadBytes(uint8_t* Data, size_t Size)
	{
#if __clang__
		m_Stream.read(reinterpret_cast<char*>(Data), (long)Size);
#else
		m_Stream.read(reinterpret_cast<char*>(Data), Size);
#endif
		return true;
	}

	/**
 * @brief Constructor for MemoryStreamReader class. Initializes a memory stream reader with the given address and size.
 * @param Addr Pointer to the start of the data buffer.
 * @param Size The size of the data in bytes.
 */
MemoryStreamReader::MemoryStreamReader(void* Addr, size_t Size)
		:m_Addr(Addr)
	{
		std::string s((char*)m_Addr, Size);
		m_Stream = std::istringstream(s);
	}
	/**
 * @brief Destructor for MemoryStreamReader class. Clears the stream of any error flags.
 */
MemoryStreamReader::~MemoryStreamReader()
	{
		m_Stream.clear();
	}
	/**
 * @brief Reads data from the stream into a buffer.
 *
 * This function reads 'Size' bytes of data from the stream and stores it in the buffer pointed to by 'Data'. 
 * The function returns true if successful, false otherwise.
 *
 * @param Data Pointer to the buffer where the read data will be stored.
 * @param Size Number of bytes to read from the stream.
 * @return True if successful, false otherwise.
 */
bool MemoryStreamReader::ReadData(char* Data, size_t Size)
	{
#if __clang__
		m_Stream.read(Data, (long)Size);
#else
		m_Stream.read(Data, Size);
#endif
		return true;
	}

	/**
 * @brief Reads a specified number of bytes from the stream into a vector.
 * 
 * This function reads a specified number of bytes from the underlying stream and stores them in a provided vector. The data is read as raw byte values, so it can be used with any type that supports std::byte.
 * 
 * @param Data A reference to a vector where the read bytes will be stored.
 * @param Size The number of bytes to read from the stream.
 * @return Always returns true. In future this may change if we decide to add error handling for when not enough data is available in the stream.
 */
bool MemoryStreamReader::ReadBytes(std::vector<std::byte>& Data, size_t Size)
	{
#if __clang__
		m_Stream.read(reinterpret_cast<char*>(Data.data()), (long)Size);
#else
		m_Stream.read(reinterpret_cast<char*>(Data.data()), Size);
#endif
		return true;
	}

	/**
 * @brief Reads a specified number of bytes from the stream into a buffer.
 * 
 * This function reads a specified number of bytes from the underlying input stream, storing them in a provided buffer. The size of the data read is determined by the 'Size' parameter.
 * 
 * @param Data Pointer to the buffer where the read data will be stored.
 * @param Size Number of bytes to read from the stream.
 * @return Returns true if the operation was successful, false otherwise (e.g., end of file).
 */
bool MemoryStreamReader::ReadBytes(uint8_t* Data, size_t Size)
	{
#if __clang__
		m_Stream.read(reinterpret_cast<char*>(Data), (long)Size);
#else
		m_Stream.read(reinterpret_cast<char*>(Data), Size);
#endif
		return true;
	}

	/**
 * @brief Reads a JSON string from the memory stream.
 * 
 * This function attempts to read a JSON string from the memory stream and stores it in the provided string reference parameter.
 * If successful, the function returns true; otherwise, false is returned.
 * 
 * @param[out] String A reference to a std::string object where the JSON string will be stored.
 * @return bool Returns true if the operation was successful, and false otherwise.
 */
bool MemoryStreamReader::ReadJson(std::string& String)
	{
		return false;
	}

	/**
 * @brief Reads data from the buffer. If size is zero, it reads a uint32_t to determine the size of the data to read next.
 * 
 * @param Data Pointer to the buffer where the data will be stored.
 * @param Size The size of the data to read. If this is zero, it means that the size of the data is expected to follow in a uint32_t format.
 */
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
	/**
 * @brief Reads a string from the data source.
 *
 * This function reads a string from the data source, resizing the input string to match the size of the read data and assigning it the value of the read data. 
 *
 * @param[out] String The string to be read into.
 */
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
	/**
 * @brief Reads a JSON string from the stream and stores it in the provided string reference.
 * The size of the JSON string is read first, then the actual data is read into a string of that size.
 * 
 * @param[out] String Reference to a string where the JSON data will be stored.
 * @return True if successful, false otherwise.
 */
bool FileStreamReader::ReadJson(std::string& String)
	{
		size_t Sizet = 0;
		std::string In;
		ReadData((char*)&Sizet, sizeof(size_t));
		In.resize(Sizet);
		std::fill(&In[0], &In[Sizet-1], 0);

#if __clang__
		m_Stream.read(&In[0], (long)Sizet);
#else
		m_Stream.read(&In[0], Sizet);
#endif
		String = In.data();

		return true;
	}
}