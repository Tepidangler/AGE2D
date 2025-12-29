#include "AGEpch.hpp"
#include "Sprite/Public/Image.h"
#include "Serializers/Public/DataReader.h"
#include <zlib.h>
#include <stb_image.h>
//TODO:  Note to Self, we have effectively move pixel data to a buffer which represents an image, now we need to work on flipping the image on the y-axis so that the picture is right side up before we pass it to the graphics renderer
namespace AGE
{
	Image::Image(ImageSpecification& Spec, bool FlipVerticallyOnLoad)
		:m_Spec(Spec), bShouldFlip(FlipVerticallyOnLoad)
	{
		switch (Spec.GetPixelType())
		{
		case PixelType::RGBA:
		case PixelType::RGB:
		{
			//https://github.com/aseprite/aseprite/blob/main/src/doc/image_impl.h

			m_RowBytes = sizeof(uint32_t) * m_Spec.GetWidth();
			size_t ForRows = sizeof(uint32_t*) * Spec.GetHeight();
			size_t Size = ForRows + m_RowBytes * Spec.GetHeight();
			m_ByteSize = Size;

			ResizeImage(Spec.GetPixelType(), Size);


			std::fill(m_Buffer, m_Buffer + (Size), 0);

			m_RGBRows = (uint32_t**)m_Buffer;
			m_RGBBits = (uint32_t*)(m_Buffer + ForRows);


			auto Addr = m_RGBBits;
			for (uint32_t y = 0; y < Spec.GetHeight(); ++y)
			{
				m_RGBRows[y] = Addr;
				Addr = (uint32_t*)(((uint8_t*)Addr) + m_RowBytes);
			}
			break;
		}
		case PixelType::Greyscale:
		{
			//https://github.com/aseprite/aseprite/blob/main/src/doc/image_impl.h

			m_RowBytes = AlignSize(sizeof(uint16_t) * m_Spec.GetWidth());
			size_t ForRows = AlignSize((sizeof(uint16_t*) * Spec.GetHeight()));
			size_t Size = ForRows + m_RowBytes * Spec.GetHeight();
			m_ByteSize = Size;

			ResizeImage(Spec.GetPixelType(), Size);


			std::fill(m_Buffer, m_Buffer + Size, 0);

			m_GSRows = (uint16_t**)m_Buffer;
			m_GSBits = (uint16_t*)(m_Buffer + ForRows);


			auto Addr = m_GSBits;
			for (uint32_t y = 0; y < Spec.GetHeight(); ++y)
			{
				m_GSRows[y] = Addr;
				Addr = (uint16_t*)(((uint8_t*)Addr) + m_RowBytes);
			}
			break;
		}
		default:
		{
			CoreLogger::Warn("Unable to make Image from this PixelType");
			break;
		}
		}

		for (auto& F : m_Spec.GetFileData().Frames)
		{
			for (auto& L : F.Layers)
			{
				for (auto& C : L.CelChunks)
				{
					for (auto& PD : C.PixelDatas)
					{
						InflateChunk(PD.Pixels, C.x, C.y);
					}	
				}
			}
		}
		//m_RGBImage = ReadImage(m_RGBImage, m_Spec.GetWidth(), m_RGBRows);
		m_RGBImage = ReadImage(m_RGBImage, m_Spec.GetWidth(), m_RGBRows);

	}
	Image::~Image()
	{
	}
	void Image::DrawHorizontalLine(int x1, int y, int x2, Vector4 Color)
	{
		uint32_t* Start = GetRGBAddress(x1, y);
		int Width = x2 - x1 + 1;

		std::fill(Start, Start + Width, (uint32_t)Color);
	}
	void Image::FillRect(int x1, int y1, int x2, int y2, Vector4 Color)
	{

		DrawHorizontalLine(x1, y1, x2, Color);

		uint32_t* FirstPixel = GetRGBAddress(x1, y1);
		int Width = x2 - x1 +1;
		
			for (int y = y1; y <= y2; ++y)
			{
				std::copy(FirstPixel, FirstPixel + Width, GetRGBAddress(x1, y));
			}
	}
	std::pair<int, int> Image::GetPixelLocation()
	{
		return std::pair<int, int>();
	}

	void Image::SetPixel(int x, int y, uint32_t Data)
	{
		*GetRGBAddress(x, y) = Data;
	}

	void Image::ClearImage(Vector4 Color)
	{

		for (uint32_t y = 0; y < m_Spec.GetHeight(); ++y)
		{
			uint32_t* First = GetRGBAddress(0, y);
			std::fill(First, First + m_Spec.GetWidth(), (uint32_t)Color);
		}

	}

	uint32_t* Image::GetRGBLineAddress(int y)
	{
		return m_RGBRows[y];
	}

	uint16_t* Image::GetGSLineAddress(int y)
	{
		return m_GSRows[y];
	}


	uint32_t* Image::GetRGBAddress(int x, int y)
	{
		return GetRGBLineAddress(y) + x;
	}

	uint16_t* Image::GetGSAddress(int x, int y)
	{
		return GetGSLineAddress(y) + x;
	}
	void Image::ReadScanline(uint32_t* Addr, uint32_t Width, uint8_t* Buffer)
	{
		for (uint32_t x = 0; x < Width; ++x, ++Addr)
		{
			uint8_t R = *(Buffer++);
			uint8_t G = *(Buffer++);
			uint8_t B = *(Buffer++);
			uint8_t A = *(Buffer++);

			Vector4 P( R,G,B,A );
			uint32_t Pixel = P;
			uint32_t* Pixel2 = &Pixel;
			if (IsSameColor(Pixel, Addr[x]))
			{
				continue;
			}
			*Addr = Pixel;
		}
	}
	template<typename T>
	T* Image::ReadImage(T* Addr, uint32_t Width, T** Buffer)
	{
		T* Img;

		if (bShouldFlip)
		{
			Img = new T[(m_Spec.GetWidth() * m_Spec.GetHeight()) * 2];
			for (int i = m_Spec.GetHeight() -1; i >= 0 ; --i)
			{
				const T* Begin = Buffer[i];
				const T* End = Begin + m_Spec.GetWidth();

				std::copy(Begin,End , Img + m_Spec.GetWidth() * ((m_Spec.GetHeight() -1) -i));

			}

			return Img;

		}
		else
		{
			Img = new T[(m_Spec.GetWidth() * m_Spec.GetHeight()) * 2];

			for (uint32_t i = 0; i < m_Spec.GetHeight(); ++i)
			{
				const T* Begin = Buffer[i];
				const T* End = Begin + m_Spec.GetWidth();

				std::copy(Begin, End, Img + m_Spec.GetWidth() * i);
			}

			return Img;

		}
	}

	void Image::ResizeImage(PixelType Type, size_t BufferSize)
	{
		switch (Type)
		{
		case PixelType::RGBA:
		case PixelType::RGB:
		{
			m_RGBImage = new uint32_t[(m_Spec.GetWidth() * m_Spec.GetHeight())];
			break;
		}
		case PixelType::Greyscale:
		{
			m_GSImage = new uint16_t[m_Spec.GetWidth() * m_Spec.GetHeight()];
			break;
		}
		}
		m_Buffer = new uint8_t[BufferSize];

	}


	std::vector<uint8_t> Image::InflateChunk(std::vector<uint8_t>& Data, int x, int y)
	{
		//https://github.com/aseprite/aseprite/blob/8e91d22b704d6d1e95e1482544318cee9f166c4d/src/doc/image_io.cpp

		MemoryStreamReader Stream(Data.data(), Data.size());
		size_t AvailBytes = Data.size();

		z_stream ZStream;
		ZStream.zalloc = (alloc_func)0;
		ZStream.zfree = (free_func)0;
		ZStream.opaque = (voidpf)0;
		
		int err = inflateInit(&ZStream);
		if (err != Z_OK)
		{
			CoreLogger::Error("Error in inflateInit()");
		}
		
		size_t Remain = AvailBytes;
		std::vector<uint8_t> compressed(4096);

		int Y = 0;
		uint8_t* Addr = (uint8_t*)GetRGBAddress(0,0);
		uint8_t* AddrEnd = (uint8_t*)GetRGBAddress(0, 0) + m_Spec.GetHeight() * m_RowBytes;
		int uncompressed_offset = 0;

		while (Remain > 0)
		{
			int Len = std::min(int(Remain), int(compressed.size()));


			uint64_t StartPositon = Stream.GetStreamPosition();
			Stream.ReadBytes(&compressed[0], Len);
			if (!Stream.IsStreamGood())
			{
				CoreLogger::Error("Error Reading Aseprite Image Data!");
			}

			size_t bytesRead = Stream.GetStreamPosition() - StartPositon;
			if (bytesRead == 0)
			{
				break;
			}
		
			Remain -= bytesRead;

			ZStream.next_in = (Bytef*)&compressed[0];
			ZStream.avail_in = (uInt)bytesRead;

			do
			{

				//if (Addr == AddrEnd)
				//{
				//	if (Y < m_Spec.GetHeight())
				//	{
				//		Addr = (uint8_t*)GetRGBAddress(0, Y++);
				//		AddrEnd = Addr + m_Spec.GetWidthBytes();
				//	}
				//}
				ZStream.next_out = (Bytef*)Addr;
				ZStream.avail_out = AddrEnd - Addr;

				err = inflate(&ZStream, Z_NO_FLUSH);
				if (err != Z_OK && err != Z_STREAM_END && err != Z_BUF_ERROR)
				{
					CoreLogger::Error("Error in inflate");
					CoreLogger::Error("\tError:{}", err);
				}


				int uncompressed_bytes = (int)((AddrEnd - Addr) - ZStream.avail_out);
				if (uncompressed_bytes > 0)
				{
					if (uncompressed_offset + uncompressed_bytes > m_Spec.GetHeight() * m_RowBytes)
					{
						throw std::exception("Bad compressed image.");
					}
					uncompressed_offset += uncompressed_bytes;
					Addr += uncompressed_bytes;
				}

			} while (ZStream.avail_in != 0 && ZStream.avail_out == 0);
		}
		
		
		err = inflateEnd(&ZStream);

		if (err != Z_OK)
		{
			CoreLogger::Error("Zlib Error in inflateEnd()");
			CoreLogger::Error("\t {}", ZStream.msg);
		}
		return std::vector<uint8_t>(1);
	}
}