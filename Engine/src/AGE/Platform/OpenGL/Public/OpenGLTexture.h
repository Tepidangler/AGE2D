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

		void Bind(uint32_t Slot = 0) const override;

		void Unbind() const override;

		uint32_t GetWidth() const override { return (uint32_t)m_Width;}

		uint32_t GetHeight() const override { return (uint32_t)m_Height; }
		std::pair<uint8_t*, size_t> GetTextureData() override {return m_ImageData;}
		void SetData(void* Data, uint32_t Size) override;

		virtual uint32_t GetNrChannels() const { return (uint32_t)m_nrChannels; }

		uint32_t GetTextureID() const override { return m_TextureID; }
		uint64_t GetAssetID() const override { return m_AssetID; }
		void SetAssetID(uint64_t ID) override { m_AssetID = ID; }
		std::string GetName() const override { return m_Name; }
		void SetName(const std::string& Name) override { m_Name = Name; }
		std::string GetTextureFilePath() const override { return m_Path; }
		void SetTextureFilePath(const std::string& Path) override { m_Path = Path; }

		const TextureSpecification& GetSpecification() const override { return m_Specification; }

		bool operator==(const Texture& Other) const override
		{
			return m_TextureID == ((OpenGLTexture2D&)Other).m_TextureID;
		}

	private:

		std::string m_Path;
		std::string m_Name;
		uint32_t m_TextureID;
		uint64_t m_AssetID;
		TextureSpecification m_Specification;
		int m_Width,m_Height,m_nrChannels;
		std::pair<uint8_t*,size_t> m_ImageData = {nullptr, 0};

		GLenum m_InternalFormat, m_DataFormat;



	
	};


}