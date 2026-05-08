#include "AGEpch.hpp"
#include "Serializers/Public/DataWriter.h"
#include "Core/Public/Buffer.h"

namespace AGE
{
	/**
 * @brief Constructs a FileStreamWriter object with the given file path.
 * 
 * This constructor opens an output stream to the specified file path using binary mode. If the file does not exist, it will be created when data is written to the stream.
 * 
 * @param Path The path of the file to open or create.
 */
FileStreamWriter::FileStreamWriter(const std::filesystem::path& Path)
		:m_Path(Path)
	{
		m_Stream = std::ofstream(Path, std::ofstream::out | std::ofstream::binary);
	}
	/**
 * @brief Destructor for the FileStreamWriter class. Closes the file stream associated with this object.
 */
FileStreamWriter::~FileStreamWriter()
	{
		m_Stream.close();
	}
	/**
 * @brief Writes data to the file stream.
 *
 * This function writes a block of data of specified size into the file stream. 
 * It takes in a pointer to the data and its size, then writes that data into the file stream.
 * The function returns true if the write operation is successful, false otherwise.
 *
 * @param Data Pointer to the data to be written.
 * @param Size Size of the data to be written.
 * @return True if the write operation was successful, false otherwise.
 */
bool FileStreamWriter::WriteData(const char* Data, size_t Size)
	{
#if __clang__
		m_Stream.write(Data, (long)Size);
#else
		m_Stream.write(Data, Size);
#endif
		return true;
	}
	/**
 * @brief Writes a buffer to the data stream.
 * 
 * This function writes a given buffer to the data stream. If the WriteSize parameter is true, it will first write the size of the buffer to the stream. The buffer's data and its size are then written to the stream.
 * @param buffer The buffer to be written.
 * @param WriteSize A flag indicating whether or not to write the size of the buffer to the stream.
 * 
 * @return void
 */
void DataWriter::WriteBuffer(Buffer buffer, bool WriteSize)
	{
		if (WriteSize)
		{
			WriteData((char*)&buffer.Size, sizeof(uint64_t));
		}

		WriteData((char*)buffer.Data, buffer.Size);
	}
	/**
 * @brief Writes a block of zeros to the data stream.
 *
 * This function writes a specified number of zero bytes to the data stream. It uses a loop to write each byte individually.
 *
 * @param Size The number of zero bytes to write.
 */
void DataWriter::WriteZero(uint64_t Size)
	{
		char Zero = 0;
		for (uint64_t i = 0; i < Size; i++)
		{
			WriteData(&Zero, 1);
		}
	}
	/**
 * @brief Writes a string to the data stream, including its length prefix.
 * @param String The string to write.
 * @return None.
 */
void DataWriter::WriteString(const std::string& String)
	{
		//Lol this isn't how it works
		size_t Size = String.length();
		WriteData((char*)&Size, sizeof(size_t));
		WriteData((char*)String.data(), sizeof(char) * Size); //This should probably be String.length() as we should be multiplying the size of a char (1 byte) by the number of chars in the string
	}
	/**
 * @brief Constructs a MemoryStreamWriter object with the given address.
 * 
 * This constructor initializes the memory stream writer with an address to write data into. The mode of the stream is set to binary and out for writing operations.
 * 
 * @param Addr A void pointer representing the starting address in memory where data will be written.
 */
MemoryStreamWriter::MemoryStreamWriter(void* Addr)
		:m_Addr(Addr)
	{
		m_Stream = std::stringstream(std::stringstream::out | std::stringstream::binary);
	}
	/**
 * @brief Destructor for MemoryStreamWriter class. Clears the stream associated with this object.
 */
MemoryStreamWriter::~MemoryStreamWriter()
	{
		m_Stream.clear();
	}
	/**
 * @brief Writes data to the memory stream.
 *
 * This function writes a block of data of specified size into the memory stream. 
 * It takes in a pointer to the data and its size, then writes that data into the stream.
 * The function returns true if the write operation is successful, false otherwise.
 *
 * @param Data Pointer to the data to be written.
 * @param Size Size of the data to be written.
 * 
 * @return True if the write operation was successful, false otherwise.
 */
bool MemoryStreamWriter::WriteData(const char* Data, size_t Size)
	{
#if __clang__
		m_Stream.write(Data, (long)Size);
#else
		m_Stream.write(Data, Size);
#endif

		return true;
	}
}