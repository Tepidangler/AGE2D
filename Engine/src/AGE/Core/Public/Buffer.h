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

		Buffer()
			: Data(nullptr), Size(0)
		{

		}

		Buffer(const void* data, uint64_t size = 0)
			:Data((void*)data), Size(size)
		{

		}

		static Buffer Copy(const Buffer& Other)
		{
			Buffer buffer;
			buffer.Allocate(Other.Size);
			memcpy(buffer.Data, Other.Data, Other.Size);
			return buffer;
		}

		static Buffer Copy(const void* data, uint64_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

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

		void Release()
		{
			delete[](char*) Data;
			Data = nullptr;
			Size = 0;
		}

		void ZeroInitialize()
		{
			if (Data)
			{
				memset(Data, 0, Size);
			}
		}

		template<typename T>
		T& Read(uint64_t offset = 0)
		{
			return *(T*)((char*)Data + offset);
		}

		char* ReadBytes(uint64_t size, uint64_t offset) const
		{
			CoreLogger::Assert(offset + size <= Size, "Buffer Overflow!");
			char* buf = new char [size];
			memcpy(buf, (char*)Data + offset, size);
			return buf;
		}

		void Write(const void* data, uint64_t size, uint64_t offset = 0)
		{
			CoreLogger::Assert(offset + size <= Size, "Buffer Overflow!");
			memcpy((char*)Data + offset, data, size);
		}

		operator bool() const
		{
			return (bool)Data;
		}

		char& operator[](int Index)
		{
			return ((char*)Data)[Index];
		}

		static void Serialize(DataWriter* Serializer, const Buffer& Instance)
		{
			Serializer->WriteRaw<uint8_t>(*(uint8_t*)Instance.Data);
			Serializer->WriteRaw<uint64_t>(Instance.Size);
		}

		static void Deserialize(DataReader* Deserializer, Buffer& Instance)
		{
			uint8_t Bytes;
			Deserializer->ReadRaw<uint8_t>(Bytes);
			Deserializer->ReadRaw<uint64_t>(Instance.Size);

			Instance.Allocate(Instance.Size);
			Instance.Write((void*)Bytes, Instance.Size, 0);
		}

	};
}