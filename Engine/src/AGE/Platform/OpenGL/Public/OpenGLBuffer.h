#pragma once

#include "Render/Public/RenderBuffer.h"

namespace AGE
{


	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t Size);
		OpenGLVertexBuffer(Matrix3D* Vertices, uint32_t Size);
		

		OpenGLVertexBuffer(float* Vertices, uint32_t Size);

		virtual ~OpenGLVertexBuffer();

		//virtual void SetData() = 0;

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void InvalidateBuffer() const override;

		inline virtual void SetLayout(const BufferLayout& Layout) override { m_Layout = Layout; }

		static inline uint32_t GetRendererID() { return s_RendererID; }

		virtual void AddDataToBuffer(float* Verticies, uint32_t Size) override;

		virtual void AddDataToBuffer(const void* Verticies, uint32_t Size) override;

		virtual Vertex* CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;
		virtual CircleVertex* CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID) override;
		virtual LineVertex* CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID = -1) override;
		virtual TextVertex* CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID,int EntID) override;
		virtual TileVertex* CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;

		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	
	private:

		uint32_t m_RendererID;
		static uint32_t s_RendererID;
		BufferLayout m_Layout;

	
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* Indices, uint32_t Size);

		virtual ~OpenGLIndexBuffer();

	//	virtual void SetData() = 0;

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void InvalidateBuffer() const override;

		virtual uint32_t GetCount() override { return m_Count; }

	private:

		uint32_t m_RendererID;

		uint32_t m_Count;

	};


	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		OpenGLUniformBuffer(uint32_t Size, uint32_t Binding);

		virtual ~OpenGLUniformBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetData(const void* Data, uint32_t Size, uint32_t Offset = 0) override;

	private:

		uint32_t m_RendererID;
	};
}