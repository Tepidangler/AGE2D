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
			}

			AGE_CORE_ASSERT(false, "Data Format not supported by AGE!");
			return 0;
		}

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
			}

			AGE_CORE_ASSERT(false, "Internal Format not supported by AGE!");
			return 0;
		}

	}

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& Spec)
		:m_Specification(Spec), m_Width(Spec.Width), m_Height(Spec.Height)
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

	OpenGLTexture2D::OpenGLTexture2D(const Image* Img, uint32_t Width, uint32_t Height, int Channels, size_t Size)
		:m_Width(Width), m_Height(Height), m_nrChannels(Channels)
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

		AGE_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported!");
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
		:m_Path(Path)
	{
		AGE_PROFILE_FUNCTION();
		//stbi_set_flip_vertically_on_load(true);
		unsigned char* Data = nullptr;
		{
			stbi_set_flip_vertically_on_load(true);
			AGE_PROFILE_SCOPE("stbi_load -> OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)");
			Data = stbi_load(Path.c_str(), &m_Width, &m_Height, &m_nrChannels, 0);
		}
		AGE_CORE_ASSERT(Data, "Unable to Load Image");

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
		else if (m_nrChannels == 2)
		{
			InternalFormat = GL_RG8;
			DataFormat = GL_RG;
		}
		else
		{
			InternalFormat = GL_R8;
			DataFormat = GL_RED;
		}
		m_InternalFormat = InternalFormat;
		m_DataFormat = DataFormat;

		AGE_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported!");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		glTextureStorage2D(m_TextureID, 1, InternalFormat, m_Width, m_Height);
		
		//Set Texture wrapping params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		//Set Texture filtering params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, DataFormat, GL_UNSIGNED_BYTE, Data);

		stbi_image_free(Data);
		std::filesystem::path FilePath = m_Path;
		m_Name = Utils::EngineStatics::GetFilename(FilePath);
		
	}

	OpenGLTexture2D::OpenGLTexture2D(const tmx_image* Image)
	{
		char* TexData = (char*)Image->resource_image;

		
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
		//AGE_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported!")
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

	OpenGLTexture2D::OpenGLTexture2D(const std::vector<std::string>& Paths)
	{
		AGE_PROFILE_FUNCTION();
		//stbi_set_flip_vertically_on_load(true);
		for (int i = 0; i < Paths.size(); i++)
		{


			unsigned char* Data = nullptr;
			{
				AGE_PROFILE_SCOPE("stbi_load -> OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)");
				Data = stbi_load(Paths[i].c_str(), &m_Width, &m_Height, &m_nrChannels, 0);

			}
			AGE_CORE_ASSERT(Data, "Unable to Load Image");

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

			AGE_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported!")
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


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_TextureID);
	}
	void OpenGLTexture2D::Bind(uint32_t Slot) const
	{
		AGE_PROFILE_FUNCTION();
		glBindTextureUnit(Slot, m_TextureID);

	}
	void OpenGLTexture2D::Unbind() const
	{
		glBindTextureUnit(0, 0);
	}

	void OpenGLTexture2D::SetData(void* Data, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		uint32_t bpc = m_DataFormat == GL_RGBA ? 4 : 3; //bytes per channel
		AGE_CORE_ASSERT(Size == m_Width * m_Height * bpc, "Size Data must be entire texture!");
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);
	}

}