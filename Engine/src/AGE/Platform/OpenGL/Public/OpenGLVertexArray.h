#pragma once
#include "Render/Public/VertexArray.h"
#include <memory>

namespace AGE
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();

		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) override;

		virtual void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
		virtual void EnableVertexAttribArray(int ArrayID) const override;

		virtual void MakeVertexAttribPtr(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const override;

		std::vector<Ref<VertexBuffer>>::iterator begin() { return m_VertexBuffers.begin(); }

		std::vector<Ref<VertexBuffer>>::iterator end() { return m_VertexBuffers.end(); }

		std::vector<Ref<VertexBuffer>>::const_iterator begin() const { return m_VertexBuffers.begin(); }

		std::vector<Ref<VertexBuffer>>::const_iterator end() const { return m_VertexBuffers.end(); }


	private:

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_ArrayID;
	};
}