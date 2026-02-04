#pragma once
#include "Texture/Public/Texture.h"
#include <glad/glad.h>

namespace AGE
{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(const std::string& Path);
		OpenGLTexture2D(const tmx_image* Image);
		OpenGLTexture2D(const std::vector<std::string>& Paths);
		OpenGLTexture2D(const TextureSpecification& Spec);
		OpenGLTexture2D(const Image* Img, uint32_t Width, uint32_t Height, int Channels, size_t Size);
		~OpenGLTexture2D();

		virtual void Bind(uint32_t Slot = 0) const override;

		virtual void Unbind() const override;

		virtual uint32_t GetWidth() const override { return (uint32_t)m_Width;}

		virtual uint32_t GetHeight() const override { return (uint32_t)m_Height; }
		std::pair<uint8_t*, size_t> GetTextureData() override {return m_ImageData;}
		virtual void SetData(void* Data, uint32_t Size) override;

		virtual uint32_t GetNrChannels() const { return (uint32_t)m_nrChannels; }

		virtual uint32_t GetTextureID() const override { return m_TextureID; }
		virtual uint64_t GetAssetID() const override { return m_AssetID; }
		virtual void SetAssetID(uint64_t ID) override { m_AssetID = ID; }
		virtual std::string GetName() const override { return m_Name; }
		virtual void SetName(const std::string& Name) { m_Name = Name; }
		virtual std::string GetTextureFilePath() const override { return m_Path; }
		virtual void SetTextureFilePath(const std::string& Path) { m_Path = Path; }

		virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

		virtual bool operator==(const Texture& Other) const override
		{
			return m_TextureID == ((OpenGLTexture2D&)Other).m_TextureID;
		}

	private:

		std::string m_Path;
		std::string m_Name;
		uint32_t m_TextureID;
		uint64_t m_AssetID;
		int m_Width,m_Height,m_nrChannels;
		TextureSpecification m_Specification;
		std::pair<uint8_t*,size_t> m_ImageData = {nullptr, 0};

		GLenum m_InternalFormat, m_DataFormat;



	
	};


}