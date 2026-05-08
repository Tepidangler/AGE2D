#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLVertexArray.h"

#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
namespace AGE
{

	/**
 * @brief Converts a given ShaderDataType to its corresponding OpenGL base type.
 *
 * This function takes in a ShaderDataType and returns the equivalent OpenGL data type. The ShaderDataType is an enumeration that represents different types of shader data, such as float, int, bool etc. 
 * The returned value can be GL_FLOAT, GL_INT or GL_BOOL depending on the input ShaderDataType. If the input is not recognized, it asserts false and logs an error message "Unknown ShaderDataType!".
 *
 * @param Type The ShaderDataType to convert.
 * 
 * @return The corresponding OpenGL base type for the given ShaderDataType. Returns GL_INT if the ShaderDataType is not recognized.
 */
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType Type)
	{
		switch ((int)Type)
		{
		case 0:
			break;
		case 1:
			return GL_FLOAT;
			break;
		case 2:
			return GL_FLOAT;
			break;
		case 3:
			return GL_FLOAT;
			break;
		case 4:
			return GL_FLOAT;
			break;
		case 5:
			return GL_FLOAT;
			break;
		case 6:
			return GL_FLOAT;
			break;
		case 7:
			return GL_INT;
			break;
		case 8:
			return GL_INT;
			break;
		case 9:
			return GL_INT;
			break;
		case 10:
			return GL_INT;
			break;
		case 11:
			return GL_BOOL;
			break;
		default:
		{
			break;
		}
		}

		CoreLogger::Assert(false, "Unknown ShaderDataType!");
		return 0;
	}

	/**
 * @brief OpenGLVertexArray is a class that represents an OpenGL Vertex Array Object. It provides methods for creating and manipulating vertex array objects in OpenGL.
 */
OpenGLVertexArray::OpenGLVertexArray()
	{
		AGE_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_ArrayID);
	}
	/**
 * @brief Destructor for OpenGLVertexArray class. Deletes the vertex array object from GPU memory.
 * 
 * This function is responsible for deleting the vertex array object (VAO) that was created in the constructor of this class. It does so by calling glDeleteVertexArrays with the ID of the VAO to be deleted.
 * 
 * @return void
 */
OpenGLVertexArray::~OpenGLVertexArray()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_ArrayID);
		
	}
	/** 
 * @brief This function binds the vertex array object.
 * 
 * The OpenGLVertexArray::Bind() function is used to bind a Vertex Array Object (VAO) which serves as a container for storing VBOs and other data related to rendering in OpenGL. It sets the VAO as the active VAO, meaning any subsequent calls to vertex array-specific functions will affect this object.
 * 
 * @return void No return value is expected from this function.
 */
void OpenGLVertexArray::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);
	}
	/** 
 * @brief This function unbinds the current vertex array object.
 * 
 * @param None
 * @return void
 */
void OpenGLVertexArray::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(0);
		
	}
	/**
 * @brief Adds a Vertex Buffer to the OpenGL Vertex Array object.
 * 
 * The function binds the vertex array, adds the given vertex buffer to the list of buffers associated with this vertex array, and sets up the vertex attributes for each element in the layout of the vertex buffer.
 * 
 * @param[in] VertexBuffer A reference to a Vertex Buffer object. The function expects that the layout of the vertex buffer has been set and is not empty.
 * 
 * @return void
 */
void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		CoreLogger::Assert(VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_ArrayID);


		VertexBuffer->Bind();

		uint32_t index = 0;
		const auto& Layout = VertexBuffer->GetLayout();
		for (const auto& E : Layout)
		{
			switch (E.DataType)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				EnableVertexAttribArray((int)index);

				MakeVertexAttribPtr(index,
					(int)E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					E.Normalized ? GL_TRUE : GL_FALSE,
					(int)Layout.GetStride(),
					(const void*)&E.Offset);
				index++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint32_t count = E.GetComponentCount();
				for (uint32_t i = 0; i < count; i++)
				{
					EnableVertexAttribArray((int)index);

					MakeVertexAttribPtr(index,
						(int)E.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(E.DataType),
						E.Normalized ? GL_TRUE : GL_FALSE,
						(int)Layout.GetStride(),
						(const void*)(E.Offset+ sizeof(float) * count * i));
					glVertexAttribDivisor(index, 1);
					index++;
				}

				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Boolean:
			{
				EnableVertexAttribArray((int)index);

				glVertexAttribIPointer(index,
					(int)E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					(int)Layout.GetStride(),
					(const void*)&E.Offset);
				index++;
				break;
			}
			default:
			{
				CoreLogger::Assert(false, "Unknown Data Type");
				break;
			}
			}


		}

		m_VertexBuffers.push_back(VertexBuffer);
	}
	/**
 * @brief This function sets the index buffer for the OpenGL vertex array.
 * 
 * @param[in] Ref<IndexBuffer>& IndexBuffer - A reference to an instance of IndexBuffer class.
 * 
 * @return void
 */
void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);

		IndexBuffer->Bind();

		m_IndexBuffer = IndexBuffer;
	}
	/** 
 * @brief Enables a vertex attribute array.
 * 
 * This function enables the vertex attribute array with the given ID. The ArrayID is an integer that represents the index of the generic vertex attribute to be enabled.
 * 
 * @param ArrayID An integer representing the index of the generic vertex attribute to be enabled.
 * @return void
 */
void OpenGLVertexArray::EnableVertexAttribArray(int ArrayID) const
	{
		glEnableVertexAttribArray((uint32_t)ArrayID);
	}
	/**
 * @brief This function sets up the vertex attribute pointer for a specific index.
 *
 * The function takes in several parameters to specify the details of the vertex attribute array, including the index, size, type, normalization flag, stride and pointer. 
 * It then calls glVertexAttribPointer with these values if the provided type is either GL_FLOAT or GL_INT. If not, it asserts false and logs an error message.
 *
 * @param index The index of the vertex attribute array to be modified.
 * @param size The number of components per generic vertex attribute. Must be 1, 2, 3, or 4.
 * @param type The data type of each component in the array. Must be GL_FLOAT or GL_INT.
 * @param normalized If true, the fixed-point data values are rescaled to the range [-1, 1] when read from an integer format. Otherwise, the fixed-point data values are left as they are.
 * @param stride The byte offset between consecutive generic vertex attributes.
 * @param pointer A pointer to the first component of the array.
 *
 * @return void
 */
void OpenGLVertexArray::MakeVertexAttribPtr(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const
	{
		if (type == GL_FLOAT || type == GL_INT)
		{
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);

			
			return;
		}

		CoreLogger::Assert(false, "MakeVertexAttribPtr Failed: Must be GL_FLOAT or GL_INT");
	
	}

}