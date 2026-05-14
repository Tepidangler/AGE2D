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

	/**
 * @brief Creates a new VertexBuffer of the specified size. The type and usage of the buffer are determined by the current Rendering API in use.
 * 
 * @param Size The size of the vertex buffer to create, in bytes.
 * @return A reference to the newly created VertexBuffer.
 */
/**
 * @brief Creates a new VertexBuffer of the specified size. The type and usage of the buffer are determined by the current Rendering API in use.
 * 
 * @param Size The size of the vertex buffer to create, in bytes.
 * @return A reference to the newly created VertexBuffer. If the current RendererAPI is not supported or an unknown error occurs, a nullptr will be returned instead.
 */
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

	/**
 * @brief Creates a new vertex buffer object.
 * 
 * This function creates and initializes a new VertexBuffer object based on the current rendering API in use. The data for the vertices is passed as an array of floats, with the size of this array also provided. If an unsupported rendering API is currently in use, nullptr is returned.
 */
"Creates a new vertex buffer based on the current Rendering API."
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
	/**
 * @brief BufferLayout is a class that represents the layout of a buffer in memory. 
 * It provides methods for adding elements to the buffer and retrieving them by index.
 * The buffer can hold any type of data, but it's typically used with primitive types like int, float, etc.
 */
/**
 * @brief BufferLayout is a class that represents the layout of a buffer in memory.
 * 
 * This class provides methods for managing and manipulating the layout of a buffer in memory. It does not handle the actual data within the buffer, only its structure.
 */
BufferLayout::BufferLayout()
	{
	}
	/**
 * @brief Creates a new UniformBuffer instance.
 * 
 * This function creates and initializes a new UniformBuffer object of the specified size and binding point. The type of buffer to be created is determined by the current Renderer API in use. If OpenGL is currently being used, an OpenGLUniformBuffer will be created; otherwise, if no supported API is found, null is returned.
 * 
 * @param Size The size (in bytes) of the UniformBuffer to create.
 * @param Binding The binding point for the UniformBuffer in the shader program.
 * 
 * @return A reference to a new UniformBuffer object if successful, nullptr otherwise.
 */
/**
 * @brief Creates a new uniform buffer.
 * 
 * This function creates and initializes a new UniformBuffer object of the specified size and binding point. The type of the underlying implementation is determined by the current Renderer API in use.
 * 
 * @param Size The size of the uniform buffer, in bytes.
 * @param Binding The binding point for this uniform buffer. This determines which shader program can access it.
 * 
 * @return A reference to a new UniformBuffer object. If an unsupported Renderer API is detected or if there are issues with creating the buffer, nullptr is returned instead.
 */
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
	/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return Returns a null pointer of type T*
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A pointer to an object of type T* which is currently always null.
 */
T* VertexBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
	template<typename T>
	/**
 * @brief This function is currently not implemented and will always return a null pointer.
 * It's intended to provide the ability to cast this IndexBuffer instance to another type, but it's not yet supported. 
 * The function will assert false with an error message indicating that As() Failed!
 * @return nullptr Always returns nullptr.
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
T* IndexBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
	template<typename T>
	/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return Returns a null pointer of type T*
 */
T* UniformBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
}
