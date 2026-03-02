#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Log.h"

namespace AGE
{
	struct Buffer;
	
	class DataWriter
	{
	public:

		virtual ~DataWriter() = default;

		virtual bool IsStreamGood() const = 0;
		virtual uint64_t GetStreamPosition() = 0;
		virtual void SetStreamPosition(uint64_t Pos) = 0;
		virtual bool WriteData(const char* Data, size_t Size) = 0;

		operator bool() const { return IsStreamGood(); }

		void WriteBuffer(Buffer buffer, bool WriteSize = true);
		void WriteZero(uint64_t Size);
		void WriteString(const std::string& String);


		template<typename T>
		void WriteRaw(const T& Type)
		{
			bool success = WriteData((char*)&Type, sizeof(T));
			GameLogger::Assert(success, "Failed to Write Data");
		}

		template<typename T>
		void WriteObject(const T& Obj)
		{
			T::Serialize(this, Obj);
		}

		template<typename Key, typename Value>
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

		FileStreamWriter() = default;
		FileStreamWriter(const std::filesystem::path& Path);
		FileStreamWriter(const FileStreamWriter&) = delete;

		virtual ~FileStreamWriter();

		bool IsStreamGood() const final { return m_Stream.good(); }
		//On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
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
		MemoryStreamWriter(const MemoryStreamWriter&) = delete;

		virtual ~MemoryStreamWriter();

		bool IsStreamGood() const final { return m_Stream.good(); }
		//On clang we return UINT64_MAX to indicate a failure, so if compiling with clang be sure to check for that
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
		void SetStreamPosition(uint64_t Pos) final { m_Stream.seekp((long)Pos); }
		bool WriteData(const char* Data, size_t Size) final;

	private:

		void* m_Addr;
		std::stringstream m_Stream;
	};
}