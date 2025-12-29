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
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Path);
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const tmx_image* Image)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Image);
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::vector<std::string>& Paths)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Paths);
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const TextureSpecification& Spec)
	{
		switch (Renderer::GetAPI())
		{
			case 0:
				AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
				break;
			case 1:
				return CreateRef<OpenGLTexture2D>(Spec);
				break;
			default:
				AGE_CORE_ASSERT(false, "Unknown Renderer API!");
				return nullptr;
				break;
			}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const Image* Img, uint32_t Width, uint32_t Height, int Channels, size_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLTexture2D>(Img, Width, Height, Channels, Size);
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	template<typename T>
	T* Texture2D::As()
	{
		AGE_CORE_ASSERT(false, "As() Failed!");
		return nullptr;
	}
}