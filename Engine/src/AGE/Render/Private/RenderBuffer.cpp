#include "AGEpch.hpp"
#include "Render/Public/RenderBuffer.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLBuffer.h"

namespace AGE
{
	Ref<VertexBuffer> VertexBuffer::Create(Matrix3D* Vertices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLVertexBuffer>(Vertices, Size);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLVertexBuffer>(Size);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* Vertices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "Renderer None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLVertexBuffer>(Vertices, Size);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, uint32_t Count)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLIndexBuffer>(Indices, Count);
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}
	BufferLayout::BufferLayout()
	{
	}
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t Size, uint32_t Binding)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLUniformBuffer>(Size, Binding);
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	template<typename T>
	T* VertexBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
	template<typename T>
	T* IndexBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
	template<typename T>
	T* UniformBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
}
