#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace AGE
{

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
		}

		AGE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		AGE_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_ArrayID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_ArrayID);
		
	}
	void OpenGLVertexArray::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(0);
		
	}
	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		AGE_CORE_ASSERT(VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

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
					E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					E.Normalized ? GL_TRUE : GL_FALSE,
					Layout.GetStride(),
					(const void*)E.Offset);
				index++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = E.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					EnableVertexAttribArray(index);

					MakeVertexAttribPtr(index,
						E.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(E.DataType),
						E.Normalized ? GL_TRUE : GL_FALSE,
						Layout.GetStride(),
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
			case ShaderDataType::Bool:
			{
				EnableVertexAttribArray(index);

				glVertexAttribIPointer(index,
					E.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(E.DataType),
					Layout.GetStride(),
					(const void*)E.Offset);
				index++;
				break;
			}
			default:
			{
				AGE_CORE_ASSERT(false, "Unknown Data Type");
				break;
			}
			}


		}

		m_VertexBuffers.push_back(VertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer)
	{
		AGE_PROFILE_FUNCTION();
		glBindVertexArray(m_ArrayID);

		IndexBuffer->Bind();

		m_IndexBuffer = IndexBuffer;
	}
	void OpenGLVertexArray::EnableVertexAttribArray(int ArrayID) const
	{
		glEnableVertexAttribArray(ArrayID);		
	}
	void OpenGLVertexArray::MakeVertexAttribPtr(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const
	{
		if (type == GL_FLOAT || type == GL_INT)
		{
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);

			
			return;
		}

		AGE_CORE_ASSERT(false, "MakeVertexAttribPtr Failed: Must be GL_FLOAT or GL_INT");
	
	}

}