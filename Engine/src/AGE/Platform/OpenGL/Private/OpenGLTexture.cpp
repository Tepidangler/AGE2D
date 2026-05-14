#include "AGEpch.hpp"
#include "Core/Public/Core.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLTexture.h"
#include "Statics/Public/Statics.h"


#include <glad/glad.h>
#include <stb_image.h>

namespace AGE
{
	namespace Utils
	{
		/**
 * @brief Converts an ImageFormat to a GLenum data format.
 *
 * This function takes in an ImageFormat and returns the corresponding GLenum data format. It uses a switch-case statement to handle different ImageFormats, 
 * returning GL_RGB for RGB8 and GL_RGBA for RGBA8. If the ImageFormat is not supported by AGE (which should never happen), it asserts false and returns 0.
 *
 * @param Format The ImageFormat to convert.
 * @return The corresponding GLenum data format.
 */
static GLenum AGEImageFormatToGLDataFormat(ImageFormat Format)
		{
			switch (Format)
			{
			case ImageFormat::RGB8:
			{
				return GL_RGB;
			}
			case ImageFormat::RGBA8:
			{
				return GL_RGBA;
			}
			default:
			{
				break;
			}
			}

			CoreLogger::Assert(false, "Data Format not supported by AGE!");
			return 0;
		}

		/**
 * @brief Converts an ImageFormat to its corresponding GL internal format.
 *
 * This function takes in an ImageFormat and returns the equivalent GL internal format. It uses a switch-case statement to handle different ImageFormats, returning the appropriate GL_RGB8 or GL_RGBA8 based on the input. If the input is not supported by AGE (which should never happen as we only have two defined formats), it asserts false and returns 0.
 *
 * @param Format The ImageFormat to convert.
 * @return The corresponding GL internal format, or 0 if the ImageFormat is not supported.
 */
static GLenum AGEImageFormatToGLInternalFormat(ImageFormat Format)
		{
			switch (Format)
			{
			case ImageFormat::RGB8:
			{
				return GL_RGB8;
			}
			case ImageFormat::RGBA8:
			{
				return GL_RGBA8;
			}
			default:
			{
				break;
			}
			}

			CoreLogger::Assert(false, "Internal Format not supported by AGE!");
			return 0;
		}

	}

	/**
 * @brief Constructs an OpenGL 2D texture with the given specification.
 * 
 * The function creates a new OpenGL texture object and initializes it with the provided TextureSpecification. It sets various parameters such as wrapping and filtering modes for the texture.
 * 
 * @param Spec The TextureSpecification that contains details about the format, width, height etc of the texture to be created.
 */
OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& Spec)
		:m_Specification(Spec), m_Width((int)Spec.Width), m_Height((int)Spec.Height)
	{
		AGE_PROFILE_FUNCTION();
		m_InternalFormat = Utils::AGEImageFormatToGLInternalFormat(Spec.Format);
		m_DataFormat = Utils::AGEImageFormatToGLDataFormat(Spec.Format);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		//Set Texture wrapping params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		//Set Texture filtering params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//glGenerateMipmap(m_TextureID);
	}

	COMMENT:
/**
 * @brief Constructs an OpenGLTexture2D object from an image.
 * 
 * This function creates a 2D texture in OpenGL and initializes it with the given image data. The width, height, number of channels, and size of the image are also stored as member variables.
 * 
 * @param Img Pointer to the Image object containing the pixel data.
 * @param Width The width of the texture in pixels.
 * @param Height The height of the texture in pixels.
 * @param Channels The number of channels in the image (3 for RGB, 4 for RGBA).
 * @param Size The size of the image data in bytes.
 */
CONFIDENCE: 1.0;

OpenGLTexture2D::OpenGLTexture2D(const Image* Img, uint32_t Width, uint32_t Height, int Channels, size_t Size)
		:m_Width((int)Width), m_Height((int)Height), m_nrChannels(Channels)
	{
		AGE_PROFILE_FUNCTION();

		GLenum InternalFormat = 0, DataFormat = 0;
		if (m_nrChannels == 4)
		{
			InternalFormat = GL_RGBA8;
			DataFormat = GL_RGBA;
		}
		else if (m_nrChannels == 3)
		{
			InternalFormat = GL_RGB8;
			DataFormat = GL_RGB;
		}

		m_InternalFormat = InternalFormat;
		m_DataFormat = DataFormat;

		CoreLogger::Assert(InternalFormat & DataFormat, "Format not supported!");
		glCreateTextures(GL_TEXTURE_2D,1, &m_TextureID);

		glTextureStorage2D(m_TextureID, 1, InternalFormat, m_Width, m_Height);

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//Set Texture wrapping params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Set Texture filtering params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		CoreLogger::Error("OpenGL Error: {}",glGetError());
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Img->GetImageBuffer());
		CoreLogger::Error("OpenGL Error: {}",glGetError());


	}
	
	
OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)
		: m_Path(Path), m_AssetID(UUID())
	{
		AGE_PROFILE_FUNCTION();

		unsigned char *Data = nullptr;
		{
			stbi_set_flip_vertically_on_load(true);
			AGE_PROFILE_SCOPE("stbi_load -> OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)");
			Data = stbi_load(Path.c_str(), &m_Width, &m_Height, &m_nrChannels, 0);
		}
		CoreLogger::Assert(Data != nullptr, "Unable to Load Image");
		m_ImageData = {Data, ((m_Width * m_Height) * m_nrChannels)};

		GLenum InternalFormat = 0, DataFormat = 0;
		if (m_nrChannels == 4)
		{
			InternalFormat = GL_RGBA8;
			DataFormat = GL_RGBA;
		} else if (m_nrChannels == 3)
		{
			InternalFormat = GL_RGB8;
			DataFormat = GL_RGB;
		} else if (m_nrChannels == 2)
		{
			InternalFormat = GL_RG8;
			DataFormat = GL_RG;
		} else
		{
			InternalFormat = GL_R8;
			DataFormat = GL_RED;
		}
		m_InternalFormat = InternalFormat;
		m_DataFormat = DataFormat;

		CoreLogger::Assert(InternalFormat & DataFormat, "Format not supported!");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		glTextureStorage2D(m_TextureID, 1, InternalFormat, m_Width, m_Height);

		//Set Texture wrapping params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Set Texture filtering params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Data);

		CoreLogger::Error("{}", glGetError());
		stbi_image_free(Data);
		std::filesystem::path FilePath = m_Path;
		m_Name = Utils::EngineStatics::GetFilename(FilePath);
	}

	
OpenGLTexture2D::OpenGLTexture2D(const tmx_image* Image)
	{
		[[maybe_unused]] char* TexData = (char*)Image->resource_image;

		
		//if (Tex)
		//{
		//	//OpenGLTexture2D Tmp = (OpenGLTexture2D)Tex;
		//	//m_TextureID = Tex->m_TextureID;
		//	//m_Width = Tex->m_Width;
		//	//m_Height = Tex->m_Height;
		//	//m_nrChannels = Tex->m_nrChannels;
		//}


		//free(Tex);
		//std::ifstream In((char*)Image->resource_image, std::ios::in | std::ios::binary);
		//if (In)
		//{
		//	In.read(reinterpret_cast<OpenGLTexture2D>(Image->resource_image), sizeof(uint32_t));
		//}
		//m_Width = Image->width;
		//m_Height = Image->height;
		//m_nrChannels = 4;
		//GLenum InternalFormat = 0, DataFormat = 0;
		//if (m_nrChannels == 4)
		//{
		//	InternalFormat = GL_RGBA8;
		//	DataFormat = GL_RGBA;
		//}
		//else if (m_nrChannels == 3)
		//{
		//	InternalFormat = GL_RGB8;
		//	DataFormat = GL_RGB;
		//}
		//
		//m_InternalFormat = InternalFormat;
		//m_DataFormat = DataFormat;
		//
		//CoreLogger::Assert(InternalFormat & DataFormat, "Format not supported!")
		//	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		//
		//glTextureStorage2D(m_TextureID, 1, InternalFormat, m_Width, m_Height);
		//
		////Set Texture wrapping params
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//
		////Set Texture filtering params
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//
		//
		//glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Image->source);
	}

	/**
 * Constructor for OpenGLTexture2D class. Loads a 2D texture from the given file paths.
 * The constructor iterates over each path in the input vector, loads an image using stbi_load(), and creates an OpenGL texture with the loaded data.
 * It also sets various parameters for the texture such as wrapping mode (GL_REPEAT), minifying/magnifying filter (GL_NEAREST).
 * The constructor assumes that all images are in RGB or RGBA format, and it uses stbi_image_free() to free the loaded image data after creating the OpenGL texture.
 * 
 * @param Paths A vector of strings representing the file paths to load the textures from.
 */
OpenGLTexture2D::OpenGLTexture2D(const std::vector<std::string>& Paths)
	{
		AGE_PROFILE_FUNCTION();
		//stbi_set_flip_vertically_on_load(true);
		for (size_t i = 0; i < Paths.size(); i++)
		{


			unsigned char* Data = nullptr;
			{
				AGE_PROFILE_SCOPE("stbi_load -> OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)");
				Data = stbi_load(Paths[i].c_str(), &m_Width, &m_Height, &m_nrChannels, 0);

			}
			CoreLogger::Assert(Data, "Unable to Load Image");

			GLenum InternalFormat = 0, DataFormat = 0;
			if (m_nrChannels == 4)
			{
				InternalFormat = GL_RGBA8;
				DataFormat = GL_RGBA;
			}
			else if (m_nrChannels == 3)
			{
				InternalFormat = GL_RGB8;
				DataFormat = GL_RGB;
			}

			m_InternalFormat = InternalFormat;
			m_DataFormat = DataFormat;

			CoreLogger::Assert(InternalFormat & DataFormat, "Format not supported!");
				glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

			glTextureStorage2D(m_TextureID, 1, InternalFormat, m_Width, m_Height);

			//Set Texture wrapping params
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Set Texture filtering params
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Data);

			//glGenerateMipmap(m_TextureID);

			stbi_image_free(Data);
		}
	}


	/**
 * @brief Destructor for OpenGLTexture2D class. Deletes the texture from GPU memory.
 * 
 * This function uses the glDeleteTextures() function to delete a single texture, identified by its ID (m_TextureID). The texture is deleted from the GPU's memory and can no longer be used in rendering operations.
 * 
 * @return void
 */
OpenGLTexture2D::~OpenGLTexture2D()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_TextureID);
	}
	/** 
 * @brief This function binds the texture to a specific slot in the OpenGL context.
 * 
 * @param Slot The index of the texture unit to which the texture should be bound.
 * 
 * @return void
 */
void OpenGLTexture2D::Bind(uint32_t Slot) const
	{
		AGE_PROFILE_FUNCTION();
		glBindTextureUnit(Slot, m_TextureID);

	}
	/**
 * @brief Unbinds the texture from the specified texture unit.
 *
 * This function binds a specific OpenGL texture to the first available texture unit (unit 0). After this operation, no further operations will affect this texture.
 *
 * @return void
 */
void OpenGLTexture2D::Unbind() const
	{
		glBindTextureUnit(0, 0);
	}

	
void OpenGLTexture2D::SetData(void* Data, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		uint32_t bpc = m_DataFormat == GL_RGBA ? 4 : 3; //bytes per channel
		CoreLogger::Assert(Size == ((uint32_t)(m_Width * m_Height) * bpc), "Size Data must be entire texture!");
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);
		if (!m_ImageData.first)
		{
			m_ImageData.first = new uint8_t[Size];
#ifdef AG_PLATFORM_WINDOWS
			memcpy_s(m_ImageData.first,Size, Data, Size);
#else
			memcpy(m_ImageData.first, Data, Size);
#endif
			m_ImageData.second = Size;
		}
	}

}