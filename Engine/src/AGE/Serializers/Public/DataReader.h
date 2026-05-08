#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Log.h"

namespace AGE
{
	class DataReader
	{
	public:
		/**
 * @brief Virtual destructor for the DataReader class.
 *
 * This function is responsible for releasing any resources that were acquired by the DataReader instance, such as memory or file handles. It does not return anything and has no parameters. 
 */
virtual ~DataReader() = default;

		virtual bool IsStreamGood() const = 0;
		virtual uint64_t GetStreamPosition() = 0;
		virtual void SetStreamPosition(uint64_t Pos) = 0;
		virtual bool ReadData(char* Data, size_t Size) = 0;
		virtual bool ReadBytes(std::vector<std::byte>& Data, size_t Size) = 0;
		virtual bool ReadBytes(uint8_t* Data, size_t Size) =0;
		virtual bool ReadJson(std::string& String) = 0;

		/**
 * @brief Checks the state of the stream.
 *
 * This function returns a boolean value indicating whether or not the stream is in a good state. It does this by calling the private method `IsStreamGood()`, which should be implemented elsewhere in the codebase.
 * 
 * @return True if the stream is in a good state, false otherwise.
 */
operator bool() const { return IsStreamGood(); }

		void ReadBuffer(char* Data, size_t Size);
		void ReadString(std::string& String);


		template<typename T>
		/**
 * @brief This function reads raw data into a specified type.
 *
 * The function takes a reference to the variable of type T and attempts to read data from an underlying source into it. If successful, it asserts that the operation was successful; if not, it throws an exception with the message "Failed to Read Data". 
 *
 * @param Type A reference to the variable where the raw data will be stored.
 * @return void
 */
void ReadRaw(T& Type)
		{
			bool success = ReadData((char*)&Type, sizeof(T));
			GameLogger::Assert(success, "Failed to Read Data");

		}

		template<typename T>
		/**
 * @brief This function reads an object of type T from the stream using Deserialize method.
 * 
 * @param[out] Obj The object to be read into.
 * @return void
 */
void ReadObject(T& Obj)
		{
			T::Deserialize(this, Obj);
		}


		template<typename Key, typename Value>
		/**
 * @brief Reads a map from the input stream.
 * 
 * This function reads a map of keys and values from the input stream. If the size is not provided, it will read it first. The key type can be any trivial or non-trivial type that has been defined for serialization. The value type must also be either trivial or non-trivial. It uses ReadRaw to read raw data if the key or value types are trivial and ReadObject otherwise.
 * 
 * @param Map Reference to the map to be populated with keys and values.
 * @param Size Optional parameter specifying the size of the map. If not provided, it will be read first.
 */
void ReadMap(std::map<Key, Value>& Map, uint32_t Size = 0)
		{
			if (Size == 0)
			{
				ReadRaw<uint32_t>(Size);
			}

			for (uint32_t i =0; i < Size; i++)
			{
				Key K;
				if constexpr (std::is_trivial<Key>())
				{
					ReadRaw<Key>(K);
				}
				else
				{
					ReadObject<Key>(K);
				}

				if constexpr (std::is_trivial<Value>())
				{
					ReadRaw<Value>(Map[K]);
				}
				else
				{
					ReadObject<Value>(Map[K]);
				}
			}
		}

		template<typename Key, typename Value>
		/**
 * @brief Reads a map from the input stream.
 * 
 * This function reads a map of keys and values from the input stream. If the size is not provided, it will read the size first. For each key-value pair, if the key or value type is trivial (like int, float etc.), it uses `ReadRaw` to read them directly; otherwise, it uses `ReadObject` to read them.
 * 
 * @param Map The map to be filled with keys and values from the input stream.
 * @param Size Optional parameter specifying the size of the map. If not provided, it will be read first.
 */
void ReadMap(std::unordered_map<Key, Value>& Map, uint32_t Size = 0)
		{
			if (Size == 0)
			{
				ReadRaw<uint32_t>(Size);
			}

			for (uint32_t i = 0; i < Size; i++)
			{
				Key K;
				if constexpr (std::is_trivial<Key>())
				{
					ReadRaw<Key>(K);
				}
				else
				{
					ReadObject<Key>(K);
				}

				if constexpr (std::is_trivial<Value>())
				{
					ReadRaw<Value>(Map[K]);
				}
				else
				{
					ReadObject<Value>(Map[K]);
				}
			}
		}

		template<typename Key, typename Value>
		/**
 * @brief Reads a map from the input stream. The size of the map is read if not provided as an argument. 
 *        If the key and value types are trivial, raw data is read directly; otherwise, objects are read.
 * @param Map The unordered_map to be populated with the data read from the input stream.
 * @param Size The size of the map. Defaults to 0 if not provided.
 * @return void
 */
void ReadMap(std::unordered_map<std::string, Value>& Map, uint32_t Size = 0)
		{
			if (Size == 0)
			{
				ReadRaw<uint32_t>(Size);
			}

			for (uint32_t i = 0; i < Size; i++)
			{
				Key K;
				if constexpr (std::is_trivial<Key>())
				{
					ReadRaw<Key>(K);
				}
				else
				{
					ReadObject<Key>(K);
				}

				if constexpr (std::is_trivial<Value>())
				{
					ReadRaw<Value>(Map[K]);
				}
				else
				{
					ReadObject<Value>(Map[K]);
				}
			}
		}

		template<typename T>
		/**
 * @brief Reads an array of elements from the input stream. 
 * If the size is not provided, it reads the size first and then the array.
 * The function uses C++14's std::is_trivial to determine whether T is a trivial type or not.
 * For trivial types, it directly reads into the array element using ReadRaw.
 * For non-trivial types, it uses ReadObject.
 * 
 * @param Array Reference to the vector that will hold the read elements.
 * @param Size The size of the array. If zero, the function first reads the size.
 * 
 * @return void
 */
void ReadArray(std::vector<T>& Array, uint32_t Size = 0)
		{
			if (Size == 0)
			{
				ReadRaw<uint32_t>(Size);
				Array.resize(Size);
			}
			else
			{
				Array.resize(Size);
			}

			for (uint32_t i = 0; i < Size; i++)
			{
				if constexpr (std::is_trivial<T>())
				{
					ReadRaw<T>(Array[i]);
				}
				else
				{
					ReadObject<T>(Array[i]);
				}
			}

		}

	};


	class FileStreamReader : public DataReader
	{
	public:
		/**
 * @brief Default constructor for the FileStreamReader class.
 *
 * This function initializes a new instance of the FileStreamReader class with default settings. It does not open any file or stream, but sets up the object to handle reading from files and streams in the future.
 *
 * @return A new instance of the FileStreamReader class with no associated file or stream.
 */
FileStreamReader() = default;
		FileStreamReader(const std::filesystem::path& Path);
		/**
 * @brief This function is a copy constructor for the FileStreamReader class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param other The object to be copied from.
 * 
 * @return No return value as this function does not return anything.
 */
FileStreamReader(const FileStreamReader&) = delete;

		virtual ~FileStreamReader();

		/**
 * @brief Checks the state of the stream object.
 *
 * This function checks whether the underlying input/output operations on the stream are good or not.
 * It returns true if the stream is in a good state, false otherwise.
 *
 * @return A boolean value indicating the health of the stream. True means the stream is in a good state, while false indicates an error has occurred.
 */
bool IsStreamGood() const final { return m_Stream.good(); }
		/*
		 * On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
		 */
		/**
 * @brief Get the current position of the stream.
 * 
 * This function returns the current position in the stream. If the tellg() call fails, it will return UINT64_MAX to indicate an error.
 * 
 * @return uint64_t The current position in the stream.
 */
uint64_t GetStreamPosition() final
		{
#if __clang__
			long pos = m_Stream.tellg();
			if (pos == -1) // -1 Indicated a failure per clang implementation
			{
				return UINT64_MAX;
			}
			return static_cast<uint64_t>(pos);
#else
			return m_Stream.tellg();
#endif
		}
		/**
 * @brief This function sets the stream position to a specific value.
 * @param Pos The new position in bytes from the beginning of the stream.
 */
void SetStreamPosition(uint64_t Pos) final { m_Stream.seekg((long)Pos); }
		bool ReadData(char* Data, size_t Size) final;
		bool ReadBytes(std::vector<std::byte>& Data, size_t Size) final;
		bool ReadBytes(uint8_t* Data, size_t Size) final;
		bool ReadJson(std::string& String) final;


	private:

		std::filesystem::path m_Path;
		std::ifstream m_Stream;

	};

	class MemoryStreamReader : public DataReader
	{
	public:

		MemoryStreamReader(void* Addr, size_t Size);
		/**
 * @brief Constructs a new instance of the MemoryStreamReader class using an existing memory stream.
 * 
 * The constructor takes in a reference to an existing memory stream and sets it as the source for reading data. It also initializes the read position to zero.
 * 
 * @param mem_stream A reference to an existing memory stream that will be used as the source of data.
 */
MemoryStreamReader(const MemoryStreamReader&) = delete;

		virtual ~MemoryStreamReader()
		;

		/**
 * @brief Checks the state of the stream.
 *
 * This function checks whether the underlying input/output stream is in a good state, i.e., it has no errors or failures that would prevent further operations on it.
 * 
 * @return A boolean value indicating if the stream is in a good state (true) or not (false).
 */
bool IsStreamGood() const final { return m_Stream.good(); }

//On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
		/**
 * @brief Get the current position of the stream.
 * 
 * This function returns the current position in the stream. If an error occurs while trying to get the position, it will return UINT64_MAX.
 * The behavior is platform-dependent and depends on whether __clang__ is defined or not. For Clang, if tellg() fails (returns -1), 
 * this function returns UINT64_MAX. Otherwise, it converts the result to uint64_t and returns it. For other platforms, it simply calls 
 * tellg(). This means that the return value is always a valid position in the stream.
 * 
 * @return The current position of the stream as an unsigned 64-bit integer. If an error occurs while trying to get the position, UINT64_MAX is returned.
 */
uint64_t GetStreamPosition() final
		{
#if __clang__
			long pos = m_Stream.tellg();
			if (pos == -1) // -1 Indicated a failure per clang implementation
			{
				return UINT64_MAX;
			}
			return static_cast<uint64_t>(pos);
#else
			return m_Stream.tellg();
#endif
		}
		/**
 * @brief This function sets the stream position to a specified value.
 * 
 * @param Pos The new position in bytes from the beginning of the stream.
 */
void SetStreamPosition(uint64_t Pos) final { m_Stream.seekg((long)Pos); }
		bool ReadData(char* Data, size_t Size) final;
		bool ReadBytes(std::vector<std::byte>& Data, size_t Size) final;
		bool ReadBytes(uint8_t* Data, size_t Size) final;
		bool ReadJson(std::string& String) final;
	private:

		void* m_Addr;
		std::string m_String;
		std::istringstream m_Stream;
	};
}