#include "AGEpch.hpp"
#include "Sprite/Public/Image.h"
#include "Serializers/Public/DataReader.h"
#include <zlib.h>
#include <stb_image.h>
//TODO:  Note to Self, we have effectively move pixel data to a buffer which represents an image, now we need to work on flipping the image on the y-axis so that the picture is right side up before we pass it to the graphics renderer
namespace AGE
{
	Unknown
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
	/**
 * @brief Destructor for the Image class.
 *
 * This destructor does not perform any specific action as it is a default one provided by the compiler. 
 * It simply releases any resources that were acquired during object creation, such as memory allocated with 'new'.
 *
 * @return void
 */
Image::~Image()
	{
	}
	/**
 * @brief Draws a horizontal line on the image.
 *
 * This function draws a horizontal line on the image at a specified y-coordinate between two x-coordinates (x1, x2). 
 * The color of the line is provided as a Vector4 object.
 *
 * @param x1 The start x-coordinate of the line.
 * @param y The y-coordinate of the line.
 * @param x2 The end x-coordinate of the line.
 * @param Color The color of the line, represented as a Vector4 object.
 * 
 * @return void
 */
void Image::DrawHorizontalLine(int x1, int y, int x2, Vector4 Color)
	{
		uint32_t* Start = GetRGBAddress((uint32_t)x1, (uint32_t)y);
		int Width = x2 - x1 + 1;

		std::fill(Start, Start + Width, (uint32_t)Color);
	}
	/**
 * @brief Fills a rectangle with the specified color.
 *
 * This function fills a rectangular area on an image with a specific color by drawing horizontal lines from (x1, y1) to (x2, y2). 
 * The color is represented as a Vector4 object.
 *
 * @param x1,y1 Coordinates of the top-left corner of the rectangle.
 * @param x2,y2 Coordinates of the bottom-right corner of the rectangle.
 * @param Color The color to fill the rectangle with.
 * 
 * @return void
 */
void Image::FillRect(int x1, int y1, int x2, int y2, Vector4 Color)
	{

		DrawHorizontalLine(x1, y1, x2, Color);

		uint32_t* FirstPixel = GetRGBAddress((uint32_t)x1, (uint32_t)y1);
		int Width = x2 - x1 +1;
		
			for (int y = y1; y <= y2; ++y)
			{
				std::copy(FirstPixel, FirstPixel + Width, GetRGBAddress((uint32_t)x1, (uint32_t)y));
			}
	}
	/**
 * @brief Get the location of a pixel in an image
 * 
 * This function returns a pair of integers representing the x and y coordinates of a pixel. If no specific pixel is specified, it will return the default location (0, 0).
 * 
 * @return A pair of integers representing the x and y coordinates of a pixel.
 */
std::pair<int, int> Image::GetPixelLocation()
	{
		return std::pair<int, int>();
	}

	/**
 * @brief Sets the pixel value at a specific location in the image.
 *
 * This function sets the RGB data for a pixel at a specified (x, y) location to a given color value. The x and y coordinates are integers representing the position of the pixel, while Data is an unsigned 32-bit integer that represents the new color value for the pixel.
 *
 * @param x An integer representing the horizontal position of the pixel in the image.
 * @param y An integer representing the vertical position of the pixel in the image.
 * @param Data An unsigned 32-bit integer representing the new RGB data for the pixel.
 */
void Image::SetPixel(int x, int y, uint32_t Data)
	{
		*GetRGBAddress((uint32_t)x, (uint32_t)y) = Data;
	}

	/**
 * @brief Clears the image with a specified color.
 *
 * This function iterates over each pixel in the image and sets its color to the provided Color parameter. 
 * The color is represented as a Vector4, where x, y, z, w represent red, green, blue, and alpha respectively.
 *
 * @param Color A Vector4 representing the color to clear the image with.
 */
void Image::ClearImage(Vector4 Color)
	{

		for (uint32_t y = 0; y < m_Spec.GetHeight(); ++y)
		{
			uint32_t* First = GetRGBAddress(0, y);
			std::fill(First, First + m_Spec.GetWidth(), (uint32_t)Color);
		}

	}

	/** 
 * @brief This function returns the address of a line in RGB image data.
 * 
 * @param y The index of the line to get the address for.
 * @return A pointer to the start of the specified row in the RGB image data.
 * 
 * @note The returned pointer should not be deleted or modified directly, as it points into internal memory owned by the Image object.
 */
uint32_t* Image::GetRGBLineAddress(uint32_t y)
	{
		return m_RGBRows[y];
	}

	/**
 * @brief Get the address of a grayscale line in the image.
 * 
 * This function returns the pointer to the start of the grayscale data for the specified line 'y'.
 * The returned pointer can be used to access or modify the grayscale values of this line directly.
 * 
 * @param y The vertical position of the line in the image, starting from 0 at the top.
 * @return Pointer to the start of the grayscale data for the specified line 'y'.
 */
uint16_t* Image::GetGSLineAddress(uint16_t y)
	{
		return m_GSRows[y];
	}


	/**
 * @brief Returns the address of a pixel in the image.
 *
 * This function returns the memory address of a specific pixel in the image. The pixel is specified by its x and y coordinates.
 *
 * @param x The x-coordinate of the pixel, starting from 0 at the leftmost position.
 * @param y The y-coordinate of the pixel, starting from 0 at the top.
 * @return A pointer to the memory address of the specified pixel.
 */
uint32_t* Image::GetRGBAddress(uint32_t x, uint32_t y)
	{
		return GetRGBLineAddress(y) + x;
	}

	/**
 * @brief This function returns the address of a pixel in the grayscale image.
 *
 * The function takes two parameters, 'x' and 'y', which represent the coordinates of the pixel in the image. 
 * It then calculates and returns the address of that pixel by adding 'x' to the line address returned by GetGSLineAddress(y).
 *
 * @param x The horizontal position (column) of the pixel, starting from 0 at the leftmost edge.
 * @param y The vertical position (row) of the pixel, starting from 0 at the top.
 *
 * @return A pointer to the grayscale value of the specified pixel.
 */
uint16_t* Image::GetGSAddress(uint16_t x, uint16_t y)
	{
		return GetGSLineAddress(y) + x;
	}
	/**
 * @brief Reads a scanline from the buffer and writes it to the image.
 *
 * This function reads each pixel's RGBA values from the provided buffer, converts them into an equivalent Vector4 object, 
 * then checks if the current pixel in the image is the same color as the one read from the buffer. If they are not the same, 
 * it updates the corresponding pixel in the image with the new color information.
 *
 * @param Addr Pointer to the start of the scanline in the image data.
 * @param Width The width of the scanline.
 * @param Buffer Pointer to the start of the buffer containing RGBA values for each pixel.
 */
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
			[[maybe_unused]] uint32_t* Pixel2 = &Pixel;
			if (IsSameColor(Pixel, Addr[x]))
			{
				continue;
			}
			*Addr = Pixel;
		}
	}
	template<typename T>
	/**
 * Reads an image from the buffer and returns a pointer to it. If bShouldFlip is true, the image will be flipped vertically.
 * 
 * @param Addr The address where the new image data should start at.
 * @param Width The width of the image in pixels.
 * @param Buffer A buffer containing the raw pixel data for each row of the image.
 * 
 * @return A pointer to the newly allocated memory that contains the image data. This must be deleted by the caller when it is no longer needed.
 */
T* Image::ReadImage(T* Addr, uint32_t Width, T** Buffer)
	{
		T* Img;

		if (bShouldFlip)
		{
			Img = new T[(m_Spec.GetWidth() * m_Spec.GetHeight()) * 2];
			for (int i = (int)m_Spec.GetHeight() -1; i >= 0 ; --i)
			{
				const T* Begin = Buffer[i];
				const T* End = Begin + m_Spec.GetWidth();

				std::copy(Begin,End , Img + (int)m_Spec.GetWidth() * (((int)m_Spec.GetHeight() -1) -i));

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

	/**
 * @brief Resizes the image based on the given pixel type and buffer size.
 *
 * This function resizes the image by allocating memory for a new buffer of the specified size. 
 * The type of pixel is determined by the PixelType parameter, which can be either RGBA, RGB or Greyscale. 
 * For RGBA and RGB types, it creates a new uint32_t array with the dimensions being width times height. 
 * For Greyscale type, it creates a new uint16_t array with the same dimensions. 
 * If an unrecognized PixelType is passed, no action is taken.
 *
 * @param Type The pixel type to resize the image for. Can be RGBA, RGB or Greyscale.
 * @param BufferSize The size of the buffer to allocate in bytes.
 */
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
		default:
		{
			break;
		}
		}
		m_Buffer = new uint8_t[BufferSize];

	}


	/**
 * @brief Inflates a chunk of compressed image data.
 *
 * This function takes in a vector of uint8_t (Data), two integers (x and y) as parameters, 
 * and returns an inflated version of the Data. The purpose of this function is to decompress 
 * the compressed image data stored in the input vector.
 *
 * @param[in] Data A vector of uint8_t containing the compressed image data.
 * @param[in] x An integer representing the x-coordinate of the chunk.
 * @param[in] y An integer representing the y-coordinate of the chunk.
 * 
 * @return A vector of uint8_t containing the inflated (decompressed) image data.
 */
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

		[[maybe_unused]] int Y = 0;
		uint8_t* Addr = (uint8_t*)GetRGBAddress(0,0);
		uint8_t* AddrEnd = (uint8_t*)GetRGBAddress(0, 0) + m_Spec.GetHeight() * m_RowBytes;
		int uncompressed_offset = 0;

		while (Remain > 0)
		{
			int Len = std::min(int(Remain), int(compressed.size()));


			uint64_t StartPositon = Stream.GetStreamPosition();
			Stream.ReadBytes(&compressed[0], (size_t)Len);
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
				ZStream.avail_out = (uint32_t)(AddrEnd - Addr);

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
						CoreLogger::Error("Bad compressed image.");
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