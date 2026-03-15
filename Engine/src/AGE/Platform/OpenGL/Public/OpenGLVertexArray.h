#pragma once
#include "Render/Public/VertexArray.h"
#include <memory>

namespace AGE
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();

		~OpenGLVertexArray() override;

		void Bind() const override;

		void Unbind() const override;

		void AddVertexBuffer(Ref<VertexBuffer>& VertexBuffer) override;

		void SetIndexBuffer(Ref<IndexBuffer>& IndexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
		
		void EnableVertexAttribArray(uint32_t ArrayID) const override;

		void MakeVertexAttribPtr(uint32_t index, int size, uint32_t type, uint8_t normalized, int stride, const void* pointer) const override;

		std::vector<Ref<VertexBuffer>>::iterator begin() override { return m_VertexBuffers.begin(); }

		std::vector<Ref<VertexBuffer>>::iterator end() override { return m_VertexBuffers.end(); }

		std::vector<Ref<VertexBuffer>>::const_iterator begin() const override { return m_VertexBuffers.begin(); }

		std::vector<Ref<VertexBuffer>>::const_iterator end() const override { return m_VertexBuffers.end(); }


	private:

		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_ArrayID;
	};
}