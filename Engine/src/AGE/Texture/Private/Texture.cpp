#include "AGEpch.hpp"
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLTexture.h"

namespace AGE
{

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
	T* Texture2D::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}

	void TextureSpecification::Serialize(DataWriter* Serializer, const TextureSpecification& Instance)
	{
		Serializer->WriteRaw<uint32_t>(Instance.Width);
		Serializer->WriteRaw<uint32_t>(Instance.Height);
		Serializer->WriteRaw<uint8_t>((uint8_t)Instance.Format);
		Serializer->WriteRaw<bool>(Instance.GenerateMips);
	}

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