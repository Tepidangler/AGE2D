#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Log.h"

namespace AGE
{
	struct Buffer;
	
	class DataWriter
	{
	public:

		/**
 * @brief Virtual destructor for the DataWriter class.
 *
 * This function is responsible for freeing any resources that were allocated by the DataWriter object, such as memory or file handles. It does not return anything (void) and thus it doesn't need a Doxygen comment to explain its behavior.
 */
/**
 * @brief Virtual destructor for the DataWriter class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not return anything and has no parameters.
 */
virtual ~DataWriter() = default;

		virtual bool IsStreamGood() const = 0;
		virtual uint64_t GetStreamPosition() = 0;
		virtual void SetStreamPosition(uint64_t Pos) = 0;
		virtual bool WriteData(const char* Data, size_t Size) = 0;

		/**
 * @brief Checks the state of the stream.
 *
 * This function returns a boolean value indicating whether or not the underlying stream is in a good state. It does this by calling the private method `IsStreamGood()`, which should be implemented elsewhere in the class.
 *
 * @return A boolean value indicating if the stream is in a good state.
 */
/**
 * @brief Checks the state of the stream.
 *
 * This function returns a boolean value indicating whether or not the stream is in a good state. It does this by calling the private method `IsStreamGood()`, which should be implemented elsewhere in the class. 
 *
 * @return bool - Returns true if the stream is in a good state, false otherwise.
 */
operator bool() const { return IsStreamGood(); }

		void WriteBuffer(Buffer buffer, bool WriteSize = true);
		void WriteZero(uint64_t Size);
		void WriteString(const std::string& String);


		template<typename T>
		/**
 * @brief Writes raw data of a specific type.
 *
 * This function writes raw data into the game file using the `WriteData` method. It takes an object of any type as input and converts it to a byte array before writing it. 
 * The size of this byte array is determined by the sizeof operator, which allows for different types to be handled uniformly.
 *
 * @param Type An object of any type that can be converted into raw data.
 * @return void
 */
/**
 * @brief Writes raw data of a specific type.
 *
 * This function writes raw data into the game file using the provided data and its size. It ensures that all data is written correctly by checking if the write operation was successful.
 * 
 * @param Type The reference to the data to be written.
 * @return void
 */
void WriteRaw(const T& Type)
		{
			bool success = WriteData((char*)&Type, sizeof(T));
			GameLogger::Assert(success, "Failed to Write Data");
		}

		template<typename T>
		/**
 * @brief This function writes an object to the stream by serializing it.
 * 
 * @param const T& Obj - The reference to the object that needs to be written.
 */
/**
 * @brief This function writes an object to the stream by serializing it using a static method.
 * 
 * @param const T& Obj - A constant reference to the object that needs to be written. The type of this object must have a Serialize() method defined for it.
 */
void WriteObject(const T& Obj)
		{
			T::Serialize(this, Obj);
		}

		template<typename Key, typename Value>
		/**
 * @brief Writes a map to the underlying storage.
 * 
 * This function writes a given map to the underlying storage. If WriteSize is true, it first writes the size of the map. Then for each key-value pair in the map, it checks if the Key and Value types are trivial (i.e., they can be copied using memcpy). If so, it directly writes them; otherwise, it uses a more complex serialization method.
 * 
 * @param Map The map to write.
 * @param WriteSize Whether or not to write the size of the map first. Defaults to true.
 * 
 * @return void
 */
/**
 * @brief Writes a map to the stream. If WriteSize is true, it writes the size of the map first. Then for each pair in the map, 
 *        if Key and Value are trivial types, they are written directly; otherwise, WriteObject function is used.
 * @param Map The map to be written.
 * @param WriteSize If true, write the size of the map before writing pairs. Defaults to true.
 */
void WriteMap(const std::map<Key, Value>& Map, bool WriteSize = true)
		{
			if (WriteSize)
			{
				WriteRaw<uint32_t>((uint32_t)Map.size());
			}

			for (const auto& [K, V] : Map)
			{
				if constexpr (std::is_trivial<Key>())
				{
					WriteRaw<Key>(K);
				}
				else
				{
					WriteObject<Key>(K);
				}

				if constexpr (std::is_trivial<Value>())
				{
					WriteRaw<Value>(V);
				}
				else
				{
					WriteObject<Value>(V);
				}
			}
		}

		template<typename Key, typename Value>
		/**
 * @brief This function writes an unordered map to a data stream. It can optionally write the size of the map as well.
 * 
 * @param Map The unordered map to be written.
 * @param WriteSize A flag indicating whether or not to write the size of the map. Defaults to true.
 */
/**
 * @brief Writes a map to the underlying storage.
 * 
 * This function writes an unordered_map to the underlying storage. If WriteSize is true, it first writes the size of the map. Then for each key-value pair in the map, if the key and value types are trivial (i.e., they can be copied using memcpy), it directly writes them; otherwise, it uses a more complex serialization method.
 * 
 * @param Map The unordered_map to write.
 * @param WriteSize Whether or not to write the size of the map first. Defaults to true.
 * @return void
 */
void WriteMap(const std::unordered_map<Key, Value>& Map, bool WriteSize = true)
		{
			if (WriteSize)
			{
				WriteRaw<uint32_t>((uint32_t)Map.size());
			}

			for (const auto& [K, V] : Map)
			{
				if constexpr (std::is_trivial<Key>())
				{
					WriteRaw<Key>(K);
				}
				else
				{
					WriteObject<Key>(K);
				}

				if constexpr (std::is_trivial<Value>())
				{
					WriteRaw<Value>(V);
				}
				else
				{
					WriteObject<Value>(V);
				}
			}
		}

		template<typename Value>
		/**
 * @brief Writes a map to the stream. If WriteSize is true, it writes the size of the map first. Then for each key-value pair in the map, it writes the key as a string and the value. For trivial types, it directly writes the value using WriteRaw. For non-trivial types, it uses WriteObject.
 * @param Map The unordered_map to write.
 * @param WriteSize Whether or not to write the size of the map first. Defaults to true.
 * @return None
 */
/**
 * @brief Writes a map to the stream. If WriteSize is true, it writes the size of the map first. 
 *        Then for each key-value pair in the map, it writes the key and value. For non-trivial types, 
 *        it uses WriteObject function, otherwise it directly writes the value using WriteRaw function.
 * @param Map The unordered_map to be written.
 * @param WriteSize A flag indicating whether or not to write the size of the map first. Defaults to true.
 * @return None
 */
void WriteMap(const std::unordered_map<std::string, Value>& Map, bool WriteSize = true)
		{
			if (WriteSize)
			{
				WriteRaw<uint32_t>((uint32_t)Map.size());
			}

			for (const auto& [K, V] : Map)
			{
				WriteString(K);

				if constexpr (std::is_trivial<Value>())
				{
					WriteRaw<Value>(V);
				}
				else
				{
					WriteObject<Value>(V);
				}
			}
		}

		template<typename T>
		/**
 * @brief Writes an array to a stream.
 * 
 * This function writes the elements of an array to a stream, optionally also writing its size. The type T must be trivially serializable or have a custom serialization method.
 * 
 * @param Array The array to write.
 * @param WriteSize If true, the size of the array will be written first. Defaults to true.
 */
/**
 * @brief Writes an array to a data stream.
 * 
 * This function writes the elements of an array to a data stream, optionally including its size as well. The type `T` is expected to be trivially copyable or serializable. If it's not, then the object-specific write method (WriteObject<T>) will be used instead.
 * 
 * @param Array A const reference to the array that should be written.
 * @param WriteSize An optional boolean indicating whether the size of the array should also be written. Default is true.
 */
void WriteArray(const std::vector<T>& Array, bool WriteSize = true)
		{
			if (WriteSize)
			{
				WriteRaw<uint32_t>((uint32_t)Array.size());
			}

			for (const auto& E : Array)
			{
				if constexpr (std::is_trivial<T>())
				{
					WriteRaw<T>(E);
				}
				else
				{
					WriteObject<T>(E);
				}
			}

		}
	};


	class FileStreamWriter : public DataWriter
	{
	public:

		/**
 * @brief Default constructor for FileStreamWriter class.
 * 
 * This function initializes an instance of the FileStreamWriter class with default settings. It does not take any parameters and returns no value.
 */
/**
 * @brief Default constructor for FileStreamWriter class.
 *
 * This function initializes an instance of the FileStreamWriter class with default values. It does not take any parameters and returns nothing.
 */
FileStreamWriter() = default;
		FileStreamWriter(const std::filesystem::path& Path);
		/**
 * @brief This function is a copy constructor for the FileStreamWriter class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param other The object to be copied.
 * @return No return value as this function throws an exception if called.
 */
/**
 * @brief This function is a copy constructor for the FileStreamWriter class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param other The object to be copied.
 * 
 * @return No return value as this function does not provide any meaningful output.
 */
FileStreamWriter(const FileStreamWriter&) = delete;

		virtual ~FileStreamWriter();

		/**
 * @brief Checks the state of the stream.
 *
 * This function checks whether the underlying stream is in a good state, i.e., it has not encountered any errors or reaching EOF.
 *
 * @return A boolean value indicating if the stream is in a good state (true) or not (false).
 */
/**
 * @brief Checks the state of the stream object.
 *
 * This function returns a boolean value indicating whether the stream is in a good state or not. The state of the stream can be determined by calling the `std::basic_ios::good` method on the underlying stream buffer.
 * 
 * @return A boolean value that indicates if the stream is in a good state (true) or not (false).
 */
bool IsStreamGood() const final { return m_Stream.good(); }
		//On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
		/**
 * @brief Get the current position in the stream.
 * 
 * This function returns the current position within the stream. If an error occurs while trying to get the position, it will return UINT64_MAX.
 * 
 * @return uint64_t The current position in the stream. Returns UINT64_MAX if there was an error getting the position.
 */
/**
 * @brief Get the current position of the stream in bytes.
 * 
 * This function retrieves the current position within the stream, which is typically a file pointer or similar. The return value is cast to uint64_t for compatibility with large files.
 * If the tellp() call fails (e.g., due to an error condition), it returns UINT64_MAX to indicate such a failure.
 * 
 * @return uint64_t Current position within the stream in bytes, or UINT64_MAX if the operation failed.
 */
uint64_t GetStreamPosition() final
		{
#if __clang__
			long pos = m_Stream.tellp();
			if (pos == -1) // -1 Indicated a failure per clang implementation
			{
				return UINT64_MAX;
			}
			return static_cast<uint64_t>(pos);
#else
			return m_Stream.tellp();
#endif
		}
		/**
 * @brief Sets the stream position to a specified value.
 *
 * This function sets the current read/write position in the stream to a specific point, defined by an unsigned 64-bit integer parameter 'Pos'.
 * The new position is calculated as (long)Pos, which means it will be truncated if Pos exceeds the maximum value that can be stored in a long.
 *
 * @param[in] Pos - The desired position to set in the stream.
 */
/**
 * @brief Sets the stream position to a specific value.
 *
 * This function sets the current read/write position in the stream to the specified position.
 * The new position is relative to the beginning of the file, which is at offset 0.
 *
 * @param Pos The desired position in the stream, measured in bytes from the start of the file.
 */
void SetStreamPosition(uint64_t Pos) final { m_Stream.seekp((long)Pos); }
		bool WriteData(const char* Data, size_t Size) final;

	private:

		std::filesystem::path m_Path;
		std::ofstream m_Stream;
	};

	class MemoryStreamWriter : public DataWriter
	{
	public:

		MemoryStreamWriter(void* Addr);
		/**
 * @brief This is a copy constructor for the MemoryStreamWriter class. It's marked as deleted to prevent copying of objects.
 * 
 * @param other The object to be copied.
 */
/**
 * @brief This is a copy constructor for the MemoryStreamWriter class. It's marked as deleted to prevent copying of objects.
 * @param other The object to be copied.
 */
MemoryStreamWriter(const MemoryStreamWriter&) = delete;

		virtual ~MemoryStreamWriter();

		/**
 * @brief Checks the state of the stream object.
 *
 * This function checks whether the underlying input/output operations on the stream are good or not.
 * It returns true if the stream is in a good state, false otherwise.
 *
 * @return True if the stream is in a good state, false otherwise.
 */
/**
 * @brief Checks the state of the stream.
 *
 * This function checks whether the underlying stream is in a good state, i.e., it has no errors or failures that would prevent further operations on it.
 *
 * @return True if the stream is in a good state, false otherwise.
 */
bool IsStreamGood() const final { return m_Stream.good(); }
		//On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
		/**
 * @brief Get the current position of the stream in bytes.
 * 
 * This function retrieves the current position within a stream object, which is useful for determining how much data has been written to the stream so far. The return value is always non-negative and represents the number of characters successfully read from the stream buffer. If an error occurs during reading (e.g., end of file), it returns UINT64_MAX indicating failure.
 * 
 * @return uint64_t Current position in bytes, or UINT64_MAX if there was an error.
 */
/**
 * @brief Get the current position in the stream
 * 
 * This function retrieves the current position within a stream. It returns this as an unsigned 64-bit integer. If the tellp() call fails, it will return UINT64_MAX to indicate failure.
 * 
 * @return uint64_t The current position in the stream
 */
uint64_t GetStreamPosition() final
		{
#if __clang__
			long pos = m_Stream.tellp();
			if (pos == -1) // -1 Indicated a failure per clang implementation
			{
				return UINT64_MAX;
			}
			return static_cast<uint64_t>(pos);
#else
			return m_Stream.tellp();
#endif
		}
		/**
 * @brief Sets the stream position to a specified value.
 *
 * This function sets the current read/write position in the stream to the provided position.
 * The new position is calculated as an offset from the beginning of the file, which is given by the parameter 'Pos'.
 * 
 * @param Pos The new position to set in the stream.
 */
/**
 * @brief Sets the stream position to a specified value.
 *
 * This function sets the current read/write position in the stream to the provided position.
 * The new position is calculated as an offset from the beginning of the file, measured in bytes.
 *
 * @param Pos The desired position in the stream, measured in bytes.
 */
void SetStreamPosition(uint64_t Pos) final { m_Stream.seekp((long)Pos); }
		bool WriteData(const char* Data, size_t Size) final;

	private:

		[[maybe_unused]] void* m_Addr;
		std::stringstream m_Stream;
	};
}