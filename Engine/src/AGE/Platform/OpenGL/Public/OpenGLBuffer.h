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

		void Bind() const override;

		void Unbind() const override;

		void InvalidateBuffer() const override;

		/**
 * @brief Sets the layout for a buffer.
 * @param Layout The new layout to be set.
 */
void SetLayout(const BufferLayout& Layout) override { m_Layout = Layout; }

		/**
 * @brief Returns the renderer ID of the current scene.
 *
 * This function returns the unique identifier for the renderer used by the current scene. The returned value is a uint32_t, which represents an unsigned integer type in C++. 
 *
 * @return A uint32_t representing the renderer ID of the current scene.
 */
static uint32_t GetRendererID() { return s_RendererID; }

		void AddDataToBuffer(float* Verticies, uint32_t Size) override;

		void AddDataToBuffer(const void* Verticies, uint32_t Size) override;

		Vertex* CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;
		CircleVertex* CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID) override;
		LineVertex* CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID) override;
		TextVertex* CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID,int EntID) override;
		TileVertex* CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;

		/**
 * @brief Returns the layout of this buffer.
 * @return A constant reference to the buffer's layout.
 */
const BufferLayout& GetLayout() const override { return m_Layout; }
	
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

		void Bind() const override;

		void Unbind() const override;

		void InvalidateBuffer() const override;

		/**
 * @brief This function returns the current count value.
 * @return The current count value as a uint32_t.
 */
uint32_t GetCount() override { return m_Count; }

	private:

		uint32_t m_RendererID;

		uint32_t m_Count;

	};


	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		OpenGLUniformBuffer(uint32_t Size, uint32_t Binding);

		virtual ~OpenGLUniformBuffer();

		void Bind() override;
		void Unbind() override;
		void SetData(const void* Data, uint32_t Size, uint32_t Offset = 0) override;

	private:

		uint32_t m_RendererID;
	};
}