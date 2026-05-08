#include "AGEpch.hpp"
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLTexture.h"

namespace AGE
{

	/**
 * @brief Creates a reference to a Texture2D object. The type of the texture is determined by the current renderer API.
 * @param Path The path to the image file for the texture.
 * @return A reference to a Texture2D object, or nullptr if an unsupported RendererAPI is used.
 */
Ref<Texture2D> Texture2D::Create(const std::string& Path)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Path);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Creates a new Texture2D object based on the current Rendering API.
 *
 * This function creates and returns a reference to a Texture2D object, which is specific to the currently used rendering API. 
 * It takes as input a pointer to an image data structure (tmx_image). The type of texture created will depend on the current RendererAPI in use.
 * If no supported Rendering API is found, it asserts false and returns nullptr.
 *
 * @param Image Pointer to the image data that the Texture2D object should be based on.
 * 
 * @return A reference to a Texture2D object of the appropriate type for the current RendererAPI in use. If no supported API is found, it returns nullptr.
 */
Ref<Texture2D> Texture2D::Create(const tmx_image* Image)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Image);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Creates a reference to a Texture2D object. The type of texture is determined by the current renderer API.
 * @param Paths A vector of strings representing the paths to the textures.
 * @return A reference to a Texture2D object, or nullptr if an unsupported RendererAPI is encountered.
 */
Ref<Texture2D> Texture2D::Create(const std::vector<std::string>& Paths)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Paths);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Creates a new Texture2D object based on the given specification.
 * The type of texture to be created is determined by the current renderer API in use.
 * 
 * @param Spec The specification for the texture to be created. This includes things like width, height, format etc.
 * @return A reference to the newly created Texture2D object. If no suitable RendererAPI is found or an error occurs during creation, a null reference is returned.
 */
Ref<Texture2D> Texture2D::Create(const TextureSpecification& Spec)
	{
		switch (Renderer::GetAPI())
		{
			case 0:
				CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
				break;
			case 1:
				return CreateRef<OpenGLTexture2D>(Spec);
				break;
			default:
				CoreLogger::Assert(false, "Unknown Renderer API!");
				return nullptr;
				break;
			}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}
	/**
 * @brief Creates a new Texture2D object. The type of the texture is determined by the current renderer API.
 * @param Img Pointer to an Image object, can be null if only dimensions are specified.
 * @param Width Width of the texture in pixels.
 * @param Height Height of the texture in pixels.
 * @param Channels Number of color channels in the image data.
 * @param Size Total size of the image data in bytes.
 * @return A reference to a Texture2D object, or nullptr if an unsupported Renderer API is used.
 */
Ref<Texture2D> Texture2D::Create(const Image* Img, uint32_t Width, uint32_t Height, int Channels, size_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Img, Width, Height, Channels, Size);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	template<typename T>
	/**
 * @brief This function is currently not implemented. It will return a pointer to an object of type T.
 *        If called, it will assert and crash the program with the message "As() Failed!".
 * 
 * @return nullptr Always returns nullptr.
 */
T* Texture2D::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}

	/**
 * @brief This function serializes a TextureSpecification instance into the provided DataWriter.
 * 
 * @param Serializer Pointer to an instance of DataWriter that will be used for writing data.
 * @param Instance The TextureSpecification instance to be serialized.
 * 
 * @return void
 */
void TextureSpecification::Serialize(DataWriter* Serializer, const TextureSpecification& Instance)
	{
		Serializer->WriteRaw<uint32_t>(Instance.Width);
		Serializer->WriteRaw<uint32_t>(Instance.Height);
		Serializer->WriteRaw<uint8_t>((uint8_t)Instance.Format);
		Serializer->WriteRaw<bool>(Instance.GenerateMips);
	}

	/**
 * @brief Deserialize a TextureSpecification from a DataReader.
 * 
 * This function reads the Width, Height, Format and GenerateMips fields of a TextureSpecification object from a DataReader.
 * The Format field is read as an uint8_t and then cast to ImageFormat.
 * @param Serializer A pointer to the DataReader that provides the serialized data.
 * @param Instance The TextureSpecification object to be deserialized.
 */
void TextureSpecification::Deserialize(DataReader* Serializer, TextureSpecification& Instance)
	{
		Serializer->ReadRaw<uint32_t>(Instance.Width);
		Serializer->ReadRaw<uint32_t>(Instance.Height);
		uint8_t format;
		Serializer->ReadRaw<uint8_t>(format);
		Instance.Format = (ImageFormat)format;
		Serializer->ReadRaw<bool>(Instance.GenerateMips);
	}
}