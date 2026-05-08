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

		/**
 * @brief Sets the layout for a buffer.
 *
 * This function sets the layout of a buffer to a new value, which is passed as an argument. The BufferLayout object being set should be provided in the parameter 'Layout'.
 * 
 * @param Layout A const reference to the new BufferLayout that will replace the current one.
 */
inline virtual void SetLayout(const BufferLayout& Layout) override { m_Layout = Layout; }

		/**
 * @brief Returns the unique identifier for the renderer.
 *
 * This function returns a constant value representing the unique ID of the renderer. The returned value is typically used to identify different types of rendering operations in a graphics system.
 *
 * @return uint32_t A 32-bit unsigned integer that represents the renderer's unique identifier.
 */
static inline uint32_t GetRendererID() { return s_RendererID; }

		virtual void AddDataToBuffer(float* Verticies, uint32_t Size) override;

		virtual void AddDataToBuffer(const void* Verticies, uint32_t Size) override;

		virtual Vertex* CreateQuad(Vertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;
		virtual CircleVertex* CreateCircle(CircleVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, float Thickness, float Fade, int EntID) override;
		virtual LineVertex* CreateLine(LineVertex* Target, Vector4 Color, Vector3 Position0, Vector3 Position1, int EntID = -1) override;
		virtual TextVertex* CreateText(TextVertex* Target, Matrix4D Transform, Vector4* Position, Vector4 Color, Vector2* TexCoords, float TexID,int EntID) override;
		virtual TileVertex* CreateTile(TileVertex* Target, Vector4 Color, Vector4* Position, Vector2 Size, Matrix4D Transform, const Vector2* TexCoords, float TilingFactor, float ID, int EnttID) override;

		/**
 * @brief Returns the layout of this buffer.
 *
 * This function returns a reference to the layout object that describes how data is stored in the buffer. The returned value cannot be modified directly, but can be used to understand the structure of the buffer's data.
 *
 * @return A const reference to the BufferLayout object representing the layout of this buffer.
 */
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

		/**
 * @brief This function returns the current count value.
 *
 * @return The current count value as a uint32_t.
 */
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