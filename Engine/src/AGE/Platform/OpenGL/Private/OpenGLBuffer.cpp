#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLBuffer.h"
#include "Render/Public/Renderer2D.h"

#include <glad/glad.h>

namespace AGE
{

	uint32_t OpenGLVertexBuffer::s_RendererID = 0;
			////////////////////////////////////////////////////////////////////
			//																  //
			//																  //
			//						VERTEX BUFFER							  //
			//																  //
			//																  //
			////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		Bind();
		glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
		
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(Matrix3D* Vertices, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_DYNAMIC_DRAW);
		
	}
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t Size)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		s_RendererID = m_RendererID;
		Bind();
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
		

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
		
	}
	void OpenGLVertexBuffer::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	void OpenGLVertexBuffer::InvalidateBuffer() const
	{
		AGE_PROFILE_FUNCTION();
		glInvalidateBufferData(m_RendererID);
		
		glDeleteBuffers(1, &m_RendererID);
		
	}

	void OpenGLVertexBuffer::AddDataToBuffer(float* Verticies, uint32_t Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Verticies);
		
	}

	void OpenGLVertexBuffer::AddDataToBuffer(const void* Verticies, uint32_t Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Verticies);
		
	}

	Vertex* OpenGLVertexBuffer::CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID)
	{

		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexTexCoords = TexCoords[i];
			Target->VertexColor = Color;
			Target->VertexTexID = ID;
			Target->VertexTilingFactor = TilingFactor;
			Target->VertexEntityID = EnttID;
			Target++;
		}

		return Target;
	}
	CircleVertex* OpenGLVertexBuffer::CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexWorldPosition = Transform * Position[i];
			Target->VertexLocalPosition = Position[i] * 2.f;
			Target->VertexColor = Color;
			Target->VertexThickness = Thickness;
			Target->VertexFade = Fade;
			Target->CircleEntityID = EntID;
			Target++;
		}

		return Target;
	}
	LineVertex* OpenGLVertexBuffer::CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID)
	{
		Target->VertexPosition = Position0;
		Target->VertexColor = Color;
		Target->LineEntityID = EntID;
		Target++;

		Target->VertexPosition = Position1;
		Target->VertexColor = Color;
		Target->LineEntityID = EntID;
		Target++;
		
		return Target;
	}

	TextVertex* OpenGLVertexBuffer::CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID,int EntID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexColor = Color;
			Target->VertexTexCoords = TexCoords[i];
			Target->TexID = TexID;
			Target->EntityID = 0;
			Target++;
		}


		return Target;
	}

	TileVertex* OpenGLVertexBuffer::CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID)
	{
		for (int i = 0; i < 4; i++)
		{
			Target->VertexPosition = Transform * Position[i];
			Target->VertexTexCoords = TexCoords[i];
			Target->VertexColor = Color;
			Target->VertexTexID = ID;
			Target->VertexTilingFactor = TilingFactor;
			Target->VertexEntityID = EnttID;
			Target++;
		}

		return Target;
	}

////////////////////////////////////////////////////////////////////
//																  //
//																  //
//						INDEX BUFFER							  //
//																  //
//																  //
////////////////////////////////////////////////////////////////////	 	

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count)
		:m_Count(Count)
	{
		AGE_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
		
	}
	void OpenGLIndexBuffer::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		AGE_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
	}
	void OpenGLIndexBuffer::InvalidateBuffer() const
	{
		AGE_PROFILE_FUNCTION();
		glInvalidateBufferData(m_RendererID);
		
		glDeleteBuffers(1, &m_RendererID);
		
	}

////////////////////////////////////////////////////////////////////
//																  //
//																  //
//						UNIFORM BUFFER							  //
//																  //
//																  //
////////////////////////////////////////////////////////////////////

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t Size, uint32_t Binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, Size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, Binding, m_RendererID);
	}
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLUniformBuffer::Bind()
	{
	}
	void OpenGLUniformBuffer::Unbind()
	{
	}
	void OpenGLUniformBuffer::SetData(const void* Data, uint32_t Size, uint32_t Offset)
	{
		glNamedBufferSubData(m_RendererID, Offset, Size, Data);
	}
}