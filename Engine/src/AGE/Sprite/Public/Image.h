#pragma once
#include "Core/Public/Core.h"
#include "Structs/Public/DataStructures.h"
#include "Core/Public/Log.h"
#include <vector>
#include <type_traits>

namespace AGE
{
	enum class PixelType : uint8_t
	{
		RGB = 1,
		RGBA = 2,
		Greyscale = 3,
		Indexed = 4
	};

	struct ImageSpecification
	{

	public:
		ImageSpecification() = default;
		ImageSpecification(const  ImageSpecification&) = default;

		ImageSpecification(uint32_t width, uint32_t height, int channels, uint8_t type, AsepriteFileData Data)
			:Width(width), Height(height), Channels(channels), Type((PixelType)type), Size({(int32_t)width,(int32_t)height}), FileData(Data)
		{
			switch (Type)
			{
			case PixelType::RGBA:
			{
				PixelsPerByte = 0;
				break;
			}
			case PixelType::RGB:
			{
				PixelsPerByte = 0;
				break;
			}
			case PixelType::Greyscale:
			{
				CoreLogger::Warn("There is currently no implementation for textures with 2 channels!");
				PixelsPerByte = 0;
			}
			default:
			{
				CoreLogger::Error("Pixel Type is invalid for making images!");
				break;
			}

			}
		};		

		//Use this constructor if you aren't sure how many channels there should be
		ImageSpecification(uint32_t width, uint32_t height, uint8_t type, AsepriteFileData Data)
			:Width(width), Height(height), Type((PixelType)type), Size({ (int32_t)width,(int32_t)height}), FileData(Data)
		{
			switch (Type)
			{
			case PixelType::RGBA:
			{
				Channels = 4;
				PixelsPerByte = 0;
				break;
			}
			case PixelType::RGB:
			{
				Channels = 3;
				PixelsPerByte = 0;
				break;
			}
			case PixelType::Greyscale:
			{
				CoreLogger::Warn("There is currently no implementation for textures with 2 channels!");
				Channels = 2;
				PixelsPerByte = 0;
			}
			default:
			{
				CoreLogger::Error("Pixel Type is invalid for making images!");
				break;
			}

			}

			Bounds = { 0,0, Size.Width, Size.Height };
		};


		~ImageSpecification() = default;

		std::pair<uint32_t, uint32_t> GetWidthHeight() { return { Width,Height }; }
		uint32_t GetWidth() const { return Width; }
		uint32_t GetWidth() { return Width; }
		uint32_t GetHeight() { return Height; }
		uint32_t GetHeight() const { return Height; }
		int GetChannels() { return Channels; }
 		PixelType GetPixelType() { return Type; }
		PixelType GetPixelType() const { return Type; }
		AGERect& GetBounds() { return Bounds; }
		AGESize& GetSize() { return Size; }
		int GetPixelsPerByte() { return PixelsPerByte; }
		uint32_t GetWidthBytes() 
		{
			uint32_t bpp;

			switch (Type)
			{
			case PixelType::RGBA:
			{
				bpp = 32;
				break;
			}
			case PixelType::RGB:
			{
				bpp = 24;
				break;
			}
			case PixelType::Greyscale:
			{
				bpp = 8;
				break;
			}
			case PixelType::Indexed:
			{
				bpp = 8;
				break;
			}
			default:
			{
				CoreLogger::Warn("Pixel Type Not Set for Image Specification... Using default 32 bits per pixel (RGBA)");
				bpp = 32;
				break;
			}
			}

			return Width * bpp;
		}

		AsepriteFileData& GetFileData() { return FileData; }


		void SetFileData(const AsepriteFileData& Data) { FileData = Data; }
		void SetWidthHeight(const std::pair<uint32_t, uint32_t>& WidthHeight) { Width = WidthHeight.first; Height = WidthHeight.second; }
		void SetWidth(const uint32_t width) { Width = width; }
		void SetHeight(const uint32_t height) { Height = height; }
		void SetChannels(int channels) { Channels = channels; }
		void SetPixelType(const PixelType& type) { Type = type; }
		void SetSize(const AGESize& size) { Size = size; }
		void SetBounds(const AGERect& bounds) { Bounds = bounds; }


	private:
		uint32_t Width = 0;
		uint32_t Height = 0;
		int Channels = 4;
		PixelType Type = PixelType::RGBA;
		AsepriteFileData FileData;
		AGESize Size = { 0,0 };
		AGERect Bounds = { 0,0,0,0 };
		int PixelsPerByte = 0;
		
	};

	class Image
	{
	public:
		Image() = default;
		Image(ImageSpecification& Spec, bool FlipVerticallyOnLoad = false);
		Image(const Image& Other) = default;
		Image(const Image&& Other) noexcept
		{
			m_Spec = Other.m_Spec;
			m_RowBytes = Other.m_RowBytes;
			m_ByteSize = Other.m_ByteSize;
			m_Buffer = Other.m_Buffer;
			m_RGBImage = Other.m_RGBImage;
			m_GSImage = Other.m_GSImage;
			m_RGBRows = Other.m_RGBRows;
			m_RGBBits = Other.m_RGBBits;
			m_GSRows = Other.m_GSRows;
			m_GSBits = Other.m_GSBits;
		};

		virtual ~Image();

		ImageSpecification& GetImageSpec() { return m_Spec; }
		const ImageSpecification& GetImageSpec() const { return m_Spec; }
		uint32_t* GetImageBuffer() { return m_RGBImage; }
		const uint32_t* GetImageBuffer() const { return m_RGBImage; }

		size_t GetImageByteSize() 
		{
			return m_ByteSize;
		}

		void SetImageSpec(const ImageSpecification& Spec) { m_Spec = Spec; }
		
		template<typename T>
		T GetPixel(int x, int y)
		{
			if (std::is_same<T,uint32_t>::value)
			{
				return GetRGBAddress(x,y);
			}

			if (std::is_same<T, uint16_t>::value)
			{
				return GetGSAddress(x, y);
			}
		}

	private:

		void DrawHorizontalLine(int x1, int y, int x2, Vector4 Color);

		void FillRect(int x1, int y1, int x2, int y2, Vector4 Color);

		void BlendRect(int x1, int y1, int x2, int y2, Vector4 Color, int Alpha)
		{
			FillRect(x1, y1, x2, y2, Color);
		}

		std::pair<int, int> GetPixelLocation();


		void SetPixel(int x, int y, uint32_t Data);

		void ClearImage(Vector4 Color);

		uint32_t* GetRGBLineAddress(int y);

		uint16_t* GetGSLineAddress(int y);


		uint32_t* GetRGBAddress(int x, int y);

		uint16_t* GetGSAddress(int x, int y);

		void ReadScanline(uint32_t* Addr, uint32_t Width, uint8_t* Buffer);

		template<typename T>
		T* ReadImage(T* Addr, uint32_t Width, T** Buffer);

		void ResizeImage(PixelType Type, size_t BufferSize);

		std::vector<uint8_t> InflateChunk(std::vector<uint8_t>& Data, int x, int y);

		template<typename T>
		inline bool IsSameColor(const T A, const T B)
		{
			if (((A >> 24) & 0xff) == 0)
			{
				if (((B >> 24) & 0xff) == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (((B >> 24) & 0xff) == 0)
			{
				return false;
			}
			else
			{
				return A == B;
			}
		}

		// LAF Base Library
		// Copyright (c) 2001-2016 David Capello
		//
		// This file is released under the terms of the MIT license.
		// Read LICENSE.txt for more information.
		//Copying the implementation from laf, since I don't need the entire library as of yet

#ifdef __cplusplus
#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
		static constexpr size_t BaseAlignment = __STDCPP_DEFAULT_NEW_ALIGNMENT__;
#else
		static constexpr size_t BaseAlignment = 1;
#endif

		constexpr size_t AlignSize(const size_t N, const size_t Alignment = BaseAlignment)
		{
			size_t Remaining = (N % Alignment);
			size_t Aligned_N = N + (Remaining ? (Alignment - Remaining) : 0);

			if (Aligned_N > Alignment)
			{
				return Aligned_N;
			}
			return Alignment;
		}
#endif

	private:

		//This is our stride
		size_t m_RowBytes = 0;
		size_t m_ByteSize = 0;


		uint8_t* m_Buffer;

		uint32_t* m_RGBImage;
		uint16_t* m_GSImage;

		uint32_t** m_RGBRows;
		uint32_t* m_RGBBits;

		uint16_t** m_GSRows;
		uint16_t* m_GSBits;

		ImageSpecification m_Spec;

		bool bShouldFlip = false;
	};
}