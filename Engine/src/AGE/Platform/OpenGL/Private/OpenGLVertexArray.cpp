#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLVertexArray.h"

#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
namespace AGE
{

	/**
 * @brief Converts a given ShaderDataType to its corresponding OpenGL base type.
 *
 * This function takes in a ShaderDataType and returns the equivalent OpenGL base type for that data type. The ShaderDataType is an enum defined elsewhere in the code, with values representing different types of data (like FLOAT, INT, BOOL). 
 *
 * @param Type The ShaderDataType to convert.
 * @return GLenum The corresponding OpenGL base type for the given ShaderDataType.
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

	COMMENT:
/**
 * @brief OpenGLVertexArray is a class that represents an OpenGL Vertex Array Object. It provides methods for creating and binding the vertex array object.
 */
CONFIDENCE: 1.0;

OpenGLVertexArray::OpenGLVertexArray()
	{
		AGE_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_ArrayID);
	}
	/**
 * @brief Destructor for OpenGLVertexArray class. Deletes the vertex array object from GPU memory.
 * 
 * This function is responsible for deleting a Vertex Array Object (VAO) from GPU memory. The VAO was created during initialization and holds references to other data such as buffers, attributes etc. that are used in rendering operations. After deletion, this VAO can no longer be used by the OpenGL context.
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
 * It uses OpenGL's glBindVertexArray() function to bind this Vertex Array Object (VAO). The VAO is an object that contains all of the state needed to supply vertex data, such as what vertex arrays to use, how to interpret them, and how to render them.
 * 
 * @return void
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
	
void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		CoreLogger::Assert(!VertexBuffer->GetLayout().GetElements().empty(), "Vertex Buffer has no layout!");

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
				EnableVertexAttribArray(index);

				MakeVertexAttribPtr(index,
					(int)E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					E.Normalized ? GL_TRUE : GL_FALSE,
					(int)Layout.GetStride(),
					(const void*)(uintptr_t)E.Offset);
				index++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint32_t count = E.GetComponentCount();
				for (uint32_t i = 0; i < count; i++)
				{
					EnableVertexAttribArray(index);

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
				EnableVertexAttribArray(index);

				glVertexAttribIPointer(index,
					(int)E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					(int)Layout.GetStride(),
					(const void*)(uintptr_t)E.Offset);
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
 * @brief This function sets the index buffer for the OpenGL Vertex Array.
 * 
 * @param IndexBuffer A reference to an Index Buffer object.
 */
void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);

		IndexBuffer->Bind();

		m_IndexBuffer = IndexBuffer;
	}
	/** 
 * @brief This function enables a vertex attribute array.
 * 
 * @param ArrayID The ID of the vertex attribute array to be enabled.
 * @return void
 */
void OpenGLVertexArray::EnableVertexAttribArray(uint32_t ArrayID) const
	{
		glEnableVertexAttribArray(ArrayID);
	}
	/**
 * @brief This function sets up the vertex attribute pointer for a specific index.
 * It takes in parameters such as size of data, type of data (GL_FLOAT or GL_INT), 
 * whether the data is normalized, stride and pointer to the data.
 * The function uses glVertexAttribPointer OpenGL function to set up the vertex attribute pointer.
 * @param index The index of the generic vertex attribute to be modified.
 * @param size Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, or 4.
 * @param type Specifies the data type of each component in the array. Must be GL_FLOAT or GL_INT.
 * @param normalized If true, the integer values are treated as a stream of normalized fixed-point values.
 * @param stride The byte offset between consecutive generic vertex attributes.
 * @param pointer Specifies a pointer to the first component of the array.
 * @return void
 */
void OpenGLVertexArray::MakeVertexAttribPtr(uint32_t index, int size, uint32_t type, uint8_t normalized, int stride, const void* pointer) const
	{
		if (type == GL_FLOAT || type == GL_INT)
		{
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
			return;
		}

		CoreLogger::Assert(false, "MakeVertexAttribPtr Failed: Must be GL_FLOAT or GL_INT");
	
	}

}