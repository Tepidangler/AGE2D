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

		/**
 * @brief This function returns the width of an object as a uint32_t value.
 * @return The width of the object represented by a uint32_t.
 */
uint32_t GetWidth() const override { return (uint32_t)m_Width;}

		/**
 * @brief This function returns the height of an object.
 *
 * @return The height as a uint32_t value.
 */
uint32_t GetHeight() const override { return (uint32_t)m_Height; }
		/**
 * @brief This function returns the texture data along with its size.
 * @return A pair of uint8 pointer and size_t, representing the texture data and its size respectively.
 */
std::pair<uint8_t*, size_t> GetTextureData() override {return m_ImageData;}
		void SetData(void* Data, uint32_t Size) override;

		/**
 * @brief Returns the number of channels in the system.
 *
 * This function returns the current number of channels that are active in the system. It does not take any parameters and always returns a uint32_t value representing the number of channels.
 *
 * @return The number of channels as an unsigned 32-bit integer.
 */
virtual uint32_t GetNrChannels() const { return (uint32_t)m_nrChannels; }

		/**
 * @brief Returns the texture ID of this object.
 *
 * This function returns the unique identifier for the texture associated with this object. The value is constant and does not change over time.
 *
 * @return A uint32_t representing the texture ID.
 */
uint32_t GetTextureID() const override { return m_TextureID; }
		/**
 * @brief This function returns the Asset ID of an object.
 * @return The asset ID as a uint64_t value.
 */
uint64_t GetAssetID() const override { return m_AssetID; }
		/**
 * @brief Sets the Asset ID of an object.
 * @param ID The unique identifier for the asset.
 * @return void
 */
void SetAssetID(uint64_t ID) override { m_AssetID = ID; }
		/**
 * @brief Returns the name of the object.
 * @return The name of the object as a string.
 */
std::string GetName() const override { return m_Name; }
		/**
 * @brief Sets the name of the object.
 * @param[in] Name The new name to set for the object.
 */
void SetName(const std::string& Name) override { m_Name = Name; }
		/**
 * @brief Returns the file path of the texture.
 * @return The file path as a string. If no path is set, returns an empty string.
 */
std::string GetTextureFilePath() const override { return m_Path; }
		/**
 * @brief Sets the texture file path for rendering.
 * @param Path The new file path to be set as a string reference.
 * @return None, void function that directly modifies member variable 'm_Path'.
 */
void SetTextureFilePath(const std::string& Path) override { m_Path = Path; }

		/**
 * @brief Returns the texture specification of this object.
 * @return A constant reference to the texture specification (m_Specification).
 */
const TextureSpecification& GetSpecification() const override { return m_Specification; }

		/**
 * @brief Compares this OpenGLTexture2D object with another for equality.
 *
 * This function compares the texture ID of this object with that of the provided Texture object. It first casts the other object to an OpenGLTexture2D, then checks if their texture IDs are equal.
 * 
 * @param Other The Texture object to compare against.
 * @return True if the texture IDs match; false otherwise.
 */
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
		int m_Width,m_Height,m_nrChannels = 0;
		std::pair<uint8_t*,size_t> m_ImageData = {nullptr, 0};

		GLenum m_InternalFormat, m_DataFormat;



	
	};


}