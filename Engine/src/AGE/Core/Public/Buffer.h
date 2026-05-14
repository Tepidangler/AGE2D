#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Log.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"

namespace AGE
{
	struct Buffer
	{
		void* Data;
		uint64_t Size;

		/**
 * @brief Buffer constructor initializes the data pointer to nullptr and size to 0.
 */
/**
 * @brief Default constructor for the Buffer class. 
 * Initializes an empty buffer with a data pointer set to nullptr and size set to 0.
 */
Buffer()
			: Data(nullptr), Size(0)
		{

		}

		/**
 * @brief Buffer constructor that initializes the buffer with given data and size.
 * @param[in] data Pointer to the data to be stored in the buffer. Can be null.
 * @param[in] size Size of the data pointed by 'data'. Defaults to 0 if not provided.
 */
/**
 * @brief Buffer constructor that initializes the buffer with a given pointer to data and its size.
 * @param data Pointer to the data to be stored in the buffer. Can be null.
 * @param size Size of the data pointed by 'data'. Defaults to 0 if not provided.
 */
Buffer(const void* data, uint64_t size = 0)
			:Data((void*)data), Size(size)
		{

		}

		/**
 * @brief Copies a Buffer object by allocating the same size and copying data from another Buffer object.
 * 
 * @param Other The Buffer object to be copied.
 * @return A new Buffer object with the same size as the input and copied data.
 */
/**
 * @brief Copies a Buffer object by allocating the same size and copying data from another Buffer.
 * 
 * This function creates a new Buffer object with the same size as the input Buffer, then copies the data from the input Buffer into this new one. The copied data is returned as the result of the function.
 * 
 * @param Other The Buffer to be copied.
 * @return A copy of the input Buffer.
 */
static Buffer Copy(const Buffer& Other)
		{
			Buffer buffer;
			buffer.Allocate(Other.Size);
			memcpy(buffer.Data, Other.Data, Other.Size);
			return buffer;
		}

		/**
 * @brief Copies a block of memory into a new Buffer object.
 * 
 * This function creates a new Buffer object and allocates the necessary memory to hold 'size' bytes. It then uses memcpy() to copy 'data' into this newly allocated memory. The copied data can be accessed through the Data property of the returned Buffer object.
 *
 * @param[in] data Pointer to the block of memory to copy.
 * @param[in] size Size in bytes of the block of memory to copy.
 * 
 * @return A new Buffer object containing a copy of 'data'.
 */
/**
 * @brief Copies a block of memory into a new Buffer object.
 * 
 * This function creates a new Buffer object and allocates the necessary memory to hold 'size' bytes. It then uses memcpy() to copy the data from the input pointer into this newly allocated memory. The copied buffer is returned as the result.
 * 
 * @param data A pointer to the block of memory to be copied.
 * @param size The number of bytes to copy from 'data'.
 * 
 * @return A new Buffer object containing a copy of the input data.
 */
static Buffer Copy(const void* data, uint64_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

		/**
 * @brief Allocates memory for an array of characters.
 *
 * This function allocates a block of memory to store an array of characters. If the input size is zero, it simply returns without doing anything. 
 * The allocated memory should be deallocated using Free() when it's no longer needed.
 *
 * @param size The number of elements in the array to be allocated.
 */
/**
 * @brief Allocates memory for an array of pointers to characters.
 *
 * This function allocates a block of memory for an array of `char` pointers. It first deletes the existing data if any, then it checks if the size is zero. If not, it allocates new memory and sets the `Size` variable accordingly.
 * 
 * @param size The number of elements to be allocated.
 */
void Allocate(uint64_t size)
		{
			delete[] (char*)Data;
			Data = nullptr;

			if (size == 0)
			{
				return;
			}

			Data = new char* [size];
			Size = size;
		}

		/**
 * @brief Releases the memory allocated for the data.
 *
 * This function deletes the dynamically allocated array of characters (char*) Data and sets it to null, effectively releasing the memory. It also resets Size to 0 indicating that no more data is present in the object.
 *
 * @return void
 */
/**
 * @brief Releases the memory allocated for the data.
 *
 * This function deletes the dynamically allocated array of characters and sets the Data pointer to null, effectively releasing the memory. It also resets the Size variable to 0 indicating that no more data is present in the object.
 *
 * @return void
 */
void Release()
		{
			delete[](char*) Data;
			Data = nullptr;
			Size = 0;
		}

		/**
 * @brief This function initializes a block of memory with zeros.
 *
 * The function takes no parameters and does not return anything. It uses the memset function from the C standard library to fill the Data array with zeros, which is of size Size. 
 */
/**
 * @brief This function initializes a block of memory with zeros.
 * 
 * The function takes no parameters and returns void. It uses the memset function from the cstring library to fill the Data array with zeros, which is assumed to be of size Size. If Data is null, nothing happens.
 * 
 * @return Void
 */
void ZeroInitialize()
		{
			if (Data)
			{
				memset(Data, 0, Size);
			}
		}

		template<typename T>
		/**
 * @brief This function reads a value of type T from the data buffer at a specified offset.
 * @param[in] offset The position in the data buffer to read from, defaults to 0 if not provided.
 * @return A reference to the value of type T located at the given offset.
 */
/**
 * @brief This function reads a value of type T from the data buffer at a specified offset.
 * @param[in] offset The position in the data buffer to read from, defaults to 0 if not provided.
 * @return A reference to the value of type T located at the given offset.
 */
T& Read(uint64_t offset = 0)
		{
			return *(T*)((char*)Data + offset);
		}

		/**
 * @brief ReadBytes reads a specified number of bytes from the buffer starting at a given offset.
 * 
 * The function checks if the requested read operation will result in a buffer overflow by comparing the sum of the size and offset with the total size of the buffer. If it's larger, an assertion is triggered to indicate a potential issue.
 * It then allocates memory for a new char array of the specified size using 'new', copies the data from the buffer starting at the given offset into this newly allocated memory, and returns a pointer to this memory.
 * 
 * @param size The number of bytes to read.
 * @param offset The position in the buffer where reading should start.
 * @return A pointer to an array containing the read data. This must be deleted by the caller when it's no longer needed.
 * 
 * @throws std::runtime_error if there is a buffer overflow (i.e., the sum of size and offset exceeds the total size of the buffer).
 */
/**
 * @brief ReadBytes reads a specified number of bytes from the buffer starting at a given offset.
 *
 * This function is used to read data from the buffer. It takes two parameters - 'size' which specifies 
 * the number of bytes to be read and 'offset', which indicates the position in the buffer where reading should start.
 * The function checks if the requested size plus the offset exceeds the total size of the buffer, and throws an error if it does.
 * It then allocates a new character array of the specified size using dynamic memory allocation (new char[size]), 
 * copies 'size' bytes from the buffer starting at the given offset to this newly allocated array, and returns this array.
 * The caller is responsible for deallocating the returned pointer with delete[].
 *
 * @param size Number of bytes to read.
 * @param offset Position in the buffer where reading should start.
 * @return Pointer to a new character array containing the read data. Caller must free this memory using 'delete[]'.
 * 
 * @throws std::runtime_error if the requested size plus the offset exceeds the total size of the buffer.
 */
char* ReadBytes(uint64_t size, uint64_t offset) const
		{
			CoreLogger::Assert(offset + size <= Size, "Buffer Overflow!");
			char* buf = new char [size];
			memcpy(buf, (char*)Data + offset, size);
			return buf;
		}

		/**
 * @brief Writes a block of data to the buffer at a specified offset.
 *
 * This function copies 'size' bytes from the memory area pointed by 'data' into the buffer starting at 'offset'. 
 * The destination buffer is assumed to be large enough to hold the copied data, i.e., it should have been allocated with Size bytes of space beforehand.
 * If the sum of 'size' and 'offset' exceeds the total size of the buffer (Size), a buffer overflow error will occur.
 * 
 * @param data Pointer to the source of the data to be copied.
 * @param size Number of bytes to copy from the source.
 * @param offset The number of bytes in the destination buffer at which copying begins. Defaults to 0 if not specified.
 */
/**
 * @brief Writes a block of data to the buffer at a specified offset.
 *
 * This function copies 'size' bytes from the memory area pointed by 'data' into the buffer starting at position 'offset'. 
 * If the sum of 'offset' and 'size' exceeds the total size of the buffer, it results in a "Buffer Overflow!" error.
 *
 * @param data Pointer to the source of the data to be copied.
 * @param size Number of bytes to copy from the source.
 * @param offset Position within the buffer at which copying begins. Defaults to 0 if not provided.
 */
void Write(const void* data, uint64_t size, uint64_t offset = 0)
		{
			CoreLogger::Assert(offset + size <= Size, "Buffer Overflow!");
			memcpy((char*)Data + offset, data, size);
		}

		/**
 * @brief This function returns a boolean value based on the truthiness of Data member.
 * @param None
 * @return Returns true if Data is not null, false otherwise.
 */
/**
 * @brief Converts the object to a boolean value.
 *
 * This function returns true if Data is not null, and false otherwise. It provides an implicit conversion from the class instance to bool.
 *
 * @return True if Data is not null, False otherwise.
 */
operator bool() const
		{
			return (bool)Data;
		}

		/**
 * @brief This function returns a reference to the character at the specified index in the Data array.
 * @param Index The zero-based index of the character to return.
 * @return A reference to the character at the given index.
 */
/**
 * @brief This function returns a reference to the character at the specified index in the Data array.
 * 
 * @param Index The zero-based index of the character to return.
 * @return A reference to the character at the given index.
 */
char& operator[](int Index)
		{
			return ((char*)Data)[Index];
		}

		/**
 * @brief This function serializes a Buffer instance into the provided DataWriter.
 * 
 * The function writes two pieces of data to the DataWriter: the first byte of the buffer and its size.
 * It uses WriteRaw method for writing raw bytes, which means it directly writes the memory content pointed by the pointer without any conversion or serialization process.
 * 
 * @param Serializer Pointer to a DataWriter instance that will be used for serialization.
 * @param Instance The Buffer instance to be serialized.
 */
/**
 * @brief This function serializes a buffer instance into the provided data writer.
 * 
 * The function writes two pieces of information to the data writer: the first byte of the buffer and its size.
 * It uses raw write operations, meaning it directly accesses the memory pointed by the Instance pointer without any additional processing.
 * @param Serializer A pointer to a DataWriter object that will be used for serialization.
 * @param Instance The Buffer instance to be serialized.
 */
static void Serialize(DataWriter* Serializer, const Buffer& Instance)
		{
			Serializer->WriteRaw<uint8_t>(*(uint8_t*)&Instance.Data);
			Serializer->WriteRaw<uint64_t>(Instance.Size);
		}

		/**
 * @brief Deserialize a Buffer instance from a DataReader.
 *
 * This function reads raw data from the provided DataReader and deserializes it into a Buffer instance. The first byte read is stored in an uint8_t variable, which is then used to allocate memory for the buffer. The size of the buffer is read next as an uint64_t. After these two values are obtained, the buffer's memory is allocated and the bytes from the DataReader are written into it.
 *
 * @param Deserializer A pointer to a DataReader instance that provides the raw data for deserialization.
 * @param Instance The Buffer instance where the deserialized data will be stored.
 */
/**
 * @brief Deserialize a Buffer instance from a DataReader.
 * 
 * This function reads raw data from the provided DataReader and deserializes it into a Buffer instance. The first byte read is stored in an uint8_t variable, which is then used to allocate memory for the buffer. The size of the buffer is read next as an uint64_t. After these two values are obtained, the buffer's memory is allocated and the bytes from the DataReader are written into it.
 * 
 * @param Deserializer Pointer to a DataReader instance that provides raw data for deserialization.
 * @param Instance Reference to a Buffer instance where the deserialized data will be stored.
 */
static void Deserialize(DataReader* Deserializer, Buffer& Instance)
		{
			uint8_t Bytes;
			Deserializer->ReadRaw<uint8_t>(Bytes);
			Deserializer->ReadRaw<uint64_t>(Instance.Size);

			Instance.Allocate(Instance.Size);
			Instance.Write((void*)&Bytes, Instance.Size, 0);
		}

	};
}