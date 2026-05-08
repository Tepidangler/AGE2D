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
		/**
 * @brief Default constructor for ImageSpecification class.
 *
 * This function initializes an instance of the ImageSpecification class with its default values.
 * It does not take any parameters and returns nothing.
 */
ImageSpecification() = default;
		/**
 * @brief Default copy constructor for the ImageSpecification class.
 *
 * This function is used to create a new instance of an ImageSpecification object by copying another existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param other The ImageSpecification object to be copied.
 */
ImageSpecification(const  ImageSpecification&) = default;

		Unknown
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
		/**
 * @brief Constructs an ImageSpecification object with the given parameters.
 * 
 * The constructor initializes the image specification based on the provided width, height, type and data. It sets the number of channels and pixels per byte according to the pixel type. If the pixel type is invalid, it logs an error message. For greyscale images, a warning message is logged as there's currently no implementation for 2-channel textures.
 * 
 * @param width The width of the image in pixels.
 * @param height The height of the image in pixels.
 * @param type The pixel type of the image (RGBA, RGB or Greyscale).
 * @param Data The AsepriteFileData associated with this ImageSpecification.
 */
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


		/**
 * @brief Destructor for the ImageSpecification class.
 *
 * This function is responsible for freeing any resources that were allocated during the lifetime of an instance of this class.
 */
~ImageSpecification() = default;

		/**
 * @brief This function returns a pair of integers representing the width and height.
 * @return A std::pair<uint32_t, uint32_t> object containing the width and height.
 */
std::pair<uint32_t, uint32_t> GetWidthHeight() { return { Width,Height }; }
		/**
 * @brief Returns the width of an object.
 *
 * This function returns the current width value stored in the 'Width' variable. It is a getter method for the 'Width' attribute.
 *
 * @return uint32_t The current width of the object.
 */
uint32_t GetWidth() const { return Width; }
		/**
 * @brief Returns the width of an object.
 * @return The width as a uint32_t value.
 */
uint32_t GetWidth() { return Width; }
		/**
 * @brief This function returns the height of an object.
 *
 * @return The current height value as a uint32_t.
 */
uint32_t GetHeight() { return Height; }
		/**
 * @brief Returns the height of an object.
 *
 * This function is used to get the current height value of an object. It does not take any parameters and returns a uint32_t representing the height.
 *
 * @return The current height as a uint32_t. If no height has been set, it will return 0.
 */
uint32_t GetHeight() const { return Height; }
		/**
 * @brief Returns the number of channels in use by the system.
 *
 * This function retrieves the current count of active channels in the system. It is used to manage resources and ensure efficient operation.
 *
 * @return int - The number of active channels. If no channels are available, it returns 0.
 */
int GetChannels() { return Channels; }
 		/**
 * @brief This function returns the type of a pixel.
 * 
 * @return PixelType The type of the pixel (e.g., RGB, Grayscale).
 */
PixelType GetPixelType() { return Type; }
		/**
 * @brief Returns the type of pixel represented by this object.
 * @return The PixelType enum value representing the type of pixel.
 */
PixelType GetPixelType() const { return Type; }
		/**
 * @brief Gets the bounds of an object.
 *
 * This function returns a reference to the 'Bounds' variable, which represents the boundaries of the object.
 * The returned value can be modified using assignment operators if required.
 *
 * @return A reference to the Bounds variable.
 */
AGERect& GetBounds() { return Bounds; }
		/**
 * @brief This function returns the size of an object.
 * @return A reference to the Size variable.
 */
AGESize& GetSize() { return Size; }
		/**
 * @brief This function returns the number of pixels per byte.
 * @return int The number of pixels per byte. If no value is set, it will return -1.
 */
int GetPixelsPerByte() { return PixelsPerByte; }
		/**
 * @brief This function returns the width of an image in bytes.
 * The bit depth (bpp) is determined by the PixelType of the image. If the PixelType is RGBA, then bpp is 32; if it's RGB, then bpp is 24; for Greyscale and Indexed pixel types, bpp is 8.
 * For any other unrecognized PixelType, a warning message is logged to inform user that the default value of bpp (RGBA) is being used.
 * @return The width of the image in bytes. This is calculated by multiplying the Width of the image with its bit depth per pixel (bpp).
 */
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

		/**
 * @brief Returns the Aseprite file data.
 *
 * This function returns a reference to the Aseprite file data object, which contains all the information about the loaded Aseprite file.
 *
 * @return A reference to the AsepriteFileData object.
 */
AsepriteFileData& GetFileData() { return FileData; }


		/**
 * @brief Sets the file data for the Aseprite object.
 * @param Data The new file data to be set.
 */
void SetFileData(const AsepriteFileData& Data) { FileData = Data; }
		/**
 * @brief Sets the width and height of an object using a pair of unsigned integers.
 * @param WidthHeight A pair of unsigned integers representing the new width and height.
 */
void SetWidthHeight(const std::pair<uint32_t, uint32_t>& WidthHeight) { Width = WidthHeight.first; Height = WidthHeight.second; }
		/**
 * @brief Sets the width of an object.
 * @param[in] width The new width to be set for the object.
 */
void SetWidth(const uint32_t width) { Width = width; }
		/**
 * @brief Sets the height of an object.
 *
 * This function sets the 'Height' member variable to a specified value. It takes one parameter, which is the new height value.
 * The function does not return anything (void).
 *
 * @param[in] height - The new height value for the object. Must be less than or equal to 4294967295.
 * @return void
 */
void SetHeight(const uint32_t height) { Height = height; }
		/**
 * @brief Sets the number of audio channels to be processed by the system.
 *
 * This function sets the 'Channels' variable, which represents the number of audio channels in the system. It takes an integer parameter 'channels', which is used to set the value of Channels.
 *
 * @param channels The new number of audio channels.
 * 
 * @return void
 */
void SetChannels(int channels) { Channels = channels; }
		/**
 * @brief Sets the pixel type of an object.
 *
 * This function sets the pixel type for an object, which can be used to determine how the object should be rendered in a graphics context.
 *
 * @param[in] type The new PixelType value to set.
 * @return void
 */
void SetPixelType(const PixelType& type) { Type = type; }
		/**
 * @brief Sets the size of an object.
 *
 * This function sets the size attribute of an object to a given value. The size is expected to be in the form of an AGESize object.
 *
 * @param[in] size - The new size for the object.
 * 
 * @return void
 */
void SetSize(const AGESize& size) { Size = size; }
		/**
 * @brief Sets the bounds of an object.
 * @param bounds The new bounds to set for the object.
 */
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
		/**
 * @brief Default constructor for the Image class.
 *
 * This function initializes an instance of the Image class with default values. It is used to create a new image object without any specific attributes set.
 *
 * @return A new Image object with all fields initialized to their default values.
 */
Image() = default;
		Image(ImageSpecification& Spec, bool FlipVerticallyOnLoad = false);
		/**
 * @brief Copy constructor for the Image class.
 *
 * This function creates a new instance of an Image object by copying all data from another Image object.
 * It uses the '= default' syntax to delegate the copy construction to the compiler, which means it will use the 
 * default implementation provided by the compiler. The compiler-generated copy constructor performs a memberwise 
 * copy of the source object into this new object. This includes copying all data members that are part of the Image class.
 *
 * @param Other The Image object to be copied.
 */
Image(const Image& Other) = default;
		/**
 * @brief Move constructor for Image class.
 * 
 * This function is used to create a new instance of the Image class by moving all its data from an existing instance.
 * It takes in a const lvalue reference to another Image object and moves its data into this new object, leaving the original object empty.
 * The move operation is exception-safe as it does not throw exceptions under normal circumstances.
 * 
 * @param Other An rvalue reference to an existing Image object.
 */
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

		/**
 * @brief Returns the image specification object.
 *
 * This function returns a reference to an ImageSpecification object, which contains information about the image such as its size and format.
 *
 * @return A reference to the ImageSpecification object.
 */
ImageSpecification& GetImageSpec() { return m_Spec; }
		/**
 * @brief Returns the image specification object associated with this instance.
 * @return A constant reference to the image specification object (m_Spec).
 */
const ImageSpecification& GetImageSpec() const { return m_Spec; }
		/**
 * @brief This function returns a pointer to the RGB image buffer.
 * @return Pointer to the RGB image buffer, type is uint32_t*. If no image data exists, it will return nullptr.
 */
uint32_t* GetImageBuffer() { return m_RGBImage; }
		/**
 * @brief Returns a pointer to the RGB image buffer.
 * @return Pointer to the RGB image buffer, or nullptr if no image is available.
 */
const uint32_t* GetImageBuffer() const { return m_RGBImage; }

		/**
 * @brief This function returns the size of an image in bytes.
 * @return The byte size of the image.
 */
size_t GetImageByteSize() 
		{
			return m_ByteSize;
		}

		/**
 * @brief Sets the image specification.
 *
 * This function sets the image specification to a new value. The ImageSpecification object is passed by const reference, meaning that no copy of it will be made and the original object can still be used elsewhere in the code.
 * 
 * @param Spec A constant reference to an ImageSpecification object containing the new image specification.
 */
void SetImageSpec(const ImageSpecification& Spec) { m_Spec = Spec; }
		
		template<typename T>
		/**
 * @brief This function returns the pixel value at a given position.
 * 
 * The function checks if the template type T is uint32_t or uint16_t and calls the appropriate function to get the pixel address.
 * If T is not either of these types, it will return a default value of T.
 * @param x The x-coordinate of the pixel position.
 * @param y The y-coordinate of the pixel position.
 * @return Returns the pixel value at the given position.
 */
T GetPixel(T x, T y)
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

		/**
 * @brief Blends a rectangle with the specified color and alpha value.
 * 
 * This function takes four integer parameters to specify the coordinates of the rectangle, a Vector4 parameter for the color, and an integer parameter for the alpha value. It uses these inputs to blend the rectangle using the FillRect function.
 *
 * @param x1 The x-coordinate of the first corner of the rectangle.
 * @param y1 The y-coordinate of the first corner of the rectangle.
 * @param x2 The x-coordinate of the second corner of the rectangle.
 * @param y2 The y-coordinate of the second corner of the rectangle.
 * @param Color The color to blend the rectangle with.
 * @param Alpha The alpha value to use for blending (0 is fully transparent, 255 is fully opaque).
 *
 * @return void
 */
void BlendRect(int x1, int y1, int x2, int y2, Vector4 Color, int Alpha)
		{
			FillRect(x1, y1, x2, y2, Color);
		}

		std::pair<int, int> GetPixelLocation();


		void SetPixel(int x, int y, uint32_t Data);

		void ClearImage(Vector4 Color);

		uint32_t* GetRGBLineAddress(uint32_t y);

		uint16_t* GetGSLineAddress(uint16_t y);


		uint32_t* GetRGBAddress(uint32_t x, uint32_t y);

		uint16_t* GetGSAddress(uint16_t x, uint16_t y);

		void ReadScanline(uint32_t* Addr, uint32_t Width, uint8_t* Buffer);

		template<typename T>
		T* ReadImage(T* Addr, uint32_t Width, T** Buffer);

		void ResizeImage(PixelType Type, size_t BufferSize);

		std::vector<uint8_t> InflateChunk(std::vector<uint8_t>& Data, int x, int y);

		template<typename T>
		/**
 * @brief This function checks if two colors are the same. The comparison is done by comparing the alpha channel of each color.
 * @param A First color to compare, represented as a T value (likely an ARGB integer).
 * @param B Second color to compare, also represented as a T value.
 * @return Returns true if both colors have the same alpha component or are fully transparent (alpha = 0), false otherwise.
 */
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

		/**
 * @brief This function aligns a size value to the specified alignment.
 *
 * The function takes in two parameters, N and Alignment (default is BaseAlignment). 
 * It calculates the remainder of N divided by Alignment, if there's any remaining it subtracts this from the total size N and adds the necessary padding to make it a multiple of the alignment.
 * If the resulting aligned size is greater than the alignment, it returns the aligned size; otherwise, it returns the alignment.
 * 
 * @param[in] N The size value to be aligned.
 * @param[in] Alignment The desired alignment (default is BaseAlignment).
 * @return The aligned size or the default alignment if no change was necessary.
 */
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